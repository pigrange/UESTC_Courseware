package com.pigrange.phonebook.list;

public class MyHashMapImpl<V> implements MyHashMap<V> {
    private static int defaultLength = 16;
    private int size = 0;
    private Entry<V>[] table;

    MyHashMapImpl() {
        this(defaultLength);
    }

    private MyHashMapImpl(int length) {
        defaultLength = length;
        table = new Entry[defaultLength];
    }

    private int hash(long key) {
        int length = defaultLength;
        int i = (int) key % length;
        if (i < 0) {
            i = -i;
        }
        return i;
    }

    private V find(Entry<V> entry, long key) {
        if (key == entry.getKey() && !entry.isRemoved) {
            return entry.getData();
        } else {
            if (entry.next != null) {
                return find(entry.next, key);
            }
        }
        return null;
    }

    @Override
    public void put(long key, V value) {
        int pos = hash(key);
        Entry<V> entry = table[pos];

        if (entry == null) {
            table[pos] = new Entry<>(key, value, null);
        } else {
            addEntry(key, value, entry);
        }
        size++;
    }

    @Override
    public V get(long key) {
        int pos = hash(key);
        if (table[pos] == null) {
            return null;
        }
        return find(table[pos], key);
    }

    @Override
    public void Remove(long key) {
        int pos = hash(key);
        Entry<V> entry = table[pos];

        while (entry.next != null) {
            if (entry.mKey == key) {
                entry.isRemoved = true;
                return;
            }
            entry = entry.next;
        }
    }

    @Override
    public int size() {
        return size;
    }

    private void addEntry(long key, V value, Entry<V> entry) {
        while (entry.next != null) {
            if (entry.isRemoved) {
                entry.mData = value;
                entry.mKey = key;
                entry.isRemoved = false;
                return;
            }
            entry = entry.next;
        }
        entry.next = new Entry<>(key, value);
    }

    private class Entry<E> {
        long mKey;
        E mData;
        Entry<E> next;
        boolean isRemoved = false;

        Entry(long key, E value, Entry<E> next) {
            this.mKey = key;
            this.mData = value;
            this.next = next;
        }

        Entry(long key, E value) {
            this.mKey = key;
            this.mData = value;
            this.next = null;
        }

        long getKey() {
            return mKey;
        }

        public E getData() {
            return mData;
        }
    }
}
