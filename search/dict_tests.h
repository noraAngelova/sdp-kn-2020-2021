#include <fstream>

TEST_CASE_TEMPLATE("Search in an empty dictionary", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  CHECK(dict.lookup(1) == nullptr);
}

TEST_CASE_TEMPLATE("Add a single element in an empty dictionary", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  REQUIRE(dict.add(1, 10));
  int* val = dict.lookup(1);
  REQUIRE(val != nullptr);
  CHECK_EQ(*val, 10);
}

TEST_CASE_TEMPLATE("Remove the last element in a dictionary", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  REQUIRE(dict.add(1, 10));
  REQUIRE(dict.remove(1));
  CHECK(dict.lookup(1) == nullptr);
}

TEST_CASE_TEMPLATE("Add many elements in a dictionary and look them up", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 4})
    REQUIRE(dict.add(i, i * 10));

  for (int i : {6, 3, 4, 1, 2}) {
    int *val = dict.lookup(i);
    CHECK(val != nullptr);
    CHECK_EQ(*val, i * 10);
  }

  for (int i : {0, 5, 10})
    CHECK(dict.lookup(i) == nullptr);
}

TEST_CASE_TEMPLATE("Remove some added elements in a dictionary and try to look them up", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 4})
    REQUIRE(dict.add(i, i * 10));

  for (int i : {3, 4, 1})
    REQUIRE(dict.remove(i));

  for (int i : {1, 3, 4})
    CHECK(dict.lookup(i) == nullptr);

  for (int i : {2, 6}) {
    int *val = dict.lookup(i);
    CHECK(val != nullptr);
    CHECK_EQ(*val, i * 10);
  }
}

TEST_CASE_TEMPLATE("Enumerate keys", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 5, 4})
    REQUIRE(dict.add(i, i * 10));
  int i = 1;
  for(int key : dict.keys())
    CHECK(key == i++);
}

TEST_CASE_TEMPLATE("Enumerate values", TestDictionary, TEST_BOTH) {
  TestDictionary dict;
  for (int i : {1, 3, 6, 2, 5, 4})
    REQUIRE(dict.add(i, i * 10));
  int i = 10;
  for(int value : dict.values()) {
    CHECK(value == i);
    i += 10;
  }
}
