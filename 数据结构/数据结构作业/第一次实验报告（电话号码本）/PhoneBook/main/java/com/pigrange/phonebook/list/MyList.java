package com.pigrange.phonebook.list;

public interface MyList<T> {

    boolean add(T data);

    boolean add(int pos, T data);

    void remove(int pos);

    void remove(T data);

    void sortByValue();

    int indexOf(T data);

    T get(int pos);

    int size();

    int searchByValue(long value);

    T getByValue(long key);
}
