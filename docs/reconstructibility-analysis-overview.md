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
