import torch
import subprocess
import webbrowser
import time
import sys
import os
import numpy as np
from sklearn.model_selection import train_test_split
from torch.utils.data import Subset
import copy
import winsound



# For the GAN - to modify the dataset so that only specific targets are generated
def select_classes(dset, target_list):
    select_classes_idx = target_list

    idx_list = []
    for elem in select_classes_idx:
        for i in range(len(dset)):
            if dset.targets[i].item() == elem:
                idx_list.append(i)

    # Deep copy please
    temp = copy.deepcopy(dset.classes)
    dset.classes.clear()

    # Update classes
    for elem in select_classes_idx:
        dset.classes.append(temp[elem])

    # Update data and targets
    dset.targets = dset.targets[idx_list]
    dset.data = dset.data[idx_list]
    return dset


# Split the dataset in a way that preserves parent set data distribution
# Default callsklearn.model_selection.train_test_split(*arrays, test_size=None, train_size=None, random_state=None, shuffle=True, stratify=None)[source]
# Docs --> https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.train_test_split.html
def stratified_split(dataset, test_perc):
    labels_idx = dataset.targets
    # Stratified Sampling for train and val
    train_idx, test_idx = train_test_split(np.arange(len(dataset)), test_size=test_perc, random_state=42, shuffle=True, stratify=labels_idx)
    # Subsets for train and val
    train_datasubset = Subset(dataset, train_idx)
    test_datasubset = Subset(dataset, test_idx)
    return train_datasubset, test_datasubset


def gradient_penalty(critic, labels, real, fake, device="cpu"):
    BATCH_SIZE, C, H, W = real.shape
    alpha = torch.rand((BATCH_SIZE, 1, 1, 1)).repeat(1, C, H, W).to(device)
    interpolated_images = real * alpha + fake * (1 - alpha)

    # Calculate critic scores
    mixed_scores = critic(interpolated_images, labels)

    # Take the gradient of the scores with respect to the images
    gradient = torch.autograd.grad(
        inputs=interpolated_images,
        outputs=mixed_scores,
        grad_outputs=torch.ones_like(mixed_scores),
        create_graph=True,
        retain_graph=True,
    )[0]
    gradient = gradient.view(gradient.shape[0], -1)
    gradient_norm = gradient.norm(2, dim=1)
    gradient_penalty_with_norm = torch.mean((gradient_norm - 1) ** 2)
    return gradient_penalty_with_norm


def save_checkpoint(state, filename="celeba_wgan_gp.pth.tar"):  # where is it saving to, if at all
    print("=> Saving checkpoint")
    torch.save(state, filename)


def load_checkpoint(checkpoint, gen, disc):
    print("=> Loading checkpoint")
    gen.load_state_dict(checkpoint['gen'])
    disc.load_state_dict(checkpoint['disc'])


def load_tensorboard(log_dir):
    run_cmd_proc = subprocess.Popen(f"tensorboard --logdir={log_dir} --reload_multifile=True")  #
    return run_cmd_proc


def open_host():
    webbrowser.open('http://localhost:6006/', new=2)  # Opens the tensor board link in edge


def tensor_msg():
    print('\nTensorboard has started, lets goooo...:\n')


## This section supports testing and development
# start time
def tic():
    start = time.time()
    return start
# end of tic


# stop time
def toc():
    stop = time.time()
    return stop
# end of toc


def beep():
    winsound.Beep(440, 250)
    winsound.Beep(440, 250)


def ring():
    stop = 8
    for i in range(1, stop + 1):
        winsound.PlaySound('Default Beep', winsound.SND_ALIAS)


def halt():
    os.system("pause")
    # sys.exit(519)
