//
// Created by 12adi on 25/05/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../Graph.h"

TEST_CASE("בדיקה של הוספת צלעות ב-Graph") {
    graph::Graph g(4);

    CHECK_NOTHROW(g.add_Edge(0, 1, 5));
    CHECK_NOTHROW(g.add_Edge(2, 3, 7));

    // בדיקה של חריגה עבור קודקודים לא חוקיים
    CHECK_THROWS(g.add_Edge(-1, 3, 2));
    CHECK_THROWS(g.add_Edge(4, 0, 1));  // מחוץ לתחום
}
