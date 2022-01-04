#ifndef BSTREE_DICTIONARY_H
#define BSTREE_DICTIONARY_H

#include "dictionary.h"
#include "key_value_pair.cpp"
#include "binary_search_stree.cpp"

template <typename K, typename V>
class BSTreeDictionary : public Dictionary<K, V>, BSTree<KeyValuePair<K, V>> {
  using KVP = KeyValuePair<K, V>;
  using P = BinTreePosition<KVP>;
  using BST = BSTree<KVP>;

  using BST::search;
  using BST::insert;
  using BST::rootPos;

  void collectKeys(std::vector<K>& keys, P pos) {
    if (pos) {
      collectKeys(keys, -pos);
      keys.push_back((*pos).getKey());
      collectKeys(keys, +pos);
    } 
  }

  void collectValues(std::vector<V>& values, P pos) {
    if (pos) {
      collectValues(values, -pos);
      values.push_back((*pos).getValue());
      collectValues(values, +pos);
    } 
  }

  
public:
  // търси стойността, свързана с ключа key, ако я има, с възможност за промяна
  V* lookup(K const& key) {
    P pos = search(key);
    if (!pos)
      return nullptr;
    return &(*pos).getValue();
  }

  // добавя стойността value към ключа key
  bool add(K const& key, V const& value) {
    return insert(KVP(key, value));
  }

  // изтрива ключа key и свързаната с него стойност
  bool remove(K const& key) {
    return BST::remove(key);
  }

  // вектор от всички ключове
  std::vector<K> keys() {
    std::vector<K> result;
    collectKeys(result, rootPos());
    return result;
  }

  // вектор от всички стойности
  std::vector<V> values() {
    std::vector<V> result;
    collectValues(result, rootPos());
    return result;
  }

};

#endif
