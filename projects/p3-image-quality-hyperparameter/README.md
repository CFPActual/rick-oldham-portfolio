# Image Quality as a Hyperparameter

## Problem

Image enhancement techniques such as brightness adjustment, sharpening, and contrast modification are commonly used in computer vision workflows. This project investigated whether these preprocessing choices behave like hyperparameters and how they influence downstream model performance.

## Approach

A controlled experimental framework was developed to evaluate combinations of image enhancement settings across multiple computer vision training runs. Performance was measured across enhancement schedules to identify individual effects and interactions between preprocessing parameters.

## Results

Results showed that image enhancement parameters can significantly influence model performance and should be treated as tunable components of the machine learning pipeline. Strong interaction effects were observed between enhancement settings, and visually improved images did not always produce better model outcomes.

## Technologies

Python, TensorFlow/Keras, OpenCV, NumPy, Pandas, Matplotlib, Jupyter Notebook

## Key Topics

Computer Vision, Data-Centric AI, Feature Engineering, Experimental Design, Hyperparameter Optimization, Machine Learning

## Artifacts

* Enhancement Interaction Heatmap
* [Project Report](https://github.com/CFPActual/myPFP/blob/main/capstone/image_enhancement/final_report_README.md)
* [Source Code](https://github.com/CFPActual/myPFP/blob/main/capstone/image_enhancement/model_as_a_meter.ipynb)


### Interaction Heatmaps (Median Recall)
![Interaction Heatmaps](capstone/image_enhancement/results/final_figures/fig06_interaction_heatmaps_grid.png)

*Median recall surfaces show strong interaction effects among enhancement parameters. Brightness conditions sharpening behavior, while contrast window geometry exhibits bounded performance regimes.*
