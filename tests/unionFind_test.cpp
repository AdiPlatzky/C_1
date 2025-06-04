//
// 12adi45@gmail.com
//
#include "doctest.h"
#include "../UnionFind.h"
using namespace graph;
TEST_CASE("create basic UnionFind")
{
    UnionFind uf(5);
    for (int i = 0; i < 5; i++) {
        CHECK(uf.Find(i) == i);
    }
}
TEST_CASE("union && find of components") {
    UnionFind uf(5);
    uf.Union(0, 1);
    CHECK(uf.Connected(0, 1));
    CHECK(uf.Find(0) == uf.Find(1));

    uf.Union(1, 2);
    CHECK(uf.Connected(0,2));
    CHECK(uf.Find(0) == uf.Find(2));

    CHECK_FALSE(uf.Connected(0,3));
    uf.Union(3, 4);
    CHECK(uf.Connected(3,4));

    uf.Union(2,4);
    CHECK(uf.Connected(0,3));
    CHECK(uf.Find(1) == uf.Find(4));
}
