# Image Enhancement (CVE) Pipeline  

This directory contains the computer-vision enhancement (CVE) pipeline used in the  
**“Image Quality as a Hyperparameter”** capstone project.  

The goal of this module is to:  

- quantify image quality using interpretable metrics, and  
- apply targeted enhancement operations to improve model readiness,  
- while keeping the downstream tree-point detection model completely frozen.  

For the broader experimental context, see the main project README at the repository root.  

---

## Pipeline Overview  

The image enhancement workflow follows a three-stage pattern:  

&emsp;Coordinate / chip list  
&emsp;&emsp;↓  
&emsp;[INGEST] → raw image chips  
&emsp;&emsp;↓  
&emsp;[ANALYZE] → quality metrics + flags  
&emsp;&emsp;↓  
&emsp;[ENHANCE] → enhanced chips + new metrics  

In this continuation capstone, the emphasis is on:  

- treating enhancement parameters, sequences, and combinations as **data-level hyperparameters**, and  
- measuring how those choices affect downstream detection performance in a frozen evaluator model.  

---

## Stages  

### 1. INGEST  

**Purpose**  
Load and organize image chips and supporting metadata so they can be analyzed and enhanced in a reproducible way.  

**Key actions**  

- Read chip files and any associated coordinate or ID information.  
- Normalize directory structure and filenames for consistent downstream use.  
- Validate that chips match expected dimensions and formats.  

Typical output: a clean set of image chips on disk plus a reference table of IDs and paths.  

---

### 2. ANALYZE  

**Purpose**  
Compute image quality metrics and identify chips that are strong, borderline, or in need of enhancement.  

**Metrics computed (per chip)**  

- contrast  
- brightness  
- sharpness  
- edge density  
- centroid offset (alignment between canopy and chip center)  

**Key actions**  

- Measure each chip using the metrics above.  
- Flag chips that fall outside acceptable ranges (for example, low sharpness or extreme brightness).  
- Produce a metrics DataFrame that can be filtered, grouped, and exported.  

Typical output: a metrics table (for example, a CSV or DataFrame) plus tags indicating which chips are candidates for enhancement.  

---

### 3. ENHANCE  

**Purpose**  
Apply tunable CVE operations to improve model readiness of chips, especially those that failed one or more quality checks.  

**Core operations**  

- contrast stretching / boosting  
- sharpening  
- gamma correction  
- brightness normalization  
- centering / structural adjustments  

**Key capabilities**  

- Run single enhancements or **combinations** (stacks) of enhancements.  
- Vary strength and sequencing of operations as experimental knobs.  
- Save enhanced chips to a new output directory, preserving traceable naming.  
- Recompute metrics for enhanced chips for before/after comparison.  

Typical output: a parallel set of enhanced chips and updated metrics suitable for feeding into the tree-point prediction pipeline.  

---

## Role in the Capstone  

In the main capstone project, this module serves as the **input-side experimental surface**.  

- The model remains fixed (frozen evaluator).  
- This pipeline changes only the input images.  
- Enhancement parameters and sequences act as **input-space hyperparameters**.  

By varying these settings and measuring their effects on recall, localization error, and stability, the project studies **how far careful image engineering alone can push performance**.  

---

## Relationship to Prior Work  

This continuation capstone builds on an earlier GreenCity image enhancement pipeline that was developed as a standalone CV module.  

For a broader description of the original image enhancement work, including additional context and examples, see:  

- Original GreenCity image enhancement documentation (link to prior repo or branch)  
    - [GreenCity CV Pipeline (original)](https://github.com/antonioamartinez/Green-City/tree/main/image_enhancement)  



---


