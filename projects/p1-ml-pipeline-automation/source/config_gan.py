import math
# Hyperparameters specific to the GAN
BATCH_SIZE_G = 64
CRITIC_ITERATIONS = 5  # recommended 5 - 10 discriminator iters per generator iter

# Features: MUST BE 16 for MNIST, 64 for others, don't forget the channels setting in config_common
FEATURES_CRITIC = 16
FEATURES_GEN = 16
GEN_EMBEDDING = 100
LAMBDA_GP = 10
# Learning rate for training optimizers. As described in the DCGAN paper, this number should be 0.0002
# If your model uses a learning rate scheduler review this on the pitfalls of the wrong setting https://neptune.ai/blog/how-to-choose-a-learning-rate-scheduler
# lr = 0.0002 # range between 0.0 and 1.0
# # Another approach in the fid example is to use different Learning rates for optimizers
# g_lr = 0.0004 # 0.0001
# d_lr = 0.0002 # 0.0002
LEARNING_RATE_G = 1e-4  # For now, this is the shared value
NUM_EPOCHS_G = 5
WORKERS = 0
Z_DIM = 100

# Not specific to model training; these support visualization and image saving
DISPLAY_SIZE_G = BATCH_SIZE_G  # Size of the sample grid used for tensorboard; independent of batch size; USE PERFECT SQUARES!!!
ROWS_G = int(math.sqrt(DISPLAY_SIZE_G))
SAVE_THRESHOLD = 25
OUTPUT_FREQUENCY = 150
# If size is a sequence like (h, w), output size will be matched to this
O_H = 28 # set this to the original image height
O_W = 28 # set this to the original image width
