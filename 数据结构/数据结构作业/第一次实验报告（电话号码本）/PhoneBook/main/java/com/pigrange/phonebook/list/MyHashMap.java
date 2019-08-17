package com.pigrange.phonebook.list;

public interface MyHashMap<V> {

    void put(long key, V value);

    V get(long key);

    void Remove(long key);

    int size();
}
