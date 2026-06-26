# Tree Point Prediction (TPP) – Frozen Evaluator  

This directory contains the Tree Point Prediction (TPP) component used in the  
**“Image Quality as a Hyperparameter”** capstone project.  

Here, TPP is **not** a research target.  
Instead, it is treated as a **fixed measurement instrument** (“meter”) that evaluates how different image enhancement strategies affect downstream detection performance.  

For the full experimental setup, see the main README at the repository root.  

---

## What This Module Contains  

This directory is adapted from the original GreenCity Tree Point Prediction implementation and typically includes:  

- model definition and training scripts  
- inference pipeline for tiled imagery  
- evaluation scripts (including `evaluation-NEW-2.py`)  
- utility code for preparing inputs and merging outputs  

In the context of this capstone:  

- the training code is kept intact for reference and reproducibility, but  
- the primary mode of operation is **frozen-eval** on a fixed set of weights.  

---

## Model and Weights  

The underlying model is a VGG-style SFANet-based tree point detector trained on Pasadena tiles.  

For this project, a single set of weights is treated as the **canonical meter**:  

- training run: 15 epochs (selected best run)  
- approximate baseline performance on raw imagery:  
&emsp;- Recall: ~0.825  
&emsp;- Precision: ~0.197  
&emsp;- F1: ~0.318  
&emsp;- Mean distance: ~4.9 m  

These numbers provide the reference point for comparing different computer-vision enhancement (CVE) configurations in the image enhancement pipeline.  

---

## How TPP Is Used in This Project  

1. **Inputs**  
   - TPP receives either raw chips or CVE-enhanced chips produced by the `image_enhancement/` module.  

2. **Inference**  
   - The model runs in evaluation mode using the fixed 15-epoch weights.  
   - Predictions are typically written as per-tile outputs (for example, GeoJSON or similar formats).  

3. **Evaluation**  
   - `evaluation-NEW-2.py` (and related scripts) compute:  
     - Recall @ 12 m  
     - TP / FN / FP  
     - Precision and F1  
     - average distance to matched trees  
     - distance distributions  
   - Results are stored as tables and plots under `results/`.  

4. **Experiment Logging**  
   - Each CVE configuration + TPP evaluation pair is logged to `results/experiments.csv` (or an equivalent registry) along with its key metrics.  

Throughout this process, **the model remains unchanged**. All experimental variation comes from the **inputs**, not from retraining or re-tuning the TPP model.  

---

## Role in the “Model as Meter” Frame  

In the main capstone, TPP serves as the **meter** in the phrase “model as a meter”:  

- CVE operations adjust input images.  
- TPP processes those images with frozen weights.  
- Evaluation measures how those adjustments affect recall, localization, and stability.  

This design:  

- removes variance due to retraining,  
- focuses analysis on the **effects of image quality**, and  
- supports controlled comparison of many CVE configurations.  

---

## Relationship to the Original GreenCity Project  

This module is a **summary and reuse** of the original GreenCity Tree Point Prediction work.  
For full architectural details, training regimes, and broader application context (including canopy mapping and web deployment), please refer to the upstream project:  

- [GreenCity – Tree Point Prediction (original)](https://github.com/antonioamartinez/Green-City/tree/main/tree_point_prediction)  

That repository remains the canonical reference for:  

- the complete TPP training pipeline,  
- integration with canopy detection and mapping, and  
- the broader GreenCity vision and UI.  

This continuation capstone narrows the focus to a single question:  

> How does changing image quality, via computer-vision enhancement, affect a fixed tree-point detector’s performance?  

TPP here is the stable measurement device used to answer that question.  

---

