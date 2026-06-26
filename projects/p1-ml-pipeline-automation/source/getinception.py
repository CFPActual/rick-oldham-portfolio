import torch
import torchvision.transforms as transforms
import warnings
# Some additional metrics to gauge GAN performance
# Some background info in the two metrics: https://arxiv.org/pdf/1801.01401.pdf
# The docs: https://torchmetrics.readthedocs.io/en/stable/index.html
from torchmetrics.image.fid import FrechetInceptionDistance
from torchmetrics.image.kid import KernelInceptionDistance


def get_scores(real_batch, fake_batch):
    transforms_list = []
    trans1 = transforms.ConvertImageDtype(torch.uint8)
    trans2 = transforms.Resize(299)
    transforms_list.append(trans1)
    transforms_list.append(trans2)
    compose_list = transforms.Compose(transforms_list)
    trans = transforms.Compose(compose_list.transforms)

    real_batch_channels = list(real_batch.shape)[1]
    fake_batch_channels = list(fake_batch.shape)[1]

    # The inbound tensors are of shape (batch size, image channel, image height, image width)
    # or (64, 1, 64, 64) ---> 4D
    # for .expand() -1 means "don't act on this dimension"
    # the 3 at dim 1 will turn 1 channel images into 3 channel images: new shape ---> (64, 3, 64, 64)
    # This, the resize and the conversion from torch.float32 to torch.uint8 are required by the inception metric classes
    if real_batch_channels == fake_batch_channels == 1:
        r = real_batch.expand(-1, 3, -1, -1)
        f = fake_batch.expand(-1, 3, -1, -1)
        r = trans(r)
        f = trans(f)
        r = r.to('cpu')  # so the device matches that of the weights tensors inception metric classes
        f = f.to('cpu')
        fid, kid = compute_inception(r, f)
        return fid, kid
    else:
        r = trans(real_batch)
        f = trans(fake_batch)
        r = r.to('cpu')
        f = f.to('cpu')
        fid, kid = compute_inception(r, f)
        return fid, kid


def compute_inception(r, f):
    warnings.filterwarnings("ignore")
    fid = FrechetInceptionDistance(feature=64)
    kid = KernelInceptionDistance(subsets=4, subset_size=16)

    fid.update(r, real=True)
    fid.update(f, real=False)
    frechet_dist = fid.compute()
    distance = frechet_dist.item()

    kid.update(r, real=True)
    kid.update(f, real=False)
    kid_mean, kid_std = kid.compute()
    mean = kid_mean.item()

    return distance, mean
