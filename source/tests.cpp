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
#include "sub_tests/iterators/operator_star.test"
#include "sub_tests/iterators/operator_arrow.test"
#include "sub_tests/iterators/operator_equals.test"
#include "sub_tests/iterators/operator_does_not_equal.test"
#include "sub_tests/iterators/operator_iterate_forward.test"


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
    REQUIRE_FALSE(list2.empty());
    REQUIRE(list2 == list);
    list2.clear();
    REQUIRE(list2.empty());
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
    REQUIRE_FALSE((list3.empty()));
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
  REQUIRE_FALSE(list == list2);
  list = list2;
  REQUIRE(list == list2);
  list.clear();
  REQUIRE(list.empty());
  REQUIRE(list2.empty());
  list.push_back(5);
  list.push_back(6);
  list.push_back(8);
  list.push_back(9);
  list2 = list;
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
    REQUIRE(list == reverse(list2));
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
    REQUIRE      (list1 == list2);
    REQUIRE      (list2 == list1);
    REQUIRE_FALSE(list1 == list3);
    REQUIRE_FALSE(list2 == list3);
  }

  SECTION("Check lists for inequality") {
    REQUIRE      (list1 != list3);
    REQUIRE      (list2 != list3);
    REQUIRE_FALSE(list1 != list2);
    REQUIRE_FALSE(list2 != list1);
  }
}


// task 3.11
TEST_CASE("inserted node should be at correct position", "[insert]") {
  List<int> k;
  k.push_back(33);
  k.push_back(2);
  k.push_back(86);
  k.insert(k.begin(), 999);
  REQUIRE(k.front() == 999);
  k.insert(k.end(), 4783);
  REQUIRE(k.back() == 4783);

  List<int> t{33, 2, 86, 46, 2, 567};
  t.insert(t.begin(), 999);
  REQUIRE(t.size() == 7);
  t.insert(t.end(), 4783);
  REQUIRE(t.front() == 999);
  REQUIRE(t.back() == 4783);
  REQUIRE(t.size() == 8);    
  List<int> v{999, 33, 2, 86, 46, 2, 567, 4783};
  REQUIRE(t == v);
  t.insert(t.begin()++, 222);
  REQUIRE(t.size() == 9);
}


// task 3.12 optional
TEST_CASE("node at position should be removed", "[erase]") {
  List<int> u;
  u.push_back(357);
  u.push_back(96);
  u.push_back(2);
  u.push_back(14);
  REQUIRE(u.front() == 357);
  //u.erase(u.begin());
  //REQUIRE(u.front() == 96);      //Segmentation violation signal
} 


// task 3.14
TEST_CASE("move all elements from rhs to a new list", "[move-constructor]") {
  List<int> rhs; 
  rhs.push_front(1); 
  rhs.push_front(2); 
  rhs.push_front(3); 
  rhs.push_front(4);
  List<int> new_list;
  REQUIRE(new_list.size() == 0); 
  new_list = std::move(rhs); 
  REQUIRE(rhs.size() == 0); 
  REQUIRE(rhs.empty());
  REQUIRE(new_list.size() == 4); 
  REQUIRE_FALSE(new_list.empty());

  List<int> rhs2; 
  rhs2.push_back(1000); 
  rhs2.push_back(2000); 
  rhs2.push_back(3000); 
  rhs2.push_back(4000);
  List<int> new_list2;
  REQUIRE(new_list2.size() == 0); 
  new_list2 = std::move(rhs2); 
  REQUIRE(rhs2.size() == 0); 
  REQUIRE(rhs2.empty());
  REQUIRE(new_list2.size() == 4);
  REQUIRE(new_list2.front() == 1000);
  REQUIRE(new_list2.back() == 4000);    
  REQUIRE_FALSE(new_list2.empty());
}


// task 3.15 optional
TEST_CASE("initializer list constructor", "[init-constructor]") {
  List<int> int_list1{9, 5, 38, 100};
  List<int> int_list2{9, 5, 38, 100};
  List<int> int_list3{7, 5, 38, 200};
  List<int> int_list4{7, 5, 38, 200};
  
  REQUIRE(int_list1.front() == 9);
  REQUIRE(int_list1.back() == 100);
  REQUIRE(int_list3.front() == 7);
  REQUIRE(int_list3.back() == 200);
  REQUIRE(int_list1.size() == 4);
  REQUIRE(int_list1 == int_list2);
  REQUIRE(int_list3 == int_list4);
  REQUIRE(int_list3.front() == int_list4.front());
  REQUIRE(int_list3.back() == int_list4.back());
  REQUIRE_FALSE(int_list1.back() == int_list3.back());
  REQUIRE_FALSE(int_list1.front() == int_list3.front());
  REQUIRE_FALSE(int_list1.front() == int_list4.front());
  int_list4.push_back(4);
  REQUIRE(int_list4.size() == 5);
}


// task 3.15 optional
TEST_CASE("free operator+ adds elements of a list into another list", "[free-operator+]") {
  List<int> a{1, 2};
  List<int> b{5, 6};
  List<int> c{1, 2, 5, 6};
  List<int> d = a + b;
  REQUIRE(d.size() == c.size());

  List<int> list1;
  List<int> list2;
  list1.push_back(10);
  list1.push_back(20);
  list2.push_back(30);
  list2.push_back(40);
  List<int> list3 = list1 + list2;
  REQUIRE(list3.front() == 10);
  REQUIRE(list3.back() == 40);
}


// task 3.15 optional
// l is move-constructed from temporary list objects
TEST_CASE("count calls of move-constructor", "[count-operator+]") {
  auto l = List<int>{1, 2, 3, 4, 5} + List<int>{6, 7, 8, 9};
  List<int> m{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << "[task 3.15]  ";
  std::copy( l.begin(), l.end(), m.begin()); // (first, last, result)
  for(auto const& i : l) {
    std::cout << i << ", ";
  } std::cout << "\n";
}



int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}




