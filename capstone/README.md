# Capstone Readme: 
Welcome to my Capstone Page.  I hope you enjoy your stay.  <br><br>

# <center>Image Quality as a Hyperparameter</center>
 
## Quantifying how image quality engineering affects downstream model performance.  

This project investigates how targeted computer-vision enhancement (CVE) operations influence the performance of a fixed, pretrained model; in this case a [tree-point detection model](https://github.com/antonioamartinez/Green-City/tree/main/tree_point_prediction).   
In this work, the tree-point detection model is used as a meter.  
By treating the model as a measurement instrument rather than something to optimize, we isolate and study the impact of image quality on detection accuracy, localization error, and recall.

#### Project Overview

This work continues a broader exploration into the role of computer vision in urban canopy mapping. Instead of training a new model from scratch, the project focuses on a more fundamental question:

#### Research Question

How much can data manipulation benefit image processing tasks?
Specifically: to what extent can controlled changes to image quality improve downstream predictions?

#### Data Source

[Street ROW Trees – City of Pasadena, CA](https://data.cityofpasadena.net/datasets/593b88391b614123890f54a1db8fbf55_0/about)
Derived from public “Open Data 2.0,” paired with NAIP aerial imagery.

#### Techniques Used

Targeted image enhancement  
 - Contrast boosting, sharpening, gamma correction, and brightness normalization.

Targeted image adjustment  
 - Spectral conversions, geometric alignment, structural adjustments.

Parameterized preprocessing sweeps  
 - Systematic exploration of enhancement parameters (grid search).

Model readiness evaluation  
 - Measuring how changes in image structure affect downstream detection performance.

#### Expected Outcomes  

Discovery of which types of image manipulation improve detection, and under what conditions.

Practical guidance for improving urban-tree models without touching the architecture or training loop.

A scalable method for assessing model-readiness of imagery at city scale.

### Why This Matters  

In many real-world CV tasks, data quality—not model architecture—is the binding constraint. Understanding how far careful image engineering can push model performance helps answer:

What are the true limits of our imagery?  

Where can technique overcome those limits?  

How do we rescue borderline or “failed” image chips so they contribute meaningfully to training and inference?

This repository brings together two complementary components image enhancement and tree-point detection—to run controlled experiments that answer these questions.


### Experimental Frame
"Model as a Meter": A controlled environment for testing input engineering and understanding how models performing computer vision tasks respond to targeted changes in data quality.

This project uses the [Green City Tree Point Prediction (TPP) model](https://github.com/antonioamartinez/Green-City/tree/main/tree_point_prediction).  
It is not retrained during experimentation.
Instead, the model provides a stable, repeatable measurement of performance as image inputs change.

### Why Freeze the Model?

- Removes variance from training runs.

- Ensures all performance changes originate from the input, not the model.

- Provides a stable “meter” for evaluating the effect of image enhancement.

- The enhancement parameters, sequences, and transformations function as data-level hyperparameters.

- The model remains frozen; only the input-space hyperparameters change.

###  What Measurements does this Meter-model" provide?
#### The frozen model is evaluated on multiple metrics:

- Recall at 12 m

- True Positives / False Negatives / False Positives

- Precision and F1

- Average distance to closest predicted tree

- Per-tree distance distributions

- Recall vs. threshold curves

- Multirun variance (standard deviation, confidence intervals)

### What Do These Metrics Tell Us?  
#### These metrics will help us identify performance impact from changes in image characteristics resulting from:  
&emsp;1. Changes in image characteristics related to visual quality; sharpness, contrast, brightness.  
&emsp;2. Adjustments to image geometry  
&emsp;3. Changes in image statistical charcteristics  

Note --> While many metrics are computed, **recall** is the focus of the analysis because it most directly reflects the model’s ability to detect trees in modified imagery. Also, it was the core dignostic metric in the original Green City TPP development.

### How the Image Enhancement and Tree Point Prediction Components Interact:

&emsp;1. Image enhancement modifies the input chips.

&emsp;2. The frozen TPP model processes those chips.

&emsp;3. The evaluation process records how these modifications affect:  
&emsp;&emsp;&emsp;- Detection rate (recall) - the primary indicator of whether enhancements help the model “see” more trees.  
&emsp;&emsp;&emsp;- Spatial error - measures how close predicted tree locations are to the true points; ensures higher recall doesn’t come at the cost of inaccurate localization.  
&emsp;&emsp;&emsp;- Result stability - checks whether the model responds consistently across enhancement settings; distinguishes real improvements from sensitivity or brittleness.  
&emsp;&emsp;&emsp;- Metric drift or unexpected tradeoffs - where we get to get a sense for the true limits of the imagery and the safe operating range of enhancements.  This also highlights when improving one metric harms another.  


This setup creates a controlled way to study how specific changes in image quality influence a modern tree-point detector, without conflating results with model training dynamics.
### Pipelines at a Glance  

This repository combines two complementary components that work together in a closed loop of controlled experimentation.

&emsp;1. An **Image Enhancement (CVE)** pipeline that measures and modifies image quality.  
&emsp;2. A **Tree Point Prediction (TPP)** pipeline that serves as a frozen evaluator, or “meter.”  

CVE settings → enhanced chips → frozen TPP model → evaluation metrics → `results/`.

#### Image Enhancement Pipeline  

The `image_enhancement/` module implements a three-stage computer-vision enhancement (CVE) workflow:

&emsp;1. **Ingest**  
&emsp;&emsp;- Loads image chips and associated metadata.  
&emsp;&emsp;- Organizes inputs into a reproducible structure for analysis and enhancement.  

&emsp;2. **Analyze**  
&emsp;&emsp;- Computes five core metrics for each chip: contrast, brightness, sharpness, edge density, and centroid offset.  
&emsp;&emsp;- Flags chips that fall below quality thresholds or exhibit structural issues.  
&emsp;&emsp;- Produces a metrics DataFrame that can be filtered, grouped, and logged.  

&emsp;3. **Enhance**  
&emsp;&emsp;- Applies tunable combinations of contrast stretching, sharpening, gamma adjustment, brightness normalization, and centering or structural adjustments.  
&emsp;&emsp;- Supports parameter sweeps and sequencing experiments (CVE as data-level hyperparameters).  
&emsp;&emsp;- Writes enhanced chips and updated metrics to disk for downstream evaluation.  

For full details, see `image_enhancement/README.md`.  

#### Tree Point Prediction Pipeline  

The `tree_point_prediction/` module is adapted from the original Green City Tree Point Prediction (TPP) work. It contains:

- Training scripts for the underlying VGG-style SFANet model.  
- Inference scripts for running prediction over Pasadena tiles.  
- `evaluation-NEW-2.py` for computing detection and distance metrics.  

In this project, the TPP model is treated as a **frozen meter**. A single set of weights (the 15-epoch “best” run) is used as the canonical configuration:

- Recall: ~0.825  
- Precision: ~0.197  
- F1: ~0.318  
- Mean distance: ~4.9 m  

Those baseline numbers provide a reference point against which different CVE configurations are compared.  
Additional technical details live in `tree_point_prediction/README.md` and the upstream Green City TPP repository.  

---

### Metrics and Evaluation Methodology  

The evaluation stack measures how CVE settings affect model behavior without retraining the model.

#### Core Detection Metrics  

For each experiment, the TPP evaluator reports:

- Recall at 12 m (primary metric for this project)  
- True Positives (TP)  
- False Negatives (FN)  
- False Positives (FP)  
- Precision  
- F1 score  

These metrics are computed by matching predicted trees to ground-truth trees within a fixed radius and aggregating over all tiles.

Note → While many metrics are computed, **recall** is the primary focus because it most directly reflects the model’s ability to detect trees in modified imagery and was the key diagnostic metric in the original Green City TPP development.  

#### Spatial and Stability Metrics  

In addition to detection counts, the evaluator tracks:

- Average distance to closest matched tree  
- Distance distributions (histograms or density plots)  
- Recall vs. threshold curves  
- Optional: multi-run variance (e.g., repeated runs with the same CVE configuration)  

These metrics help distinguish:

- “More detections” vs. “sloppier detections” (higher recall but degraded localization), and  
- Genuine improvements vs. unstable or brittle behavior across runs.  

#### Metric Outputs  

Typical outputs include:

- A metrics table (for example, `evaluation_metrics.csv`) summarizing detection and distance statistics.  
- Plots written under `results/figures/`, such as:  
&emsp;- distance histograms  
&emsp;- recall vs. threshold curves  
&emsp;- comparative bar or line plots across CVE configurations  

These artifacts support both quantitative comparison and downstream reporting.  

---

### Experiment Workflow  

This section outlines how an experiment moves from raw chips to logged results.

&emsp;1. **Prepare Inputs**  
&emsp;&emsp;- Organize raw or enhanced chips and associated metadata.  
&emsp;&emsp;- Ensure paths in `image_enhancement/` and `tree_point_prediction/` are aligned.  

&emsp;2. **Run CVE Analysis and Enhancement**  
&emsp;&emsp;- Use the `image_enhancement` pipeline to compute quality metrics.  
&emsp;&emsp;- Select chips of interest (for example, failed or borderline cases).  
&emsp;&emsp;- Apply one or more CVE configurations (parameter sets and sequences).  

&emsp;3. **Stage Enhanced Chips for TPP**  
&emsp;&emsp;- Export enhanced chips into the directory expected by the TPP inference scripts.  
&emsp;&emsp;- Maintain consistent naming so evaluation can correctly match predictions to ground truth.  

&emsp;4. **Run Tree Point Prediction**  
&emsp;&emsp;- Execute the inference pipeline (directly or via `run_pipe.sh`) using the frozen 15-epoch weights.  
&emsp;&emsp;- Generate per-tile prediction outputs (for example, GeoJSON files).  

&emsp;5. **Run Evaluation**  
&emsp;&emsp;- Call `evaluation-NEW-2.py` to:  
&emsp;&emsp;&emsp;- merge predictions  
&emsp;&emsp;&emsp;- compute detection metrics  
&emsp;&emsp;&emsp;- compute distance statistics  
&emsp;&emsp;&emsp;- write metrics files and plots to `results/`  

&emsp;6. **Log the Experiment**  
&emsp;&emsp;- Append a row to `results/experiments.csv` capturing:  
&emsp;&emsp;&emsp;- experiment identifier  
&emsp;&emsp;&emsp;- CVE configuration (parameter values, sequence, data subset)  
&emsp;&emsp;&emsp;- key metrics (recall, precision, F1, mean distance, etc.)  
&emsp;&emsp;&emsp;- notes or observations, if relevant  

&emsp;7. **Compare Against Baseline**  
&emsp;&emsp;- Use plots and tables in `results/` to compare:  
&emsp;&emsp;&emsp;- new CVE runs vs. the raw-image baseline  
&emsp;&emsp;&emsp;- tradeoffs between recall, precision, and distance error  

This workflow is designed to be repeated as new CVE configurations are explored.  

---

### Key Findings (Living Section)  

This section is intended to evolve as experiments are completed. It summarizes what has been learned so far.

Current canonical baseline (frozen meter, 15-epoch weights):

- Model: Green City TPP (VGG-style SFANet)  
- Training: 15 epochs on Pasadena tiles  
- Baseline performance on raw imagery (approximate):  
&emsp;- Recall: ~0.825  
&emsp;- Precision: ~0.197  
&emsp;- F1: ~0.318  
&emsp;- Mean distance: ~4.9 m  

As experiments progress, this section will highlight:

- CVE configurations that consistently improve recall without unacceptable increases in distance error.  
- Cases where visually “better looking” images do not improve detection.  
- Regimes where aggressive enhancement harms performance.  
- Patterns linking changes in image metrics (sharpness, contrast, brightness, edge density, centroid offset) to changes in detection metrics.  

The goal is to move from individual runs to generalizable patterns about how image quality interacts with tree-point detection.  

---

### Results Gallery  

The `results/` directory serves as the visual record of the experiments.

Contents include:

- Before/after image pairs  
&emsp;- raw vs. enhanced chips  
&emsp;- examples of “rescued” failed or borderline chips  

- Metric plots  
&emsp;- per-run and comparative recall/precision/F1 summaries  
&emsp;- recall vs. threshold curves for different CVE configurations  

- Time and Tools Permitting --> Geospatial overlays  
&emsp;- qualitative examples of prediction overlays on imagery  
&emsp;- comparisons illustrating changes in detections or false positives 
<br>Note: currently exploring QGIS-like solutions

---

### How to Reproduce  

This section describes how to reproduce the experiments end-to-end.

#### Environment  

- Python 3.9 or later  
- GPU strongly recommended for TPP training and inference  
- Core libraries include (but are not limited to):  
&emsp;- PyTorch / TensorFlow (as required by the TPP implementation)  
&emsp;- OpenCV, NumPy, Pandas  
&emsp;- GeoPandas, Rasterio, Shapely  
&emsp;- Standard plotting libraries such as Matplotlib  

All required dependencies are listed in the project’s `requirements.txt` or environment configuration.  

#### Basic Steps  

&emsp;1. **Clone the repository**  
&emsp;&emsp;- Place this project alongside or as part of the Green City codebase, consistent with the paths expected by `tree_point_prediction/`.  

&emsp;2. **Prepare data**  
&emsp;&emsp;- Obtain the Pasadena Street ROW Trees dataset and associated NAIP imagery (or use provided samples under `data/` if available).  
&emsp;&emsp;- Configure file paths in both sub-readmes and scripts.  

&emsp;3. **Run baseline pipeline**  
&emsp;&emsp;- Use the TPP pipeline with raw imagery to reproduce the 15-epoch baseline metrics.  
&emsp;&emsp;- Confirm that results match (within reasonable tolerance) the baseline recall, precision, F1, and mean distance.  

&emsp;4. **Run CVE experiments**  
&emsp;&emsp;- Configure CVE parameters in the `image_enhancement` pipeline.  
&emsp;&emsp;- Generate enhanced chips and updated metrics.  
&emsp;&emsp;- Feed those chips into the TPP inference pipeline and evaluate with `evaluation-NEW-2.py`.  

&emsp;5. **Log and compare**  
&emsp;&emsp;- Append new runs to `results/experiments.csv`.  
&emsp;&emsp;- Use plots and tables to compare new runs against the baseline and against each other.  

---

### Citation and Acknowledgements  

This project builds on prior work from the [Green City team](https://github.com/antonioamartinez/Green-City) and publicly available data sources.

- Tree Point Prediction model and training framework adapted from the original Green City TPP implementation.  
- Data derived from the City of Pasadena Street ROW Trees dataset (Open Data 2.0) and NAIP aerial imagery.  
- Developed in the context of the UC Berkeley MIDS Capstone program.  

**toDo: add formal citation block**  
