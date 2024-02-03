#ifndef SHARED_LIBRARY_LIBRARY_H
#define SHARED_LIBRARY_LIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    void (*displayFunction)(void *);
    void (*exportFunction)(FILE *, void *);
    int (*compareFunction)(const void *, const void *);
} GenSetOperation;

typedef struct {
    size_t elementSize;
    size_t capacity;
    int size;
    void **elements;
    const GenSetOperation *operations;
} GenSet;

GenSet *initSet(size_t elementSize, const GenSetOperation *ops);
void deinitSet(GenSet *set);
void addToSet(GenSet *set, void *element);
void displaySet(GenSet *set);
GenSet *unionSet(const GenSet *set1, const GenSet *set2);
GenSet *intersectSet(const GenSet *set1, const GenSet *set2);
GenSet *diffSet(const GenSet *set1, const GenSet *set2);
int countSet(const GenSet *set);
bool isEmptySet(const GenSet *set);
bool isSubsetSet(const GenSet *set1, const GenSet *set2);
void export(const GenSet *set);

void displayInt(void *data);
void displayString(void *data);
void displayDouble(void *data);

int compareInt(const void *a, const void *b);
int compareString(const void *a, const void *b);
int compareDouble(const void *a, const void *b);

void exportInt(FILE *file, void *data);
void exportString(FILE *file, void *data);
void exportDouble(FILE *file, void *data);

#endif //SHARED_LIBRARY_LIBRARY_H
