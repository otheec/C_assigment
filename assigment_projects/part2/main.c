#include <stdio.h>
#include "library/library.h"

#define STRING_LENGTH 65

int main() {
    GenSetOperation intOperations = {displayInt, exportInt, compareInt};
    GenSetOperation doubleOperations = {displayDouble, exportDouble, compareDouble};
    GenSetOperation stringOperations = {displayString, exportString, compareString};

    GenSet *intSet = initSet(sizeof(int), &intOperations);
    GenSet *intSet2 = initSet(sizeof(int), &intOperations);
    GenSet *doubleSet = initSet(sizeof(double), &doubleOperations);
    GenSet *stringSet = initSet(sizeof(char) * STRING_LENGTH, &stringOperations);
    GenSet *stringSet2 = initSet(sizeof(char) * STRING_LENGTH, &stringOperations);

    addToSet(intSet, &(int){1});
    addToSet(intSet, &(int){2});
    addToSet(intSet, &(int){3});
    addToSet(intSet, &(int){4});

    addToSet(intSet2, &(int){3});
    addToSet(intSet2, &(int){4});
    addToSet(intSet2, &(int){5});
    addToSet(intSet2, &(int){6});

    addToSet(doubleSet, &(double){1.5});
    addToSet(doubleSet, &(double){2.5});
    addToSet(doubleSet, &(double){3.5});
    addToSet(doubleSet, &(double){4.5});

    addToSet(stringSet, "Hello");
    addToSet(stringSet, "Adios");
    addToSet(stringSet, "Buenos Dias");
    addToSet(stringSet, "Hola");

    addToSet(stringSet2, "Hello");
    addToSet(stringSet2, "Ciao");
    addToSet(stringSet2, "Adios");

    printf("intSet: ");
    displaySet(intSet);

    printf("intSet2: ");
    displaySet(intSet2);

    printf("intSet size: %d\n", countSet(intSet));
    printf("intSet is empty: %s\n", isEmptySet(intSet) ? "true" : "false");

    printf("doubleSet: ");
    displaySet(doubleSet);
    printf("stringSet: ");
    displaySet(stringSet);

    printf("Test of union of intSet and doubleSet: ");
    GenSet *intUnionError = unionSet(intSet, doubleSet);

    GenSet *intUnionResult = unionSet(intSet, intSet2);
    printf("Int Union: ");
    displaySet(intUnionResult);

    GenSet *intIntersectResult = intersectSet(intSet, intSet2);
    printf("Int Intersection: ");
    displaySet(intIntersectResult);

    GenSet *stringIntersectResult = intersectSet(stringSet, stringSet2);
    printf("String Intersect: ");
    displaySet(stringIntersectResult);

    GenSet *intDiff = diffSet(intSet, intSet2);
    printf("Int Difference: ");
    displaySet(intDiff);

    export(stringSet);

    printf("Int Subset: %s", isSubsetSet( intDiff, intSet) ? "true" : "false");

    deinitSet(intSet);
    deinitSet(doubleSet);
    deinitSet(stringSet);
    deinitSet(intUnionResult);
    deinitSet(intIntersectResult);
    deinitSet(intDiff);
    deinitSet(intSet2);
    deinitSet(stringSet2);

    return 0;
}
