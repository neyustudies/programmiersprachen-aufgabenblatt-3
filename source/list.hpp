#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev  = nullptr;
  ListNode* next  = nullptr;
};


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.11)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* DESCRIPTION  operator*() */
  T& operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.11 - Teil 1)

  } //call *it

  /* DESCRIPTION  operator->() */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.11 - Teil 2)
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.11 - Teil 3)
    
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.11 - Teil 4)

  }


  /* ... */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.11 - Teil 5)
    // Iterators should be the same if they refer to the same node
    return false;
  } // call it: == it

  /* ... */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.11 - Teil 6)
    // Reuse operator==
    return false;
  } // call it: != it

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};

/*--------------- class List ----------------------------------------------------------*/

template <typename T>
class List {
  public:
    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    /* default constructor */
    List() :
      size_   {0},
      first_  {nullptr},
      last_   {nullptr} {}

    // TODO: test and implement
    /* copy constructor using Deep-Copy semantics 
       moves all elements from List1 to List2 */
    List(List<T>&& rhs) :
      first_{rhs.first_}, 
      last_{rhs.last_} {rhs.first_ = nullptr;
                        rhs.last_  = nullptr;
                        size_      = rhs.size_;
                        rhs.size_  = 0;}

    // (3.14 - Teil 1)
    /* calls initializer_list constructor */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //ListNode* prev_{nullptr},
      //ListNode* next_{nullptr}
    }

    // TODO: test and implement 3.5
    /* Copy-Konstruktor using Deep-Copy semantics */
    List(List<T> const& rhs) {
      auto tmp = rhs.first_;
      for(auto i = 0; i < rhs.size_; ++i) {
        push_back(tmp->value);
        tmp = tmp->next;
      }
    }

    // TODO: test and implement 3.6
    /*(unifying) copy-and-swap assignment operator */
    List<T>& operator=(List<T> rhs) { 
      swap(rhs); // rhs.swap(*this)?
      return *this;
    }

    /* ... */
    // test and implement:
    bool operator==(List const& rhs)
    {
      //TODO: operator== (Aufgabe 3.8)
    }

    bool operator!=(List const& rhs)
    {
      //TODO: operator!= (Aufgabe 3.8)
      // make use of operator==
    }

    /* deletes all elements and the list itself */
    ~List() {
      clear();
    }

    /* ... */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.10)
      return {};
    }

    /* ... */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.10)
      return {};
    }

    /* deletes all elements of the list */ 
    void clear() {
      auto tmp_size = size_;
      for(auto i = 0; i < tmp_size; ++i) {
        pop_back();
      } // TODO: test method clear()
    }

    /* ... */
    //TODO: member function insert (Aufgabe 3.12)

    /* ... */
    //TODO: member function insert (Aufgabe 3.13)

    /* reverse the list */
    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)
    void reverse() {
      if(empty()) {
        throw "List is empty";
      } auto tmp = first_;
        for(auto i = 0; i < size_; ++i) {
          auto old_prev  = tmp->prev;
          tmp->prev      = tmp->next;
          tmp->next      = old_prev;
          tmp            = tmp->prev;
        } auto old_first = first_;
          first_         = last_;
          last_          = old_first;
    }

    /* adds element to the beginning of list */
    void push_front(T const& element) {
      ListNode<T>* tmp = new ListNode<T>{element};
      ++size_;
      if(empty()) {
        first_       = tmp;
        last_        = tmp;
      } tmp->next    = first_;
        first_->prev = tmp;
        first_       = tmp;
        first_->prev = nullptr;
        last_->next  = nullptr;
    }

    /* adds element to the end of the list */
    void push_back(T const& element) {
      ListNode<T>* tmp = new ListNode<T>{element};
      ++size_;
      if(empty()) {
        first_       = tmp;
        last_        = tmp;
      } tmp->prev    = last_;
        last_->next  = tmp;
        last_        = tmp;
        first_->prev = nullptr;
        last_->next  = nullptr;
    }

    /* deletes first element */
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      } else if(size_ == 1) {
        --size_;
        delete(first_);
        first_          = nullptr;
        last_           = nullptr;
      } else {
        --size_;
        auto tmp        = first_;
        tmp->next->prev = nullptr;
        first_          = tmp->next;
        delete(tmp);
      }
    }

    /* deletes last element */
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      } else if(size_ == 1) {
        --size_;
        delete(first_);
        first_          = nullptr;
        last_           = nullptr;
      } else {
        --size_;
        auto tmp        = last_;
        tmp->prev->next = nullptr;
        last_           = tmp->prev;
        delete(tmp);     
      }
    }

    /* returns reference to first element */
    T& front() {
      if(empty()) {
        throw "List is empty";
      } return first_->value;
    }

    /* returns reference to last element */
    T& back() {
      if(empty()) {
        throw "List is empty";
      } return last_->value;
    }

    /* checks if list is empty */
    bool empty() const {
      return first_ == nullptr;
    };

    /* returns the number of elements in the list */
    std::size_t size() const {      
      return size_;
  };

  /* list members */
  private: 
    std::size_t  size_;
    ListNode<T>* first_;
    ListNode<T>* last_;
};

/*--------------- free functions ----------------------------------------------------*/

/* reverse the list */
template <typename T>
List<T> reverse(List<T> const& x) {
  List<T> list{x};
  list.reverse();
  return list;
}

/* ... */
//TODO: Freie Funktion operator+ (3.14 - Teil 2)

#endif // #define BUW_LIST_HPP
