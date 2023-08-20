#ifndef SET_OPERATORS_H
#define SET_OPERATORS_H

#include <algorithm>
#include <set>

// This file has the boilerplate code you need in order to use
// the set operators we talked about in class with std::sets.
// #include it in a .cpp file to enable the operators there.


template <class T, class C, class A>
inline std::set<T,C,A> operator & (const std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  std::set<T,C,A> result;
  std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(result, result.end()));
  return result;
}

template <class T, class C, class A>
inline std::set<T,C,A> operator | (const std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  std::set<T,C,A> result;
  std::set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(result, result.end()));
  return result;
}

template <class T, class C, class A>
inline std::set<T,C,A> operator ^ (const std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  std::set<T,C,A> result;
  std::set_symmetric_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(result, result.end()));
  return result;
}

template <class T, class C, class A>
inline std::set<T,C,A> operator - (const std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  std::set<T,C,A> result;
  std::set_difference(a.begin(), a.end(), b.begin(), b.end(), inserter(result, result.end()));
  return result;
}


template <class T, class C, class A>
inline std::set<T,C,A>& operator &= (std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  return a = a & b;
}

template <class T, class C, class A>
inline std::set<T,C,A>& operator |= (std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  return a = a | b;
}

template <class T, class C, class A>
inline std::set<T,C,A>& operator ^= (std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  return a = a ^ b;
}

template <class T, class C, class A>
inline std::set<T,C,A>& operator -= (std::set<T,C,A>& a, const std::set<T,C,A>& b) {
  return a = a - b;
}

#endif
