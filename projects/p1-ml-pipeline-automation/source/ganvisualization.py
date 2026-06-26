from torch.utils.tensorboard import SummaryWriter
from utils import load_tensorboard, open_host, tensor_msg
from threading import Event
from getinception import get_scores
import matplotlib.pyplot as plt
import torchvision.utils as vutils
import numpy as np
from config_gan import*
import os


class GANVisualization:

    def __init__(self, log_dir):
        self.log_dir = log_dir

        # TB docs suggests running rm -rf logs/
        if not os.path.exists('logs/'):
            os.makedirs('logs/')

        self.writer_real = SummaryWriter(f"{self.log_dir}/real")
        self.writer_fake = SummaryWriter(f"{self.log_dir}/fake")
        self.writer_g_loss = SummaryWriter(f"{self.log_dir}/g_loss")
        self.writer_d_loss = SummaryWriter(f"{self.log_dir}/d_loss")
        self.writer_fid = SummaryWriter(f"{self.log_dir}/FID")
        self.writer_kid = SummaryWriter(f"{self.log_dir}/KID")
        self.sub_process = None


    def start_tensorboard(self):
        self.sub_process = load_tensorboard(self.log_dir)
        Event().wait(15)  # do not allow the next line to execute until the waiting period has expired
        tensor_msg()
        open_host()


    def write_logs(self, img_grid_real, img_grid_fake, loss_gen, loss_critic, real_batch, fake_batch, batch_labels, step):
        fid, kid = get_scores(real_batch, fake_batch)
        self.writer_real.add_image("Real", img_grid_real, global_step=step)
        self.writer_real.flush()


        # explore add text and add_images seemes
        fake_labels = "Fake: " + str(batch_labels[0:DISPLAY_SIZE_G])[1:-1]
        self.writer_fake.add_text("Fake labels", fake_labels, global_step=step)
        self.writer_fake.add_image("Fake", img_grid_fake, global_step=step)
        self.writer_fake.flush()

        self.writer_g_loss.add_scalar("Generator Loss", loss_gen, global_step=step)
        self.writer_g_loss.flush()

        self.writer_d_loss.add_scalar("Discriminator Loss", loss_critic, global_step=step)
        self.writer_d_loss.flush()

        self.writer_fid.add_scalar("FID", fid, global_step=step)
        self.writer_fid.flush()

        self.writer_kid.add_scalar("KID", kid, global_step=step)
        self.writer_kid.flush()

    def stop_tensorboard(self):
        self.sub_process.terminate()
        self.sub_process.kill()
        self.writer_real.close()
        self.writer_fake.close()
        self.writer_g_loss.close()
        self.writer_d_loss.close()
        self.writer_fid.close()
        self.writer_kid.close()


    def plot_batch(self, batch, device):
        real_batch = batch
        plt.figure(figsize=(8, 8))
        plt.axis('off')
        plt.title('Images Sample')
        plt.imshow(np.transpose(vutils.make_grid(real_batch.to(device)[:DISPLAY_SIZE_G], nrow=ROWS_G, padding=2, normalize=True).cpu(), (1, 2, 0)))
        # filename = filepath + '/training_images_sample_grid_' + datetimestr+'.png'
        # plt.savefig(filename)
        plt.show(block=False)
        plt.ioff()
        plt.show()

