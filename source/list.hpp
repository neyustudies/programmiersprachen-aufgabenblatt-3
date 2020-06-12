#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>
#include <vector>
#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev  = nullptr;
  ListNode* next  = nullptr;
};


template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* derefenciation of 
  iterator using operator* */
  T& operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    } return node->value;
  }


  /* derefenciation of 
  iterator using operator-> */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    } return &this->operator*(); // &node->value
  }


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    } node = node->next;
      return *this; 
  }


  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call: it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    } ListIterator<T> tmp = *this;
      ++(*this);
      return tmp;   
  }


  /* Equality-Operation for Iterator */
  bool operator==(ListIterator<T> const& x) const {
    return x.node == node;
  }


  /* Inequality-Operation for Iterator */
  bool operator!=(ListIterator<T> const& x) const {
    return !(x == *this);
  }


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


/*--------------- class List ----------------------------------------------------------------*/


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


    /* copy constructor 
    using Deep-Copy semantics */
    List(List<T> const& rhs) : List() {
        auto tmp = rhs.first_; 
        for(unsigned i = 0; i < rhs.size_; ++i) {
          push_back(tmp->value);
          tmp = tmp->next;
        }
      }
    

    /* move constructor moves all 
    elements from rhs to a new list */
    List(List<T>&& rhs) :
      size_   {rhs.size_},
      first_  {rhs.first_}, 
      last_   {rhs.last_} {
        rhs.size_  = 0;
        rhs.first_ = nullptr;
        rhs.last_  = nullptr;
      }


    /* calls initializer_list constructor */
    List(std::initializer_list<T> const& ini_list) : List() {
        for(auto const& elem : ini_list) {
          push_back(elem);
        }
      }


    /* unifying copy-and-swap assignment operator */
    List<T>& operator=(List<T> rhs) {
      swap(rhs);
      return *this;
    }


    /* swap function for assignment operator */
    void swap(List<T>& list) {
      std::swap(first_,list.first_);
      std::swap(last_, list.last_);
      std::swap(size_, list.size_);
    }


    /* checks if two lists are equal */
    bool operator==(List const& rhs) const {
      if(size_ != rhs.size_) {
        return false;
      } else if(first_ == nullptr ^ rhs.first_ == nullptr) {
        return false;
      } else if(first_ == nullptr && rhs.first_ == nullptr) {
        return true;
      } else { 
        auto lhs_elem = first_;
        auto rhs_elem = rhs.first_;
        for(unsigned i = 0; i < size_; ++i) {
          if(lhs_elem->value != rhs_elem->value) {
            return false;
          } rhs_elem = rhs_elem->next;
            lhs_elem = lhs_elem->next;
        } return true;
      }
    }


    /* checks if two lists are inequal */
    bool operator!=(List const& rhs) const {
      return !(rhs == *this);
    } 


    /* destructor */
    ~List() {
      clear();
    }


    /* returns iterator to the first element */
    ListIterator<T> begin() const {
      return ListIterator<T>{first_};
    }


    /* returns iterator to the 
    element after the last element */
    ListIterator<T> end() const {
      return ListIterator<T>{nullptr};
    }


    /* deletes all elements */ 
    void clear() {
      auto tmp_size = size_;
      for(unsigned i = 0; i < tmp_size; ++i) {
        pop_back();
      }
    }


    /* inserts x at position pos, iterator pointing to insertion point */
    ListIterator<T> insert(ListIterator<T> const& pos, T const& x) {
      if(pos.node == first_){
        push_front(x);
        return begin();
        } else if(pos.node == nullptr) {
          push_back(x);
          return ListIterator<T>{last_};
          } else {              // ListNode<T>{T value, prev, next}
            ListNode<T>* tmp = new ListNode<T>{x, pos.node->prev, pos.node};
            tmp->prev->next = tmp;
            tmp->next->prev = tmp;
            ++size_;
            return ListIterator<T>{tmp};
            }
    }


    /* deletes a node at position pos, iterator pointing to next node */
    ListIterator<T> erase(ListIterator<T> const& pos) {
      ListNode<T>* tmp = pos.node;
      tmp->next->prev = tmp->prev;
      tmp->prev->next = tmp->next;
      auto it = ListIterator<T>{tmp->next};
      delete tmp;
      --size_;
      return it;
    }


    /* reverses the list */
    void reverse() {
      if(empty()) {
        throw "List is empty";
      } auto tmp = first_;
        for(unsigned i = 0; i < size_; ++i) {
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


/*--------------- free functions --------------------------------------------------------------*/


/* (free) reverse the list */
template <typename T>
List<T> reverse(List<T> const& lhs) {
  List<T> r{lhs};
  r.reverse();
  return r;
}


/* (free) adds elements of a list to another list */
template <typename T>
List<T> operator+(List<T> const& lhs, List<T> const& rhs) {
  List<T> r{lhs};
  for(auto const& c : rhs) {
    r.push_back(c);
  } return r;   
}

/* (free) returns true if list and vector are equal */
template <typename T>
bool has_same_content(List<T> const& list, std::vector<T> const& vec) {
  bool equal = false;
	std::vector<T> vecA(list.begin(), list.end());
	if (vecA == vec) {
		equal = true;
	} return equal;
}


#endif // #define BUW_LIST_HPP

