#ifndef __DICTIONARY_H
#define __DICTIONARY_H

#include <vector>

template <typename K, typename V>
class Dictionary {
public:
  // търси стойността, свързана с ключа key, ако я има, с възможност за промяна
  virtual V* lookup(K const& key) = 0;

  // добавя стойността value към ключа key
  virtual bool add(K const& key, V const& value) = 0;

  // изтрива ключа key и свързаната с него стойност
  virtual bool remove(K const& key) = 0;

  // вектор от всички ключове
  virtual std::vector<K> keys() = 0;

  // вектор от всички стойности
  virtual std::vector<V> values() = 0;
};

#endif
