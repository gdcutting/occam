# RA Algorithms

## Key objects in RA
For background on RA, see the [RA overview](reconstructibility-analysis-overview.md). That document is somewhat brief but contains links to more detailed introductions.

Very briefly, here is a quick recap of key RA concepts:
* Relation - (want to get a better definition here. I've been going through the various overview docs and 'relation' is used frequently but I don't see a definition anywhere so I want to clarify that.)
* Model - a calculated probability distribution over some sets of relations. Model distributions are calculated to maximize entropy while preserving constraints imposed by the marginal probabilities in the data. So, for example, given data ABCD, a candidate model might be AB:CD (AB and CD are each relations); this model would be calculated by maximizing entropy while preserving the marginal probabilities of the AB and CD projections.

## Search
RA provides a systematic way to generate candidate models of some data by enumerating a lattice of possible structures. A key part of the OCCAM machinery is to efficiently search this lattice and identify 'best' models, where fitness is judged according to various statistical and information-theoretic criteria. 

OCCAM implements a number of different search algorithms:
* full searches starting from the top or bottom of the lattice
* up or down searches of loopless models (variable- and state-based versions)
* up or down searches of disjoint models
* chain search

for a total of nine different search procedures. Not of all of them are equally common in OCCAM usage, so we will focus first on specifying the most commonly used searches (full up and down, and variable-based loopless).

All search algorithms implement a [beam search](https://en.wikipedia.org/wiki/Beam_search),
an optimization of [best first search](https://en.wikipedia.org/wiki/Best-first_search) that reduces its memory requirements.

### Full Down Search

Location: cpp/search.cpp(23-47)
Input: _start_, a model to begin the search from.

**SearchFullDown(start)**
```
1  relcount = start.getRelationCount()
2  models = new Model[relcount + 1]
3  allocate to _models_ a memory block of size (relcount + 1) * sizeof(Model), filled with zeros
4  slot = 0
5  for i = 0 to relcount - 1
6      start_rel = start.getRelation(i)
7      if (start_rel.getVariableCount() == 1)
8          continue
9      if system is directed and start_rel.isIndependentOnly()
10           continue
11      new_model = makeChildModel(start, i, o, makeProjection())
12      if model passes filter requirements
13          models[slot] = new_model
14          slot = slot + 1
15  return models
```

This procedure first sets _relcount_ to the count of relations in the starting model (1). Then it creates a Model array (with length (_relcount_ + 1)) to hold the search results (2), and allocates memory for that array (3). Slot, which is used as an array index for adding models to the _models_ array, is initialized to 0 (4). Then the procedure loops over the component relations in the starting model (for loop at line 5), and does the following at each iteration:
* if the variable count in the input relation _start_ is 1, do nothing (continue)
* if the system is directed and the input relation contains only independent variables, do nothing
* if neither of these sets of conditions is met, generate a new child model, new_model. If new_model passes some requirements specified by a filter (further note needed), add it to _models_ (the array containing models returned by the search)

When the for loop completes, _models_ is populated with zero or more models, the results of the search.
