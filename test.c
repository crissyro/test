#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "libs/algorithms/array/array.h"
#include "libs/data_structures/unorderedset.h"

void test_unordered_array_set_in() {
    unordered_array_set set = unordered_array_set_create(3);
    unordered_array_set_insert(&set, 3);
    unordered_array_set_insert(&set, 1);
    unordered_array_set_insert(&set, 2);

    size_t position = unordered_array_set_in(&set, 2);
    assert(position != set.size);

    size_t notInSet = unordered_array_set_in(&set, 4);
    assert(notInSet == set.size);

    unordered_array_set_delete(set);
}

void test_unordered_array_set_isSubset() {
    unordered_array_set set1 = unordered_array_set_create(3);
    unordered_array_set_insert(&set1, 2);
    unordered_array_set_insert(&set1, 3);
    unordered_array_set_insert(&set1, 1);

    unordered_array_set set2 = unordered_array_set_create(2);
    unordered_array_set_insert(&set2, 2);
    unordered_array_set_insert(&set2, 3);

    size_t isSubset = unordered_array_set_isSubset(set2, set1);
    assert(isSubset != set2.size);

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
}

void test_unordered_array_set_insert() {
    unordered_array_set set = unordered_array_set_create(3);
    unordered_array_set_insert(&set, 3);
    unordered_array_set_insert(&set, 1);
    unordered_array_set_insert(&set, 2);

    size_t position = unordered_array_set_in(&set, 2);
    assert(position != set.size);

    unordered_array_set_delete(set);
}

void test_unordered_array_set_deleteElement() {
    unordered_array_set set = unordered_array_set_create(3);
    unordered_array_set_insert(&set, 3);
    unordered_array_set_insert(&set, 1);
    unordered_array_set_insert(&set, 2);

    unordered_array_set_deleteElement(&set, 2);
    size_t position = unordered_array_set_in(&set, 2);
    assert(position == set.size);

    unordered_array_set_delete(set);
}

void test_unordered_array_set_union() {
    unordered_array_set set1 = unordered_array_set_create(3);
    unordered_array_set_insert(&set1, 3);
    unordered_array_set_insert(&set1, 1);
    unordered_array_set_insert(&set1, 2);

    int array2[] = {2, 3, 4, 5};
    unordered_array_set set2 = unordered_array_set_create_from_array(array2, 4);

    unordered_array_set set_union = unordered_array_set_union(set1, set2);
    assert(set_union.size == 5);

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(set_union);
}

void test_unordered_array_set_intersection() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){2, 1, 3, 4}, 4);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){3, 4, 6, 5}, 4);

    unordered_array_set set_intersection = unordered_array_set_intersection(set1, set2);
    assert(set_intersection.size == 2);

    assert(unordered_array_set_in(&set_intersection, 2));
    assert(unordered_array_set_in(&set_intersection, 4));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(set_intersection);
}

void test_unordered_array_set_difference() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){4, 2, 3, 1}, 4);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){6, 4, 5, 3}, 4);

    unordered_array_set set_difference = unordered_array_set_difference(set1, set2);
    assert(set_difference.size == 2);

    unordered_array_set expected_set = unordered_array_set_create_from_array((int[]){2, 1}, 2);
    assert(unordered_array_set_isEqual(set_difference, expected_set));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(set_difference);
    unordered_array_set_delete(expected_set);
}

void test_unordered_array_set_symmetricDifference() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){4, 2, 3, 1}, 4);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){6, 4, 5, 3}, 4);

    unordered_array_set set_symmetric_difference = unordered_array_set_symmetricDifference(set1, set2);
    assert(set_symmetric_difference.size == 4);

    unordered_array_set expected_set = unordered_array_set_create_from_array((int[]){2, 1, 6, 5}, 4);
    assert(unordered_array_set_isEqual(set_symmetric_difference, expected_set));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(set_symmetric_difference);
    unordered_array_set_delete(expected_set);
}

void test_unordered_array_set_complement() {
    unordered_array_set set1 = unordered_array_set_create_from_array((int[]){2, 1, 3, 4}, 4);
    unordered_array_set set2 = unordered_array_set_create_from_array((int[]){3, 4, 6, 5}, 4);

    unordered_array_set set_complement = unordered_array_set_complement(set1, set2);
    assert(set_complement.size == 2);

    unordered_array_set expected_set = unordered_array_set_create_from_array((int[]){6, 5}, 2);
    assert(unordered_array_set_isEqual(set_complement, expected_set));

    unordered_array_set_delete(set1);
    unordered_array_set_delete(set2);
    unordered_array_set_delete(set_complement);
    unordered_array_set_delete(expected_set);
}

void test () {
    test_unordered_array_set_in () ;
    test_unordered_array_set_isSubset () ;
    test_unordered_array_set_insert () ;
    test_unordered_array_set_deleteElement () ;
    test_unordered_array_set_union () ;
    test_unordered_array_set_intersection () ;
    test_unordered_array_set_difference () ;
    test_unordered_array_set_symmetricDifference () ;
    test_unordered_array_set_complement () ;
}

#include <stdio.h>

int main() {

    test();

    return 0;
}