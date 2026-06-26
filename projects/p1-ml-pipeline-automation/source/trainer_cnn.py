import torchvision
# from projectRO4.__init__ import *
from model_cnn import CNNModel
from torch.utils.data import DataLoader
import torch.nn as nn
import torchvision.transforms.functional as functional
from config_cnn import*
from cnnvisualization import CNNVisualization
import time
from utils import halt, ring
from threading import Event
import torch.optim as optim
from torch.optim import lr_scheduler
import torch
import copy


class CNNModelTraining:

    # the model trainer
    def train_cnn_model(self, dataset, dataset_sizes, class_names):
        datetimestr = time.strftime('%Y%m%d-%H%M')
        print("Starting CNN Training Loop...")
        print()

        # # for tensorboard plotting
        # log_dir = './logs/CNN_MNIST_' + datetimestr
        # tboard = CNNVisualization(log_dir)
        # Assign a processor
        device = "cuda" if torch.cuda.is_available() else "cpu"

        # build the CNN model
        model = CNNModel(device)
        model = model.build(class_names)

        # Assign a loss function
        criterion = nn.CrossEntropyLoss()

        # Observe that all parameters are being optimized
        optimizer = optim.SGD(model.parameters(), lr=LEARNING_RATE_C, momentum=MOMENTUM)

        # Decay LR by a factor of 0.1 every (step_size) epochs
        scheduler = lr_scheduler.StepLR(optimizer, step_size=STEP_SIZE, gamma=GAMMA)

        # The loader contains 2 data subsets: train and val
        loader = {x: DataLoader(dataset[x], batch_size=BATCH_SIZE_C, shuffle=True, num_workers=WORKERS) for x in ['train', 'val']}

        print(f"Epochs set to {NUM_EPOCHS_C}\n")

        start = time.time()
        best_model_wts = copy.deepcopy(model.state_dict())
        best_acc = 0.0

        # The training loop
        for epoch in range(NUM_EPOCHS_C):
            for phase in ['train', 'val']:
                if phase == 'train':
                    model.train()  # Set model to training mode
                else:
                    model.eval()  # Set model to evaluate mode
                running_loss = 0.0
                running_corrects = 0

                # Iterate over data.
                for images, labels in loader[phase]:
                    inputs = images
                    channels = functional.get_image_num_channels(inputs)
                    if channels != 3:
                        expanded_inputs = inputs.expand(-1, 3, -1, -1) # Tensors with 3-channel images are expected, so expand when needed
                        inputs = expanded_inputs
                    inputs = inputs.to(device)
                    labels = labels.to(device)

                    # zero the parameter gradients
                    optimizer.zero_grad()

                    # forward
                    # track history if only in train
                    with torch.set_grad_enabled(phase == 'train'):
                        outputs = model(inputs)
                        _, preds = torch.max(outputs, 1)
                        loss = criterion(outputs, labels)

                        # backward + optimize only if in training phase
                        if phase == 'train':
                            loss.backward()
                            optimizer.step()
                    running_corrects += torch.sum(preds == labels.data)
                    running_loss += loss.item() * inputs.size(0)

                if phase == 'train':
                    scheduler.step()
                epoch_loss = running_loss / dataset_sizes[phase]
                epoch_acc = running_corrects/ dataset_sizes[phase]
                print(f"Epoch {epoch + 1}/{NUM_EPOCHS_C} {phase} phase Loss: {epoch_loss:.4f} Acc: {epoch_acc:.4f}")

                # deep copy the model
                if phase == 'val' and epoch_acc > best_acc:
                    best_acc = epoch_acc # to capture progressively better accuracy
                    best_model_wts = copy.deepcopy(model.state_dict())
                    print(f"The best accuracy during {phase} phase is {best_acc * 100:.4f}% so far")
            print( )

        model.load_state_dict(best_model_wts)
        print()
        time_elapsed = time.time() - start
        print(f"Training complete in {time_elapsed // 60:.0f}m {time_elapsed % 60:.1f}s")  # no f prefix?
        print(f"The best accuracy is: {best_acc * 100:4f}")
        print()

        ## load best model weights
        model.load_state_dict(best_model_wts)
        # return model
        # Start tensorboard...
        print('Lets pause a few seconds while TensorBoard is loaded...\n')
        log_dir = './logs/CNN_MNIST_' + datetimestr
        tboard = CNNVisualization(log_dir)
        tboard.start_tensorboard()

        acc_log = []
        step = 1
        freq = 100 # How often you want tensor board updated
        # Test the trained model with the Validation set
        model.eval()
        for idx, (images, labels) in enumerate(loader['val']):
            with torch.no_grad():
                inputs = images
                channels = functional.get_image_num_channels(inputs)
                if channels != 3:
                    expanded_inputs = inputs.expand(-1, 3, -1, -1)  # Tensors with 3-channel images are expected, so expand when needed
                    inputs = expanded_inputs
                inputs = inputs.to(device)
                labels = labels.to(device)

                outputs = model(inputs)
                _, preds = torch.max(outputs, 1)

                if idx % freq == 0 and idx >= 1:
                    batch_labels = labels.tolist()
                    batch_preds = preds.tolist()
                    wrong = torch.subtract(labels.data, preds).tolist()
                    pred_total = len(batch_labels)
                    bad_pred_count = sum(elem != 0 for elem in wrong)
                    batch_acc = (pred_total - bad_pred_count) / pred_total
                    acc_log.append(batch_acc)

                    img_tensor_list = []
                    for pos, elem in enumerate(wrong):
                        img = inputs[pos]
                        if elem != 0:
                            img_tensor_list.append(functional.invert(img))
                        else:
                            img_tensor_list.append(img)

                    # To tensorboard
                    marked_input_batch = torch.stack(img_tensor_list)
                    img_grid = torchvision.utils.make_grid(marked_input_batch, nrow=ROWS_C, normalize=True)
                    # tboard.plot_batch(marked_input_batch, device)
                    avg = sum(acc_log) / len(acc_log)
                    begin = idx - 100
                    end = idx
                    tboard.write_logs(img_grid, batch_preds, batch_labels, step)
                    Event().wait(1)
                    print(f"Average accuracy from batch {begin:n} to batch {end:n} is: {avg * 100:4f} step {step:n} idx {idx:n}")
                    step += 1
        # ring()
        # halt()
        tboard.stop_tensorboard()
