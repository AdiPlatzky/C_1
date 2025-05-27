//
// Created by 12adi on 26/05/2025.
//
#include "doctest.h"
#include "../PropertyQueue.h"

using namespace graph;

TEST_SUITE("PropertyQueue Edge Cases")
{
    TEST_CASE("basic check of insert && extractMin")
    {
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

    TEST_CASE("decreaseKey check")
    {
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

    TEST_CASE("contains && getPatent check")
    {
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

    TEST_CASE("Empty queue operations")
    {
        PropertyQueue pq;

        CHECK(pq.isEmpty());
        CHECK_THROWS(pq.extractMin());

        Node_V* dummy = new Node_V(1);
        CHECK_FALSE(pq.contains(dummy));
        CHECK(pq.getParent(dummy) == nullptr);

        delete dummy;
    }

    TEST_CASE("Same priority elements")
    {
        PropertyQueue pq;
        Node_V* a = new Node_V(1);
        Node_V* b = new Node_V(2);
        Node_V* c = new Node_V(3);

        // הוסף עם אותו עדיפות
        pq.insert(a, 10, nullptr);
        pq.insert(b, 10, nullptr);
        pq.insert(c, 10, nullptr);

        // בדוק שכולם בתור
        CHECK(pq.contains(a));
        CHECK(pq.contains(b));
        CHECK(pq.contains(c));

        // הוצא והבטח שהתור עדיין עובד
        Node_V* first = pq.extractMin();
        CHECK((first == a || first == b || first == c));

        CHECK_FALSE(pq.isEmpty());

        delete a; delete b; delete c;
    }

    TEST_CASE("Decrease key to same value")
    {
        PropertyQueue pq;
        Node_V* a = new Node_V(1);

        pq.insert(a, 20, nullptr);

        // נסה להקטין למותו ערך
        pq.decreaseKey(a, 20, nullptr);

        CHECK(pq.contains(a));
        CHECK(pq.extractMin() == a);

        delete a;
    }

    TEST_CASE("Decrease key with invalid node")
    {
        PropertyQueue pq;
        Node_V* a = new Node_V(1);
        Node_V* b = new Node_V(2);

        pq.insert(a, 10, nullptr);

        // נסה להקטין ערך של node שלא בתור
        CHECK_NOTHROW(pq.decreaseKey(b, 5, nullptr));

        // a עדיין צריך להיות בתור
        CHECK(pq.contains(a));
        CHECK_FALSE(pq.contains(b));

        delete a; delete b;
    }

    // TEST_CASE("Large queue stress test")
    // {
    //     PropertyQueue pq;
    //     std::vector<Node_V*> nodes;
    //
    //     // צור 1000 nodes
    //     for(int i = 0; i < 1000; i++) {
    //         nodes.push_back(new Node_V(i));
    //         pq.insert(nodes[i], 1000 - i, nullptr);  // עדיפות הפוכה
    //     }
    //
    //     // בדוק שהתור מוציא בסדר הנכון
    //     for(int i = 999; i >= 0; i--) {
    //         Node_V* extracted = pq.extractMin();
    //         CHECK(extracted->get_id() == i);
    //     }
    //
    //     CHECK(pq.isEmpty());
    //
    //     // נקה זיכרון
    //     for(Node_V* node : nodes) {
    //         delete node;
    //     }
    // }
}