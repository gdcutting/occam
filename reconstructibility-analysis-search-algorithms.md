# RA Algorithms

## Search
RA implements a number of different search algorithms:
* full searches starting from the top or bottom of the lattice
* up or down searches of loopless models (variable- and state-based versions)
* up or down searches of disjoint models
* chain search

```
Model **SearchFullDown::search(Model *start) {
    //-- worst case - need a list with a slot for each relation in start model,
    //-- plus one for null termination of list
    int relcount = start->getRelationCount();
    Model **models = new Model *[relcount + 1];
    Model *model;
    int i, slot;
    memset(models, 0, (relcount + 1) * sizeof(Model*));
    for (i = 0, slot = 0; i < relcount; i++) {
        Relation *rel = start->getRelation(i);
        //-- skip trivial relations
        if (rel->getVariableCount() == 1)
            continue;

        //-- for directed systems, skip any relations which only have independent vars
        if (isDirected() && rel->isIndependentOnly())
            continue;

        //-- otherwise this will generate a child relation
        model = ((VBMManager *) manager)->makeChildModel(start, i, 0, makeProjection());
        if (((VBMManager *) manager)->applyFilter(model))
            models[slot++] = model;
    }
    return models;
}
```
