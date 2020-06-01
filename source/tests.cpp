#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include "list.hpp"


// Hilfsfunktionen, um indirekt auf die Member der Klasse List zuzugreifen (nur für die Tests!)
template <typename T>
size_t get_size(List<T> const& list_to_test) {return list_to_test.size_;}

template <typename T>
ListNode<T>* get_first_pointer(List<T> const& list_to_test) {return list_to_test.first_;}

template <typename T>
ListNode<T>* get_last_pointer(List<T> const& list_to_test) {return list_to_test.last_;}


//test case definitions for default constructor of list as well as empty and size for empty list
#include "sub_tests/default_constructed_list.test"

//test case definitions for push methods of list
#include "sub_tests/push_front.test"
#include "sub_tests/push_back.test"

//test case definitions for pop methods of list
#include "sub_tests/pop_front.test"
#include "sub_tests/pop_back.test"

//test cases for element access of list
#include "sub_tests/front.test"
#include "sub_tests/back.test"

//test cases for retrieving iterators
//#include "sub_tests/begin.test"
//#include "sub_tests/end.test"

//iterator tests
//#include "sub_tests/iterators/operator_star.test"
//#include "sub_tests/iterators/operator_arrow.test"
//#include "sub_tests/iterators/operator_equals.test"
//#include "sub_tests/iterators/operator_does_not_equal.test"
//#include "sub_tests/iterators/operator_iterate_forward.test"


/*--------------- own tests -----------------------------------------------------------------------*/

// task 3.4
TEST_CASE("remove all elements with clear", "[list_modifier]") {
  List<int> list{};

  SECTION("4 elements to be cleared") {
    list.push_back(5);
    list.push_back(6);
    list.push_back(8);
    list.push_back(9);
    list.clear();
    REQUIRE(list.empty());
  }

  SECTION("1 element to be cleared") {
    list.push_back(3);
    list.clear();
    REQUIRE(list.empty());
  }
    
  SECTION("0 elements to be cleared") {
    list.clear();
    REQUIRE(list.empty());
  }

}

// task 3.5
/*
TEST_CASE("copying all elements into another list", "[copy_constructor]") {
      List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    List<int> list2{list};
    REQUIRE(!(list2.empty()));
} */

/*
// task 3.6
TEST_CASE("check unifying copy-and-swap assignment operator", "[operator=]") {
  List<int> list{};
  list.push_back(5);
  list.push_back(6);
  list.push_back(8);
  list.push_back(9);
  List<int> list2{};
  list = list2;
  REQUIRE(list == list2);
}*/


// task 3.8
TEST_CASE("Check lists for equality and inequality", "[compare]") {
  List<int> list1{};
  list1.push_front(1);
  list1.push_front(2);
  list1.push_front(3);
  list1.push_front(4);
  List<int> list2{};
  list2.push_front(1);
  list2.push_front(2);
  list2.push_front(3);
  list2.push_front(4);
  List<int> list3{};
  list3.push_front(1);
  list3.push_front(2);

  SECTION("Check lists for equality") {
    REQUIRE((list1 == list2) == true);
    REQUIRE((list2 == list1) == true);
    REQUIRE((list1 == list3) == false);
    REQUIRE((list2 == list3) == false);
  }

  SECTION("Check lists for inequality") {
    REQUIRE((list1 != list3) == true);
    REQUIRE((list2 != list3) == true);
    REQUIRE((list1 != list2) == false);
    REQUIRE((list2 != list1) == false);
  }

}


int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}




