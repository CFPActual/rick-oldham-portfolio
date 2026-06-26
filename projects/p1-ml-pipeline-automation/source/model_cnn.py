from torchvision.models import ResNet18_Weights
import torch.nn as nn
import torchvision.models as models


class CNNModel:

    def __init__(self, device):
        self.device = device

    def build(self, class_names):
        # # resnet/cnn MODEL SETUP
        # "pretrained=True or False" deprecated solution here --> https://qiita.com/noobar/items/6d985f92ad6e364aaefe
        model = models.resnet18(weights=ResNet18_Weights.IMAGENET1K_V1)

        # The number of input features
        num_ftrs = model.fc.in_features

        # A couple of different techniques for assigning the value
        num_classes = len(class_names)  # measure a list

        # Here the size of each output sample is set to 2.
        # Alternatively, it can be generalized to nn.Linear(num_ftrs, len(class_names)).
        model.fc = nn.Linear(num_ftrs, num_classes)  # num_outputs set in init.py 1000 for resnet, 10 for mstar

        model = model.to(self.device)

        return model
