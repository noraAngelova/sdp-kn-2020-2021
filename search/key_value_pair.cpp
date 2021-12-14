#ifndef KEY_VALUE_PAIR_CPP
#define KEY_VALUE_PAIR_CPP

template <typename K, typename V>
class KeyValuePair {
  K key;
  V value;

public:
  KeyValuePair(K const& k = K(), V const& v = V()) : key(k), value(v) {}

  K const& getKey() const { 
    return key; 
  }
  
  V const& getValueConst() const { 
    return value; 
  }
  
  V& getValue() { 
    return value; 
  }

  bool operator==(KeyValuePair const& kvp) const { 
    return key == kvp.key; 
  }
  
  bool operator!=(KeyValuePair const& kvp) const { 
    return !(*this == kvp); 
  }
  
  bool operator< (KeyValuePair const& kvp) const { 
    return key < kvp.key; 
  }
  
  bool operator>=(KeyValuePair const& kvp) const { 
    return !(*this < kvp); 
  }
  
  bool operator>(KeyValuePair const& kvp) const  { 
    return !(*this == kvp || *this < kvp); 
  }
  
  bool operator<=(KeyValuePair const& kvp) const { 
    return !(*this > kvp); 
  }
};

#endif
