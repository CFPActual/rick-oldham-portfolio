import os
import torch
from torchvision.utils import save_image
from config_common import*
import torchvision.transforms as transforms
import torchvision.transforms.functional as functional
from config_gan import*


ds_mean = []
ds_std = []
original_size = 0

bulk_transforms_list = []
trans_01 = transforms.Grayscale(num_output_channels=3) # optional param --> num_output_channels=1 or 3 Note: 1 channel images will be expanded to 3 where needed
trans_02 = transforms.CenterCrop(128)
trans_03 = transforms.RandomHorizontalFlip(p=0.33) # default value of p is 0.5
trans_04 = transforms.RandomVerticalFlip(p=0.33)
trans_05 = transforms.RandomRotation(degrees=120)
trans_06 = transforms.RandomCrop(100) # Single value for square crop or (h,w) value pair for rectangular crop
trans_07 = transforms.ColorJitter(brightness=(0.5,1.5), contrast=(1), saturation=(0.5,1.5), hue=0.25)
trans_08 = transforms.RandomGrayscale(p=0.25)
trans_09 = transforms.RandomInvert(p=0.1)
trans_10 = transforms.RandomAutocontrast()
trans_11 = transforms.GaussianBlur(kernel_size=501)
trans_12 = transforms.RandomPerspective(distortion_scale=0.6, p=0.25)
trans_13 = transforms.RandomCrop(size=(128, 128))
trans_14 = transforms.RandomErasing()
trans_15 = transforms.RandomResizedCrop(200)
trans_16 = transforms.Resize((IMG_SIZE, IMG_SIZE))  # int param --> maintains original image aspect ration, tuple param does not
trans_17 = transforms.ToTensor()
trans_18 = transforms.Normalize([0.5 for _ in range(CHANNELS_IMG)], [0.5 for _ in range(CHANNELS_IMG)]) # 0.5 mean and 0.5 std dev per channel ---> range[-1,1]
trans_19 = transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])  # the ImageNet standard for 3-channel images. Considered common practice
trans_20 = transforms.Normalize(ds_mean, ds_std)  # Optional mean and standard deviation freshly calculated in main


## select the transforms to apply - common transforms seem to be trans_ 16, 17 and (18, 19 , or 20); order matters adjust --> to tensor --> normalize
bulk_transforms_list.append(trans_01)
bulk_transforms_list.append(trans_02)
bulk_transforms_list.append(trans_03)
bulk_transforms_list.append(trans_04)
bulk_transforms_list.append(trans_05)
bulk_transforms_list.append(trans_06)
bulk_transforms_list.append(trans_07)
bulk_transforms_list.append(trans_08)
bulk_transforms_list.append(trans_09)
bulk_transforms_list.append(trans_10)
bulk_transforms_list.append(trans_11)
bulk_transforms_list.append(trans_12)
bulk_transforms_list.append(trans_13)
bulk_transforms_list.append(trans_14)
bulk_transforms_list.append(trans_15)
bulk_transforms_list.append(trans_16)
bulk_transforms_list.append(trans_17)
bulk_transforms_list.append(trans_18)
bulk_transforms_list.append(trans_19)
bulk_transforms_list.append(trans_20)


## Create the Compose object from the bulk list of transforms;
# idx_list is a list of the indices of the bulk list corresponding to your trans_* choice(s)
def get_transformations(idx_list):
    transforms_to_apply = []
    for idx in idx_list:
        transforms_to_apply.append(bulk_transforms_list[idx])
    composelist = transforms.Compose(transforms_to_apply)
    return composelist


# Calculate mean and standard deviation of the dataset to be used with normalization
def get_stats(loader):
    channels_sum, channels_squared_sum, num_batches = 0, 0, 0
    num_batches = 0
    for data, _ in loader:
        channels_sum += torch.mean(data, dim=[0, 2, 3])
        channels_squared_sum += torch.mean(data**2, dim=[0, 2, 3])
        num_batches += 1
    mn = channels_sum / num_batches
    sd = (channels_squared_sum / num_batches - mn**2)**0.5
    mean = mn.tolist()
    std = sd.tolist()
    return mean, std


# If needed, check_image_dim will provide the paths of non-square images (where h != w)
def check_image_dim(loader):
    count = 0
    samples = loader.dataset.imgs
    for idx, (image, _) in enumerate(loader, 0):
        if functional.get_image_size(image) != [200, 200]:
            print(samples[idx], 'is', functional.get_image_size(image))
            count += 1
    print('There are', count, 'images with the wrong dimensions.')


def save_gan_images(filepath, img_batch, batch_labels):
    if len(img_batch) == 0:
        print('No images to save')
        return
    if not os.path.exists(filepath):
        os.makedirs(filepath)
    # Split the tensor into sub-tensors of 1 image
    for idx, image in enumerate(torch.split(img_batch, 1)):
        # Convert tensors to .png files and save them
        trans = transforms.Resize((O_H, O_W))
        image = trans(image) # resize back to original dimensions before saving
        fake_fname = 'fake_image_' + str(idx + 1) + '_(' + str(batch_labels[idx]) + ')' + '.png'
        save_image(image, os.path.join(filepath, fake_fname))
