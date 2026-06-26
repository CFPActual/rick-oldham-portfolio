import torch
import torch.optim as optim
from torch.utils.data import DataLoader
from utils import gradient_penalty, save_checkpoint, load_checkpoint, tic, toc, halt, beep, ring
from projectRO4.imageprocessing import save_gan_images
from config_gan import*
from config_common import*
from model_gan import Discriminator, Generator, initialize_weights
import time
import torchvision
from ganvisualization import GANVisualization
from threading import Event


class GANModelTraining:

    def train_gan_model(self, data, classes):
        dataset = data
        class_list = classes

        # For saving images
        datetimestr = time.strftime('%Y%m%d-%H%M')
        save_thresh = SAVE_THRESHOLD

        # # Decide which device we want to run on
        # device = torch.device('cuda:0' if (torch.cuda.is_available() and ngpu > 0) else 'cpu')
        device = "cuda" if torch.cuda.is_available() else "cpu"

        loader = DataLoader(dataset, batch_size=BATCH_SIZE_G, shuffle=True, num_workers=WORKERS)

        ## initialize gen and disc, note: discriminator should be called critic,
        # according to WGAN paper (since it no longer outputs between [0, 1])
        gen = Generator(Z_DIM, CHANNELS_IMG, FEATURES_GEN, NUM_CLASSES, IMG_SIZE, GEN_EMBEDDING).to(device)
        critic = Discriminator(CHANNELS_IMG, FEATURES_CRITIC, NUM_CLASSES, IMG_SIZE).to(device)
        initialize_weights(gen)
        initialize_weights(critic)

        # initializate optimizer
        opt_gen = optim.Adam(gen.parameters(), lr=LEARNING_RATE_G, betas=(0.0, 0.9))
        opt_critic = optim.Adam(critic.parameters(), lr=LEARNING_RATE_G, betas=(0.0, 0.9))

        # for tensorboard plotting
        log_dir = './logs/GAN_MNIST_' + datetimestr
        tboard = GANVisualization(log_dir)

        step = 1
        gen.train()
        critic.train()

        start = tic()
        for epoch in range(NUM_EPOCHS_G):
            beep()
            # for batch_idx, (real, labels) in enumerate(tqdm(loader)):
            for batch_idx, (real, labels) in enumerate(loader):
                real = real.to(device)
                cur_batch_size = real.shape[0]
                labels = labels.to(device)

                # Train Critic: max E[critic(real)] - E[critic(fake)]
                # equivalent to minimizing the negative of that
                for _ in range(CRITIC_ITERATIONS):
                    noise = torch.randn(cur_batch_size, Z_DIM, 1, 1).to(device)
                    fake = gen(noise, labels)
                    critic_real = critic(real, labels).reshape(-1)
                    critic_fake = critic(fake, labels).reshape(-1)
                    gp = gradient_penalty(critic, labels, real, fake, device=device)
                    loss_critic = (
                            -(torch.mean(critic_real) - torch.mean(critic_fake)) + LAMBDA_GP * gp
                    )
                    critic.zero_grad()
                    loss_critic.backward(retain_graph=True)
                    opt_critic.step()

                # Train Generator: max E[critic(gen_fake)] <-> min -E[critic(gen_fake)]
                gen_fake = critic(fake, labels).reshape(-1)
                loss_gen = -torch.mean(gen_fake)
                gen.zero_grad()
                loss_gen.backward()
                opt_gen.step()

                # Every nth batch the tensorboard logs are updated and maybe some images are
                output_frequency = OUTPUT_FREQUENCY
                if batch_idx % output_frequency == 0 and batch_idx > 0:
                    print(f"\tEpoch [{epoch + 1}/{NUM_EPOCHS_G}] Batch {batch_idx}/{len(loader)} / Loss D: {loss_critic:.4f}, loss G: {loss_gen:.4f}, Step: {step:n}")
                    with torch.no_grad():
                        # take out (up to) "SAMPLE_SIZE" examples
                        real_batch = real[:BATCH_SIZE_G]
                        fake_batch = fake[:BATCH_SIZE_G]
                        real_display_batch = real[:DISPLAY_SIZE_G]
                        fake_display_batch = fake[:DISPLAY_SIZE_G]
                        img_grid_real = torchvision.utils.make_grid(real_display_batch, nrow=ROWS_G, normalize=True)
                        img_grid_fake = torchvision.utils.make_grid(fake_display_batch, nrow=ROWS_G, normalize=True)
                        batch_labels = labels.tolist()
                        tboard.write_logs(img_grid_real, img_grid_fake, loss_gen, loss_critic, real_batch, fake_batch, batch_labels, step)
                        Event().wait(1)

                        # if generator loss is below the assigned thresh, save the batch as images
                        if (epoch + 1) > 1 and loss_gen <= save_thresh:
                            batch_id = '_E_' + str(epoch + 1) + '_B_' + str(batch_idx)
                            filepath = './gan_images/generated_' + datetimestr + batch_id
                            save_gan_images(filepath, fake_batch, batch_labels)
                            save_thresh = loss_gen  # to save progressively better images

                    tboardstart = output_frequency * 2  # Note must be < total batch count
                    if (epoch + 1) == 1 and batch_idx == tboardstart:  # start tboard at first epoch, nth batch
                        print()
                        print('Lets pause a few seconds while TensorBoard is loaded...\n')
                        tboard.start_tensorboard()

                    step += 1

        # ring()
        # halt()
        tboard.stop_tensorboard()
        stop = toc()
        elapsed = stop - start
        ring()
        print('Training completed in', elapsed, 'seconds or', (elapsed / 60), 'minutes for', NUM_EPOCHS_G, 'epochs.')
