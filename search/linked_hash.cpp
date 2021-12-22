#ifndef LINKED_HASH_CPP
#define LINKED_HASH_CPP

#include <iostream>

#include "dictionary.h"
#include "key_value_pair.cpp"
#include "llist.cpp"

template <typename K>
using HashFunction = unsigned (*)(K const&);

template <typename K, typename V, HashFunction<K> hashFunction, unsigned HASH_SIZE = 101>
class LinkedHash : public Dictionary<K, V> {
  using KVP = KeyValuePair<K, V>;
  using Bucket = LinkedList<KVP>;
  Bucket table[HASH_SIZE];

  Bucket& findBucket(K const& key) {
    return table[hashFunction(key) % HASH_SIZE];
  }

  Bucket const& findBucketConst(K const& key) const {
    return table[hashFunction(key) % HASH_SIZE];
  }

public:
  // търси стойността, свързана с ключа key, ако я има, с възможност за промяна
  V* lookup(K const& key) {
    Bucket& b = findBucket(key);
    for(KVP& kv : b)
      if (kv.getKey() == key)
        return &kv.getValue();
    return nullptr;
  }

  V const* lookupConst(K const& key) const {
    Bucket const& b = findBucketConst(key);
    for(KVP const& kv : b)
      if (kv.getKey() == key)
        return &kv.getValueConst();
    return nullptr;
  }

  // добавя стойността value към ключа key
  bool add(K const& key, V const& value) {
    if (lookup(key) != nullptr)
      return false;
    findBucket(key).insertLast(KVP(key, value));
    return true;
  }

  // изтрива ключа key и свързаната с него стойност
  bool remove(K const& key) {
    Bucket& b = findBucket(key);
    for(typename Bucket::I it = b.begin(); it; ++it)
      if ((*it).getKey() == key)
        // намерихме ключа, изтриваме го
        return b.deleteAt(it);
    return false;
  }

  // вектор от всички ключове
  std::vector<K> keys() {
    std::vector<K> result;
    for(Bucket& b : table)
      for(KVP kv : b)
        result.push_back(kv.getKey());
    return result;
  }

  // вектор от всички стойности
  std::vector<V> values() {
    std::vector<V> result;
    for(Bucket& b : table)
      for(KVP kv : b)
        result.push_back(kv.getValue());
    return result;
  }
};

#endif
