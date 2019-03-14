# Recontructibility Analysis (RA) Overview]

This article is intended as a *brief* overview of Reconstructibility Analysis (RA), the analytical method implemented in OCCAM. For more detailed introductions, see the [Discrete Multivariate Modeling research page](https://www.pdx.edu/sysc/research-discrete-multivariate-modeling), in particular:
* [An Overview Of Reconstructibility Analysis](]https://www.pdx.edu/sysc/sites/www.pdx.edu.sysc/files/overview.pdf)
* [Wholes and Parts in General Systems Methodology](https://www.pdx.edu/sysc/sites/www.pdx.edu.sysc/files/wholesg.pdf)
* [Using Information Theory to Find Relationships in Data](https://www.pdx.edu/sysc/sites/www.pdx.edu.sysc/files/2013_SySc_Using_Info_Th_0.pdf)

RA is a discrete multivariate modeling methodology, developed in the systems community, which partly overlaps log-linear statistical methods used in the social sciences and also resembles methods used in logic design. Though much of the method was developed before the explosion of machine learning (ML) methods in the last couple of decades, RA strongly overlaps with ML methods as well. It can be used for data mining (identifying patterns in large datasets). It is also a powerful dimensionality reduction method - an essential component of RA is identifying simplified, or reduced-complexity, models which preserve essential features and relationships from the data. RA can be used for feature selection, and pre-structuring inputs for Neural Networks (NNs), Genetic Algorithms, and other methods (see under "Neural Net and genetic algorithm preprocessing" at the [DMM research page](https://www.pdx.edu/sysc/research-discrete-multivariate-modeling).


## RA Data Types

RA applies to multivariate data involving nominal variables  or quantitative variables which are converted into nominal
variables by being discretized.  Variables need not be binary (dichotomous) but can be multi-valued.  Nominal variables,
whose states are discrete and unordered, are the most general type of variable, and so methods which apply to
them encompass ordinal and quantitative variables as well. Continuous quantitative variables can be discretized either
by quantization (non-overlapping binning intervals) or by fuzzification (Zadeh, 1965; Cellier et al, 1995).


## System Types (Directed or Neutral)

RA can be used to analyze neutral or directed systems. In a *directed* system, inputs and outputs ("independent"  and "dependent"
variables) are distinguished.  While most RA applications involve predictive, dynamic, or causal (hence directed) relationships between variables, sometimes variables have equal status; these are *neutral* systems.

## Data Types (Information-theoretic and Set-theoretic)

RA has two versions: a version which applies to set-theoretic relations and mappings, and an information-theoretic (probabilistic) version which applies to frequency and probability distributions. Information-theoretic RA (IRA) is the most commonly used version, so we will focus on it in this introduction.

The same model structures are considered in both IRA and SRA (Set-theoretic RA). Let ABC represent a probability or frequency distribution (IRA) or a set-theoretic relation or mapping (SRA) for a three-variable system, with projections AB, AC, and BC, and A, B, and C. Define a structure as a non-redundant set of projections [GDC note: this language needs to be clarified, and this definition made more formal], and the "lattice of structures" as the set of all possible structures containing these variables or subsets of them (again, this needs to be clarified).

At the top of the lattice of structures is the data, also called the "saturated model" (denoted in this example by **ABC***). At the bottom of the lattice is the independence model, denoted by **A:B:C** (in IRA, one can go further down the lattice to the uniform distribution, but the independence model is usually considered as the bottom model in the lattice).

![Lattice of specific structures for a three-variable neutral system](images/3-variable-neutral-lattice.png)

The size of the lattice increases very rapidly with the number of variables...

OCCAM implements search methods to efficiently explore the lattice of possible structures and select candidate models from the (potentially very large) space of possible models for a given dataset.
