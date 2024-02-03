#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "library.h"

GenSet *initSet(size_t elementSize, const GenSetOperation *ops) {
    GenSet *set = (GenSet *)malloc(sizeof(GenSet));

    set->elementSize = elementSize;
    set->capacity = 2;
    set->size = 0;
    set->operations = ops;
    set->elements = (void **)malloc(set->capacity * sizeof(void *));

    return set;
}

void deinitSet(GenSet *set) {
    for (size_t i = 0; i < set->size; ++i) {
        free(set->elements[i]);
    }
    free(set->elements);
    free(set);
}

void addToSet(GenSet *set, void *element) {
    for (size_t i = 0; i < set->size; ++i) {
        if (set->operations->compareFunction(set->elements[i], element) == 0) {
            return;
        }
    }

    if (set->size == set->capacity) {
        set->capacity += 2;
        set->elements = realloc(set->elements, set->capacity * sizeof(void *));
        if (set->elements == NULL) {
            printf("Error in resizing set");
        }
    }

    set->elements[set->size] = malloc(set->elementSize);

    memcpy(set->elements[set->size], element, set->elementSize);

    set->size++;
}

void displaySet(GenSet *set) {
    const GenSetOperation *ops = set->operations;
    ops->displayFunction(set->elements[0]);
    for (size_t i = 1; i < set->size; ++i) {
        printf(", ");
        ops->displayFunction(set->elements[i]);
    }
    printf("\n");
}

GenSet *unionSet(const GenSet *set1, const GenSet *set2) {
    if(set1->operations != set2->operations){
        printf("Defferent datatypes\n");
        return NULL;
    }

    GenSet *result = initSet(set1->elementSize, set1->operations);

    for (size_t i = 0; i < set1->size; ++i) {
        addToSet(result, set1->elements[i]);
    }

    for (size_t i = 0; i < set2->size; ++i) {
        addToSet(result, set2->elements[i]);
    }

    return result;
}

GenSet *intersectSet(const GenSet *set1, const GenSet *set2) {
    if(set1->operations != set2->operations){
        printf("Defferent datatypes\n");
        return NULL;
    }

    GenSet *result = initSet(set1->elementSize, set1->operations);

    for (size_t i = 0; i < set1->size; ++i) {
        for (size_t j = 0; j < set2->size; ++j) {
            if (set1->operations->compareFunction(set1->elements[i], set2->elements[j]) == 0) {
                addToSet(result, set1->elements[i]);
                break;
            }
        }
    }

    return result;
}

GenSet *diffSet(const GenSet *set1, const GenSet *set2) {
    if(set1->operations != set2->operations){
        printf("Defferent datatypes\n");
        return NULL;
    }

    GenSet *result = initSet(set1->elementSize, set1->operations);

    for (size_t i = 0; i < set1->size; ++i) {
        int isCommon = 0;
        for (size_t j = 0; j < set2->size; ++j) {
            if (set1->operations->compareFunction(set1->elements[i], set2->elements[j]) == 0) {
                isCommon = 1;
                break;
            }
        }
        if (!isCommon) {
            addToSet(result, set1->elements[i]);
        }
    }

    return result;
}

int countSet(const GenSet *set) {
    return set->size;
}

bool isSubsetSet(const GenSet *set1, const GenSet *set2) {
    const GenSetOperation *ops = set1->operations;
    int commonCounter = set1->size;

    for (size_t i = 0; i < set1->size; ++i) {
        for (size_t j = 0; j < set2->size; ++j) {
            if (ops->compareFunction(set1->elements[i], set2->elements[j]) == 0) {
                commonCounter--;
                break;
            }
        }
    }

    return !commonCounter;
}

bool isEmptySet(const GenSet *set) {
    return set->size == 0;
}

void export(const GenSet *set) {
    FILE *file = fopen("exported_set.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
    }

    for (size_t i = 0; i < set->size; ++i) {
        set->operations->exportFunction(file, set->elements[i]);
        fprintf(file, "\n");
    }

    fclose(file);
}

void displayInt(void *data) {
    printf("%d", *((int *)data));
}

void displayString(void *data) {
    printf("%s", (char *)data);
}

void displayDouble(void *data) {
    printf("%lf", *((double *)data));
}

int compareInt(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

int compareString(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int compareDouble(const void *a, const void *b) {
    double diff = *((double *)a) - *((double *)b);
    return (diff > 0) ? 1 : ((diff < 0) ? -1 : 0);
}

void exportInt(FILE *file, void *data) {
    fprintf(file, "%d", *((int *)data));
}

void exportString(FILE *file, void *data) {
    fprintf(file, "%s", (char *)data);
}

void exportDouble(FILE *file, void *data) {
    fprintf(file, "%lf", *((double *)data));
}
