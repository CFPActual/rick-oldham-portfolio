import math
# Hyperparameters specific to the CNN

BATCH_SIZE_C = 64
GAMMA = 0.1
LEARNING_RATE_C = 0.001
MOMENTUM = 0.9
NUM_EPOCHS_C = 5
NUM_TRAIN_SAMPLES = 320
STEP_SIZE = 7
WORKERS = 0

# Not specific to model training; these support visualization
DISPLAY_SIZE_C = BATCH_SIZE_C # 64  # Size of the sample grid used for tensorboard; independent of batch size; USE PERFECT SQUARES!!!
ROWS_C = int(math.sqrt(DISPLAY_SIZE_C))

