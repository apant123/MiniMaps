//
//  HashMap.hpp
//  GoogleMapsDemo
//
//  Created by Arav Pant on 3/9/24.
//

#ifndef HashMap_hpp
#define HashMap_hpp

#include <stdio.h>
#include <string>
#include <list>
#include <iostream>
#include <functional>
#include <iterator>
using namespace std;

template <typename T>
class HashMap {
public:

HashMap(double max_load = 0.75);
    
    ~HashMap() {
    typename list<data>::iterator clear;
    for(int j = 0 ; j < cooked.size(); j++) {
        clear = cooked[j].begin();
        while(clear != cooked[j].end()) {
                clear = cooked[j].erase(clear);
        }
    }
        cooked.clear();
    }
    
    
    
    // destructor; deletes all of the items in the hashmap
 int size() const; // return the number of associations in the hashmap
 // The insert method associates one item (key) with another (value).
 // If no association currently exists with that key, this method inserts
 // a new association into the hashmap with that key/value pair. If there is
 // already an association with that key in the hashmap, then the item
 // associated with that key is replaced by the second parameter (value).
 // Thus, the hashmap must contain no duplicate keys.
    
    

 void insert(const std::string& key, const T& value);
 // Defines the bracket operator for HashMap, so you can use your map like this:
 // your_map["david"] = 2.99;
 // If the key does not exist in the hashmap, this will create a new entry in
 // the hashmap and map it to the default value of type T (0 for builtin types).
 // It returns a reference to the newly created value in the map.
 T& operator[](const std::string& key);
 // If no association exists with the given key, return nullptr; otherwise,
 // return a pointer to the value associated with that key. This pointer can be
 // used to examine that value within the map.
 const T* find(const std::string& key) const;
 // If no association exists with the given key, return nullptr; otherwise,
 // return a pointer to the value associated with that key. This pointer can be
 // used to examine that value or modify it directly within the map.
 T* find(const std::string& key) {
 const auto& hm = *this;
 return const_cast<T*>(hm.find(key));
 }

 double getBuckets() const {return m_buckets;}
 void setBuckets(int set) {m_buckets = set;}
 double getAssociations() const {return m_associations;}
 void setAssociations(int set) {m_associations = set;}
 double getMaxLoad() {return m_max_load;}
 unsigned int HashMe(const std::string &value) const {
     std::hash<std::string> str_hash;
     unsigned long hashValue = str_hash(value);
     return hashValue % m_buckets;
    //unsigned long hashValue = std::hash<T>{}(value);
    //   return hashValue % m_buckets;
}
    
 void rehash();
    
    
    
    
    
private:
    int m_buckets;
    double m_max_load;
    double m_associations;
    struct data {
        string KeyName;
        T dataname;

    };
    std::vector<std::list<data>> cooked;
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;
};



template <typename T>
void HashMap<T>::rehash() {
    
    setBuckets(getBuckets() * 2);
    std::vector<std::list<data>> temp;
    temp.resize(getBuckets());
    
    typename list<data>::iterator it;
    
    for(int i = 0 ; i < cooked.size(); i++) {
         for (it = cooked[i].begin(); it != cooked[i].end(); ++it) {
             unsigned int fried = HashMe(it->KeyName);
             temp[fried].push_back({it->KeyName,it->dataname});
             }
    }
    
    typename list<data>::iterator clear;
    for(int j = 0 ; j < cooked.size(); j++) {
//        for(clear = cooked[j].begin(); clear != cooked[j].end(); clear++) {
//            clear = cooked.erase(clear);
//        }
        clear = cooked[j].begin();
        while(clear != cooked[j].end()) {
            clear = cooked[j].erase(clear);
        }
        
        
    }
    cooked.clear();
    cooked.resize(getBuckets());
    for(int i = 0 ; i < temp.size(); i++) {
         for (it = temp[i].begin(); it != temp[i].end(); ++it) {
             unsigned int fried = HashMe(it->KeyName);
             cooked[fried].push_back({it->KeyName,it->dataname});
             }
    }
    
    for(int j = 0 ; j < temp.size(); j++) {
        clear = temp[j].begin();
        while(clear != temp[j].end()) {
            clear = temp[j].erase(clear);
        }
    }
    temp.clear();
    
}





template <typename T>
HashMap<T>::HashMap(double max_load): m_buckets(10) {
    if(max_load < 0) m_max_load = .75;
    else m_max_load = max_load;
    cooked.resize(getBuckets());
    m_associations = 0;
}

template <typename T>
int HashMap<T>::size() const {
    return getAssociations();
}

template <typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
    
  //  unsigned int temp = HashMe(key);
   // cooked[temp].push_back({key,value});
    
    T* foundValue = find(key);
    if(foundValue == nullptr) {
        
        double what = (getAssociations() + 1) / getBuckets();
        double blud = getMaxLoad();
        if(what >  blud)  {
            rehash();
        }
        unsigned int temp = HashMe(key);
        cooked[temp].push_back({key,value});
        setAssociations(getAssociations() + 1);
    }else {
      T* replace = foundValue;
        *replace = value;
    }
}


template <typename T>
const T* HashMap<T>::find(const std::string& key) const {
    unsigned int temp = HashMe(key);
    
   typename list<data>::const_iterator it;
    
    for (it = cooked[temp].begin(); it != cooked[temp].end(); ++it) {
            if (it->KeyName == key) {
                return &(it->dataname);
            }
        }
        return nullptr;
}

template <typename T>
T& HashMap<T>::operator[](const std::string& key) {
    
//    T* foundValue = find(key);
//    if(foundValue == nullptr) {
//        insert(key, T());
//        return *find(key);
//
//    }
    insert(key, T());
    return *find(key);
    //return *find(key);
}


#endif /* HashMap_hpp */
