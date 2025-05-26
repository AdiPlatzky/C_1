//
// Created by 12adi on 26/05/2025.
//
#include "doctest.h"
#include "../Queue.h"

using namespace graph;
TEST_CASE("create queue and make a base checks") {
    Queue q;
    CHECK(q.is_empty());
}
TEST_CASE("enqueue && dequeue") {
    Queue q;
    Node_V* a = new Node_V(1);
    Node_V* b = new Node_V(2);
    Node_V* c = new Node_V(3);

    q.enqueue(a);
    q.enqueue(b);
    q.enqueue(c);

    CHECK_FALSE(q.is_empty());
    CHECK(q.dequeue()->get_id() == 1);
    CHECK(q.dequeue()->get_id() == 2);
    CHECK(q.dequeue()->get_id() == 3);
    CHECK(q.is_empty());

    delete a;
    delete b;
    delete c;
}
TEST_CASE("throw errors when makes dequeue from empty queue") {
    Queue q;
    CHECK_THROWS(q.dequeue());
}
