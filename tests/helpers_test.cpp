//
// Created by 12adi on 26/05/2025.
//
#include "doctest.h"
#include "../Helpers.h"

using namespace graph;
struct DummyNode {
    int value;
    DummyNode* next;

    DummyNode(int val) : value(val), next(nullptr) {}
};

TEST_CASE("is in bounds")
{
    CHECK(isInBounds(5,1,10));
    CHECK(isInBounds(1,1,10));
    CHECK(isInBounds(10,1,10));
    CHECK_FALSE(isInBounds(0,1,10));
    CHECK_FALSE(isInBounds(11,1,10));
}

TEST_CASE("delete and advance") {
    DummyNode* n1 = new DummyNode(1);
    DummyNode* n2 = new DummyNode(2);
    DummyNode* n3 = new DummyNode(3);
    n1->next = n2;
    n2->next = n3;

    DummyNode* current = n1;

    CHECK(current->value == 1);
    deleteAndAdvance(current);
    CHECK(current->value == 2);
    deleteAndAdvance(current);
    CHECK(current->value == 3);
    deleteAndAdvance(current);
    CHECK(current == nullptr);
}