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
#include "sub_tests/begin.test"
#include "sub_tests/end.test"

//iterator tests
//#include "sub_tests/iterators/operator_star.test"
//#include "sub_tests/iterators/operator_arrow.test"
//#include "sub_tests/iterators/operator_equals.test"
//#include "sub_tests/iterators/operator_does_not_equal.test"
//#include "sub_tests/iterators/operator_iterate_forward.test"


/*--------------- own tests -----------------------------------------------------------------------*/


// task 3.4
TEST_CASE("remove all elements with clear", "[clear]") {
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
TEST_CASE("copying all elements into another list", "[copy_constructor]") {

  SECTION("copy-construct an empty list and compare both lists") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    List<int> list2{list};
    REQUIRE(!(list2.empty()));
    REQUIRE(list2 == list);
    list2.clear();
    REQUIRE((list2.empty()));
  }

  SECTION("copy-construct a non empty list and compare both lists") {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    List<int> list2;
    list.push_front(8);
    list.push_front(7);
    list.push_front(6);
    list.push_front(5);
    List<int> list3{list};
    REQUIRE(!(list3.empty()));
    REQUIRE(list3 == list);
    list3.clear();
    REQUIRE((list3.empty()));
  }
} 


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
}


// task 3.7
TEST_CASE("member-reverse the order of a list", "[member_reverse]") {
  List<int> list1{};
  List<int> list2{};

  SECTION("reverse a list of 1 element") {
    list1.push_back(1);
    list2.push_back(1);
    list1.reverse();
    list2.reverse();
    REQUIRE(list1 == list2);
  }

  SECTION("reverse a list of 2 elements") {
    list1.push_back(1);
    list1.push_back(3);
    list2.push_back(3);
    list2.push_back(1);
    list2.reverse();
    REQUIRE(list1 == list2);
  }

  SECTION("reverse a list of more than 2 elements") {
    list1.push_back(3);
    list1.push_back(4);
    list1.push_back(5);
    list1.push_back(6);
    list1.push_back(7);
    list1.push_back(8);
    list2.push_back(8);
    list2.push_back(7);
    list2.push_back(6);
    list2.push_back(5);
    list2.push_back(4);
    list2.push_back(3);
    list2.reverse();
    REQUIRE(list1 == list2);
    list2.reverse();
    list1.reverse();
    REQUIRE(list1 == list2);
    list2.reverse();
    list1.reverse();
    REQUIRE(list1 == list2);
  }
}


// task 3.7
TEST_CASE("free-reverse the order of a list", "[free_reverse]") {
  List<int> list{};
  List<int> list2{};


  SECTION("free-reverse a list of 2 elements") {
     list.push_back(1);
     list.push_back(3);
    list2.push_back(3);
    list2.push_back(1);
    REQUIRE((list == reverse(list2)));
  }

  SECTION("free-reverse a list of more than 2 elements") {
     list.push_back(3);
     list.push_back(4);
     list.push_back(5);
     list.push_back(6);
     list.push_back(7);
     list.push_back(8);
    list2.push_back(8);
    list2.push_back(7);
    list2.push_back(6);
    list2.push_back(5);
    list2.push_back(4);
    list2.push_back(3);
    REQUIRE((list == reverse(list2)));
    REQUIRE((reverse(list) == (list2)));
    REQUIRE(((list) == reverse(list2)));
  }
}


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


// task 3.9
TEST_CASE("move all elements from rhs to a new list", "[move-constructor]") {
  List<int> list; 
  list.push_front(1); 
  list.push_front(2); 
  list.push_front(3); 
  list.push_front(4);
  List<int> list2 = std::move(list); 
  REQUIRE(0 == list.size()); 
  REQUIRE(list.empty());
  REQUIRE(4 == list2.size()); 
}

/*
// task 3.10
TEST_CASE("initializer list constructor", "[init-constructor]") {
  List<int> int_list{9, 5, 38, 100};
}*/


int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}




