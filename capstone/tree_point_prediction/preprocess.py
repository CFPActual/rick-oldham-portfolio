# import tensorflow as tf
#
# def preprocess_RGBN(images):
#     R = images[...,0:1]
#     N = images[...,3:4]
#     ndvi = tf.math.divide_no_nan((N-R),(N+R))
#     ndvi *= 127.5
#
#     bgr = tf.keras.applications.vgg16.preprocess_input(images[:,:,:,:3])
#
#     nir = (images[:,:,:,3:4]-127.5)
#
#     images_out = tf.concat([bgr,nir,ndvi],axis=-1)
#
#     return images_out
#
# def preprocess_RGB(images):
#     bgr = tf.keras.applications.vgg16.preprocess_input(images[:,:,:,:3])
#
#     return bgr

import tensorflow as tf  # keep if other code uses it
from keras import ops    # NEW: use Keras ops for symbolic tensors


# VGG16 "caffe" style mean (BGR order)
_IMAGENET_MEAN = ops.convert_to_tensor(
    [103.939, 116.779, 123.68], dtype="float32"
)


def _vgg16_preprocess_rgb(images):
    """
    VGG16-style 'caffe' preprocessing for KerasTensors:
    - expects RGB channels
    - assumes inputs are 0–255 (same as original preprocess_input usage)
    - converts RGB -> BGR
    - subtracts ImageNet mean
    """
    # take RGB channels and cast to float32
    x = images[..., :3]
    x = ops.cast(x, "float32")

    # RGB -> BGR using Keras ops
    r = x[..., 0:1]
    g = x[..., 1:2]
    b = x[..., 2:3]
    x_bgr = ops.concatenate([b, g, r], axis=-1)

    # subtract Imagenet BGR mean (broadcasts across H,W)
    return x_bgr - _IMAGENET_MEAN


def preprocess_RGBN(images):
    """
    RGB + NIR preprocessing:
    - VGG16-style preprocessing on RGB -> BGR
    - NDVI from R and NIR
    - NIR centered around 127.5 like original code
    """
    x = ops.cast(images, "float32")

    # R and NIR bands for NDVI
    R = x[..., 0:1]
    N = x[..., 3:4]

    # NDVI = (N - R) / (N + R + eps)
    eps = ops.convert_to_tensor(1e-6, dtype="float32")
    ndvi = (N - R) / (N + R + eps)
    ndvi = ndvi * 127.5  # match original scaling

    # VGG-style preprocessing on RGB part
    bgr = _vgg16_preprocess_rgb(x)

    # NIR channel centered around 0 like before
    nir = x[..., 3:4] - 127.5

    # concat BGR + NIR + NDVI
    images_out = ops.concatenate([bgr, nir, ndvi], axis=-1)
    return images_out


def preprocess_RGB(images):
    """
    RGB-only preprocessing: VGG16-style BGR + mean subtraction.
    """
    return _vgg16_preprocess_rgb(images)


