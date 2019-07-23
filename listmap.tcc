// $Id: listmap.tcc,v 1.12 2019-02-21 17:28:55-08 - - $

#include "listmap.h"
#include "debug.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key, Value, Less>::node::node(node* next, node* prev,
     const value_type& value_) :
     link(next, prev), value(value_) {
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename Key, typename Value, class Less>
listmap<Key, Value, Less>::~listmap() {
     DEBUGF('l', reinterpret_cast<const void*> (this));
}


//
// iterator listmap::insert (const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::iterator
listmap<Key, Value, Less>::insert(const value_type& pair) {
     iterator i = begin();
     node** curr = &(anchor()->next);
     Less less;
     node* endNode = end().where;
     while (*curr != endNode and less((*curr)->value.first, pair.first)) {
          curr = &(*curr)->next;
          ++i;
     }
     if (*curr == endNode or less(pair.first, (*curr)->value.first)) {
          bool atEnd = *curr == endNode;
          *curr = new node((*curr)->next, (*curr)->prev, pair);
          if (atEnd) {
               endNode->prev = *curr;
               (*curr)->next = endNode;
          }
          else {
               (*curr)->prev->next = *curr;
               (*curr)->next->prev = *curr;
          }
          i = *curr;
     }
     return i;
}

//
// listmap::find(const key_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::iterator
listmap<Key, Value, Less>::find(const key_type& that) {
     iterator i;
     for (i = begin(); i != end(); ++i) {
          key_type current = i->first;
          if (current == that) {
               return i;
          }
     }
     return i;
}

//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::iterator
listmap<Key, Value, Less>::erase(iterator position) {
     iterator i = begin();
     node** curr = &(anchor()->next);
     node* endNode = anchor();
     while ((*curr) != endNode and *curr != position.where) {
          curr = &(*curr)->next;
          ++i;
     }
     if (*curr != endNode) {
          ++i;
          node* prevPtr = ((*curr)->prev);
          node* nextPtr = (*curr)->next;
          delete (*curr);
          if (prevPtr == endNode) {
               endNode->next = nextPtr;
          }
          else {
               prevPtr->next = nextPtr;
          }
          if (nextPtr == endNode) {
               endNode->prev = prevPtr;
          }
          else {
               nextPtr->prev = prevPtr;
          }
          //(*curr)->prev->next = (*curr)->next;
          //(*curr)->next->prev = (*curr)->prev;
          //delete (*curr);
     }
     return i;
}


//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::value_type&
listmap<Key, Value, Less>::iterator::operator*() {
     DEBUGF('l', where);
     return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::value_type*
listmap<Key, Value, Less>::iterator::operator->() {
     DEBUGF('l', where);
     return &(where->value);
}

template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::iterator&
listmap<Key, Value, Less>::iterator::operator+(const int& that) {
     DEBUGF('l', where);
     for (int i = 0; i < that; ++i) {
          this++;
     }
     return *this;
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::iterator&
listmap<Key, Value, Less>::iterator::operator++() {
     DEBUGF('l', where);
     where = where->next;
     return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key, Value, Less>::iterator&
listmap<Key, Value, Less>::iterator::operator--() {
     DEBUGF('l', where);
     where = where->prev;
     return *this;
}


//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key, Value, Less>::iterator::operator==
(const iterator& that) const {
     return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key, Value, Less>::iterator::operator!=
(const iterator& that) const {
     return this->where != that.where;
}

