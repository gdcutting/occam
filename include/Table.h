/*
 * Copyright © 1990 The Portland State University OCCAM Project Team
 * [This program is licensed under the GPL version 3 or later.]
 * Please see the file LICENSE in the source
 * distribution of this software for license terms.
 */

#ifndef ___Table
#define ___Table

#include "Key.h"
#include "Constants.h"
#include "Globals.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Table - defines a data table, which is a collection of tuples. The tuples are stored
 * in a contiguous table.  Since tuples are variable sized, the Table object stores the
 * size information for the tuple storage.
 */

class Relation;

class Table {
    public:
        Table(int keysz, long long maxTuples, TableType typ = TableType:: InformationTheoretic); // initialize the table and allocate tuple space
        ~Table();
        long long size();

        void copy(const Table *from); // copy data table

        //-- add or sum tuples in the table.  These take into account the type of table
        //-- (info theoretic or set theoretic)
        void addTuple(KeySegment *key, double value); // append to end
        void insertTuple(KeySegment *key, double value, long long index); // insert in given spot
        void sumTuple(KeySegment *key, double value); // add (or) this value to matching tuple

        //-- key and value access functions
        double getValue(long long index);
        void setValue(long long index, double value);
        KeySegment *getKey(long long index);
        void copyKey(long long index, KeySegment *key);

        //-- find the given key. If matchOnly is true, -1 is returned on no match.
        //-- if matchOnly is false, the position of the next higher tuple is returned
        long long indexOf(KeySegment *key, bool matchOnly = true); //
        long long getTupleCount() {
            return tupleCount;
        }
        int getKeySize() {
            return keysize;
        }

        void sort(); // sort tuples by key
        void reset(int keysize); // reset table to empty, but reuse the storage

        // dump debug output
        void dump(bool detail = false);

        // normalize information-theoretic table.  No effect for set-theoretic tables.
        // if these are counts, then the return value is the sample size
        double normalize();

        // Add a constant to every value in the table.
        // This is used for function data, and it assumes that the table is fully specified.
        // i.e., it doesn't create missing tuples with assumed zero values, to add the constant to.
        void addConstant(double constant);

        // Returns the lowest value in the table.
        double getLowestValue();

    private:
        void* data; // storage for all keys and values
        int keysize; // number of key segments in the key for each tuple
        long long tupleCount; // number of tuples in the tuple array
        long long maxTupleCount; // the total size of the data member, in terms of tuples
        TableType type; // one of INFO_TYPE, SET_TYPE
};

template <typename F>
void tableIteration(Table* input_table, VariableList* varlist, Relation* rel,
                    Table* fit_table, Table* indep_table, 
                    long var_count, F action) {
    long long dataCount = input_table->getTupleCount();
    int *key_order = new int[dataCount];
    for (long long i = 0; i < dataCount; i++) { key_order[i] = i; }
    sort_var_list = varlist;
    sort_count = var_count;
    sort_vars = nullptr;
    sort_keys = nullptr;
    sort_table = input_table;
    qsort(key_order, dataCount, sizeof(int), sortKeys);
    if (fit_table == NULL) { fit_table = input_table; }
    if (indep_table == NULL) { indep_table = fit_table; }


    for (long long order_i = 0; order_i < dataCount; order_i++) {
        int i = key_order[order_i];
        KeySegment* refkey = input_table->getKey(i);
        double refvalue = input_table->getValue(i);
       
       
        long long vindex = fit_table->indexOf(refkey, true);
        double value = vindex == -1 ? 0.0 : fit_table->getValue(vindex);
        
        long long iviindex = indep_table->indexOf(refkey, true);
        double ivivalue = iviindex == -1 ? 0.0 : indep_table->getValue(iviindex);
         
        // disabled debug output
        //printf("VI: %d, V: %g, IVII: %d, IVIV: %g\n", vindex, value, iviindex, ivivalue);
        action(rel, value, refkey, refvalue, ivivalue);
    }
    delete[] key_order;
}


template <typename F> 
void tableKVIteration(Table* table, VariableList* varlist, long var_count, F action) {
    long long dataCount = table->getTupleCount();
    char* keystr = new char[var_count * MAXABBREVLEN + 1];
    int *key_order = new int[dataCount];
    for (long long i = 0; i < dataCount; i++) { key_order[i] = i; }
    sort_var_list = varlist;
    sort_count = var_count;
    sort_vars = nullptr;
    sort_keys = nullptr;
    sort_table = table;
    qsort(key_order, dataCount, sizeof(int), sortKeys);
    for (long long order_i = 0; order_i < dataCount; order_i++) {
        int i = key_order[order_i];
        KeySegment* key = table->getKey(i);
        double value = table->getValue(i);
        Key::keyToUserString(key, varlist, keystr);
        action(keystr, value);
    }

    delete[] keystr;
    delete[] key_order;

}

#endif
