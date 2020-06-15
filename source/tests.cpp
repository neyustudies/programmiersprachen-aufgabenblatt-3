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
#include "sub_tests/constructors/default_constructed_list.test"

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


/*--------------- own tests --------------------------------------------------------------------*/

#include "sub_tests/clear.test"                                 // task 3.4 
#include "sub_tests/constructors/copy_constructed_list.test"    // task 3.5
#include "sub_tests/unifying_assignment_operator.test"          // task 3.6
#include "sub_tests/reverse.test"                               // task 3.7
#include "sub_tests/equal.test"                                 // task 3.8
#include "sub_tests/iterators/insert.test"                      // task 3.11 optional
#include "sub_tests/iterators/erase.test"                       // task 3.12 optional
#include "sub_tests/has_same_content.test"                      // task 3.13 optional
#include "sub_tests/constructors/move_constructed_list.test"    // task 3.14
#include "sub_tests/constructors/init_constructed_list.test"    // task 3.15 part 1 optional
#include "sub_tests/free_operator_plus.test"                    // task 3.15 part 2 optional
#include "sub_tests/constructors/count_calls.test"              // task 3.15 part 3 optional


int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}

