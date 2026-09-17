#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#include "IList.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

template<class T>
class SLinkedList : public IList<T> {
public:
    class Iterator;
    class Node;

protected:
    Node* head;
    Node* tail;
    int count;
    bool (*itemEqual)(T& lhs, T& rhs);
    void (*deleteUserData)(SLinkedList<T>*);

public:
    SLinkedList(
        void (*deleteUserData)(SLinkedList<T>*) = 0,
        bool (*itemEqual)(T&, T&) = 0
    ) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->next = head;
        count = 0;
        this->itemEqual = itemEqual;
        this->deleteUserData = deleteUserData;
    }

    SLinkedList(const SLinkedList<T>& list) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->next = head;
        count = 0;
        itemEqual = list.itemEqual;
        deleteUserData = list.deleteUserData;
        copyFrom(list);
    }

    SLinkedList<T>& operator=(const SLinkedList<T>& list) {
        if (this == &list) return *this;
        removeInternalData();
        head->next = tail;
        tail->next = head;
        count = 0;
        itemEqual = list.itemEqual;
        deleteUserData = list.deleteUserData;
        copyFrom(list);
        return *this;
    }

    ~SLinkedList() {
        removeInternalData();
        delete head;
        delete tail;
    }

    void add(T e) override {
        tail->data=e;
        Node* newTail= new Node;
        tail->next=newTail;
        newTail->next=head;
        tail=newTail;
        count++;
        //(void)e;
        //throw logic_error("TODO Q1: SLinkedList::add");
    }

    void add(int index, T e) override {
        if(index < 0 || index > count){
            throw out_of_range("Index out of bounds");
        }
        if(index==count){
            add(e);
            return;
        }

        Node* newNode = new Node;
        newNode->data = e;
        Node* prev = head;
        for(int i=0; i<index; i++){
            prev=prev->next;
        }
        newNode->next=prev->next;
        prev->next=newNode;
        count++;

        //(void)index; (void)e;
        //throw logic_error("TODO Q1: SLinkedList::add(index, e)");
    }

    T removeAt(int index) override {
        if(index<0 || index>=count){
            throw out_of_range("Index out of bounds");
        }
        Node* prev=head;
        for(int i=0; i<index; i++){
            prev=prev->next;
        }
        Node* tmp=prev->next;
        T data = tmp->data;
        prev->next=prev->next->next;
        delete tmp;
        count--;
        return data;
        //(void)index;
        //throw logic_error("TODO Q1: SLinkedList::removeAt");
    }

    bool removeItem(T item, void (*removeItemData)(T) = 0) override {
        Node* prev = head;
        while(prev->next != tail){
            if(equals(prev->next->data, item, itemEqual)){
                Node* tmp= prev->next;
                prev->next=prev->next->next;
                T data = tmp->data;
                delete tmp;
                count--;
                if(removeItemData){
                    removeItemData(data);
                }
                return true;
            }
            prev=prev->next;
        }
        return false;
        //(void)item; (void)removeItemData;
        //throw logic_error("TODO Q1: SLinkedList::removeItem");
    }

    void clear() override {
        removeInternalData();
        head->next=tail;
        tail->next=head;
        count=0;
        //throw logic_error("TODO Q1: SLinkedList::clear");
    }

    T& get(int index) override {
        if(index<0 || index>=count){
            throw out_of_range("Index out of bounds");
        }
        Node* cur=head->next;
        for(int i=0; i<index; i++){
            cur=cur->next;
        }
        return cur->data;
        //(void)index;
        //throw logic_error("TODO Q1: SLinkedList::get");
    }

    int indexOf(T item) override {
        Node* cur=head->next;
        int index=0;
        while(cur!=tail){
            if(equals(cur->data, item, itemEqual)){
                return index;
            }
            cur=cur->next;
            index++;
        }
        return -1;
        //(void)item;
        //throw logic_error("TODO Q1: SLinkedList::indexOf");
    }

    bool empty() override { return count == 0; }
    int size() override { return count; }

    bool contains(T item) override {
        return indexOf(item) >= 0;
    }

    string toString(string (*item2str)(T&) = 0) override {
        stringstream ss;
        ss << "[";
        Node* cur = head->next;
        bool first = true;
        while (cur != tail) {
            if (!first) ss << ", ";
            if (item2str) ss << item2str(cur->data);
            else ss << cur->data;
            first = false;
            cur = cur->next;
        }
        ss << "]";
        return ss.str();
    }

    void println(string (*item2str)(T&) = 0) {
        cout << toString(item2str) << endl;
    }

    void setDeleteUserDataPtr(void (*deleteUserData)(SLinkedList<T>*) = 0) {
        this->deleteUserData = deleteUserData;
    }

    Iterator begin() { return Iterator(this, true); }
    Iterator end() { return Iterator(this, false); }

    static void free(SLinkedList<T>* list) {
        Iterator it = list->begin();
        while (it != list->end()) {
            delete *it;
            it++;
        }
    }

protected:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T&)) {
        return itemEqual ? itemEqual(lhs, rhs) : (lhs == rhs);
    }

    void copyFrom(const SLinkedList<T>& list) {
        Node* src = list.head->next;
        while (src != list.tail) {
            add(src->data);
            src = src->next;
        }
    }

    void removeInternalData() {
        if (deleteUserData != 0) deleteUserData(this);
        Node* cur = head->next;
        while (cur != tail) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

public:
    class Node {
    public:
        T data;
        Node* next;

        Node(Node* next = 0) : next(next) {}
        Node(T data, Node* next = 0) : data(data), next(next) {}
    };

    class Iterator {
    private:
        SLinkedList<T>* pList;
        Node* pNode;

    public:
        Iterator(SLinkedList<T>* pList = 0, bool begin = true) {
            this->pList = pList;
            if (pList == 0) pNode = 0;
            else pNode = begin ? pList->head->next : pList->tail;
        }

        Iterator& operator=(const Iterator& iterator) {
            pNode = iterator.pNode;
            pList = iterator.pList;
            return *this;
        }

        void remove(void (*removeItemData)(T) = 0) {
            if (pList == 0 || pNode == pList->tail) return;

            Node* prev = pList->head;
            int index = 0;
            while (prev->next != pList->tail && prev->next != pNode) {
                prev = prev->next;
                ++index;
            }
            if (prev->next != pNode) return;

            T removed = pList->removeAt(index);
            if (removeItemData != 0) removeItemData(removed);
            pNode = prev;
        }

        T& operator*() { return pNode->data; }
        bool operator!=(const Iterator& iterator) { return pNode != iterator.pNode; }
        Iterator& operator++() { pNode = pNode->next; return *this; }
        Iterator operator++(int) { Iterator old = *this; ++(*this); return old; }
    };
};

#endif
