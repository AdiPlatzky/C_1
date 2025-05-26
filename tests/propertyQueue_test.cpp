//
// Created by 12adi on 26/05/2025.
//
#include "doctest.h"
#include "../PropertyQueue.h"

using namespace graph;
TEST_CASE("basic check of insert && extractMin") {
    PropertyQueue pq;

    Node_V* a= new Node_V(1);
    Node_V* b= new Node_V(2);
    Node_V* c= new Node_V(3);

    pq.insert(a,10,nullptr);
    pq.insert(b,20,nullptr);
    pq.insert(c,30,nullptr);

    CHECK_FALSE(pq.isEmpty());
    CHECK(pq.extractMin()->get_id() == 1);
    CHECK(pq.extractMin()->get_id() == 2);
    CHECK(pq.extractMin()->get_id() == 3);
    CHECK(pq.isEmpty());

    delete a;
    delete b;
    delete c;
}

TEST_CASE("decreaseKey check") {
    PropertyQueue pq;
    Node_V* a= new Node_V(1);
    Node_V* b= new Node_V(2);
    Node_V* c= new Node_V(3);

    pq.insert(a,30,nullptr);
    pq.insert(b,20,nullptr);
    pq.insert(c,40,nullptr);

    pq.decreaseKey(a,10,nullptr);

    CHECK(pq.extractMin()->get_id() == 1);

    delete a;
    delete b;
    delete c;
}

TEST_CASE("contains && getPatent check") {
    PropertyQueue pq;
    Node_V* a= new Node_V(1);
    Node_V* b= new Node_V(2);

    pq.insert(a,15,b);

    CHECK(pq.contains(a));
    CHECK_FALSE(pq.contains(b));
    CHECK(pq.getParent(a) == b);
    CHECK(pq.getParent(b) == nullptr);

    delete a;
    delete b;
}