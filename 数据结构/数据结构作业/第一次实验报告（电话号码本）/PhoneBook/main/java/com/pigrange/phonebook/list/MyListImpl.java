package com.pigrange.phonebook.list;

import com.pigrange.phonebook.model.HasValue;

public class MyListImpl<T extends HasValue> implements MyList<T> {
    private int length;
    private Node<T> lastNode;
    private Node<T> firstNode;
    private MyHashMap<T> hashMap = new MyHashMapImpl<>();


    public T getByValue(long key) {
        return hashMap.get(key);
    }

    @Override
    public boolean add(T data) {
        int state = judge(data);
        if (state == 1) {
            return false;
        }
        if (firstNode == null && lastNode == null) {
            firstNode = lastNode = new Node<>(null, data);
            length++;
            return true;
        }
        lastNode.next = new Node<>(null, data);
        lastNode = lastNode.next;
        length++;
        hashMap.put(data.getValue(), data);
        return true;
    }

    @Override
    public boolean add(int pos, T data) {
        int state = 1;
        if (pos == 0) {
            Node<T> node = new Node<>();
            node.setData(data);
            node.setNext(firstNode);
            firstNode = node;
        } else if (pos > length || pos < 0) {
            state = 0;
        } else {
            Node<T> prevNode = getNode(pos - 1);
            prevNode.setNext(new Node<>(prevNode.next, data));
        }
        if (state == 1) {
            length++;
            hashMap.put(data.getValue(), data);
            return true;
        } else {
            return false;
        }
    }

    @Override
    public void remove(int pos) {
        int state = 1;
        if (pos < 0 || pos > length - 1) {
            state = 0;
        } else if (pos == 0) {
            firstNode = firstNode.next;
            if (length == 1) {
                firstNode = null;
                lastNode = null;
            }
        } else {
            Node<T> prevNode = getNode(pos - 1);
            long key = prevNode.getNext().getData().getValue();
            if (pos == length - 1) {
                lastNode = prevNode;
            } else {
                prevNode.setNext(prevNode.next.next);
            }
            hashMap.Remove(key);
        }
        if (state == 1) {
            length--;
        }
    }

    @Override
    public void remove(T data) {
        if (data.equals(firstNode.data)) {
            firstNode = firstNode.next;
            hashMap.Remove(data.getValue());
            length -= 1;

        } else if (data.equals(lastNode.data)) {
            lastNode = lastNode.next;
            hashMap.Remove(data.getValue());
            length -= 1;

        } else {
            Node<T> currentNode = firstNode;
            for (int i = 0; i < length - 2; i++) {
                if (currentNode.getNext().getData().equals(data)) {
                    currentNode.next = currentNode.getNext().getNext();
                    hashMap.Remove(data.getValue());
                    length -= 1;
                    break;
                }
                currentNode = currentNode.getNext();
            }
        }
    }

    @Override
    public void sortByValue() {
        for (int i = length; i > 0; i--) {
            for (int j = 0; j < i - 1; j++) {
                if (getNode(j).getData().getValue() > getNode(j + 1).getData().getValue()) {
                    nodeExchange(j, j + 1);
                }
            }
        }
    }

    @Override
    public int indexOf(T data) {
        if (data.equals(firstNode.getData())) {
            return 0;
        } else if (data.equals(lastNode.getData())) {
            return length - 1;

        } else {
            Node<T> currentNode = firstNode;
            for (int i = 1; i < length - 1; i++) {
                if (currentNode.getNext().getData().equals(data)) {
                    return i;
                }
                currentNode = currentNode.getNext();
            }
        }
        return -1;
    }

    @Override
    public T get(int pos) {
        if (pos > length - 1 || pos < 0) {
            return null;
        }
        return getNode(pos).getData();
    }

    @Override
    public int size() {
        return length;
    }

    @Override
    public int searchByValue(long value) {
        int pos = -1;
        Node<T> currentNode = firstNode;
        for (int i = 0; i < length; i++) {
            if (currentNode.getData().getValue() == value) {
                pos = i;
                break;
            }
            currentNode = currentNode.getNext();
        }
        return pos;
    }

    private Node<T> getNode(int position) {
        Node<T> targetNode = firstNode;
        for (int i = 0; i < position; i++) {
            targetNode = targetNode.next;
        }
        return targetNode;
    }

    private void nodeExchange(int lager, int smaller) {
        Node<T> smallerNode = getNode(smaller);
        Node<T> lagerNode = getNode(lager);
        Node<T> end = smallerNode.next;
        Node<T> prev = getNode(lager - 1);

        if (length == 1 || length == 2) {
            firstNode = smallerNode;
            lastNode = lagerNode;
        }
        if (lager == 0) {
            smallerNode.setNext(lagerNode);
            lagerNode.setNext(end);
            firstNode = smallerNode;
        } else if (smaller == length - 1) {
            prev.next = smallerNode;
            smallerNode.next = lagerNode;
            lastNode = lagerNode;
        } else {
            prev.next = smallerNode;
            smallerNode.next = lagerNode;
            lagerNode.next = end;
        }
    }

    private int judge(T data) {
        int state = 0;
        Node<T> currentNode = firstNode;
        for (int i = 0; i < length; i++) {
            if (data.getValue() == currentNode.getData().getValue()) {
                state = 1;
                break;
            }
            currentNode = currentNode.getNext();
        }

        return state;
    }

    private class Node<E extends HasValue> {
        private Node<E> next;
        private E data;

        private Node() {
        }

        private Node(Node<E> next, E data) {
            this.next = next;
            this.data = data;
        }


        private void setData(E data) {
            this.data = data;
        }

        private E getData() {
            return data;
        }

        private Node<E> getNext() {
            return next;
        }

        private void setNext(Node<E> node) {
            next = node;
        }
    }
}


