from torch.utils.tensorboard import SummaryWriter
from utils import load_tensorboard, open_host, tensor_msg
from threading import Event
import matplotlib.pyplot as plt
import torchvision.utils as vutils
import numpy as np
from config_cnn import*
import os
from config_common import*
import torch


class CNNVisualization:


    def __init__(self, log_dir):
        self.log_dir = log_dir

        # TB docs suggests running rm -rf logs/
        if not os.path.exists('logs/'):
            os.makedirs('logs/')

        self.writer_real = SummaryWriter(f"{self.log_dir}/batch_preds")
        self.sub_process = None


    def start_tensorboard(self):
        self.sub_process = load_tensorboard(self.log_dir)
        Event().wait(15)  # do not allow the next line to execute until the waiting period has expired
        tensor_msg()
        open_host()


    def write_logs(self, img_grid, preds_list, truth_list, step):
        preds = "Predictions: " + str(preds_list[0:DISPLAY_SIZE_C])[1:-1]
        self.writer_real.add_text("Batch predictions", preds, global_step=step)

        truth = "Truth: " + str(truth_list[0:DISPLAY_SIZE_C])[1:-1]
        self.writer_real.add_text("Batch truth", truth, global_step=step)

        self.writer_real.add_image("Inverted colors are incorrect predictions", img_grid, global_step=step)
        self.writer_real.flush()


    def stop_tensorboard(self):
        self.writer_real.close()
        self.sub_process.terminate()
        # self.sub_process.kill()


    def plot_batch(self, batch, device):
        real_batch = batch
        plt.figure(figsize=(4, 4))
        plt.axis('off')
        plt.title('Inverted colors are incorrect predictions')
        plt.imshow(np.transpose(vutils.make_grid(real_batch.to(device)[:DISPLAY_SIZE_C], nrow=ROWS_C, padding=2, normalize=True).cpu(), (1, 2, 0)))
        # filename = filepath + '/training_images_sample_grid_' + datetimestr+'.png'
        # plt.savefig(filename)
        plt.show(block=False)
        plt.ioff()
        plt.show()
