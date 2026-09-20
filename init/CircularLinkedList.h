#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include "IList.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

template<class T>
class CircularLinkedList : public IList<T> {
public:
    class Node;

protected:
    Node* head;
    Node* tail;
    int count;
    bool (*itemEqual)(T& lhs, T& rhs);
    void (*deleteUserData)(CircularLinkedList<T>*);

public:
    CircularLinkedList(
        void (*deleteUserData)(CircularLinkedList<T>*) = 0,
        bool (*itemEqual)(T&, T&) = 0
    )
        : head(nullptr), tail(nullptr), count(0),
          itemEqual(itemEqual), deleteUserData(deleteUserData) {}

    CircularLinkedList(const CircularLinkedList<T>& list)
        : head(nullptr), tail(nullptr), count(0),
          itemEqual(list.itemEqual), deleteUserData(list.deleteUserData) {
        copyFrom(list);
    }

    CircularLinkedList<T>& operator=(const CircularLinkedList<T>& list) {
        if (this == &list) return *this;
        removeInternalData();
        itemEqual = list.itemEqual;
        deleteUserData = list.deleteUserData;
        copyFrom(list);
        return *this;
    }

    ~CircularLinkedList() {
        removeInternalData();
    }

    void add(T e) override {
        Node* newNode = new Node(e);
        if(this->empty()){
            head=newNode;
            tail=newNode;
            newNode->next=newNode;
            count++;
            return;
        }
        tail->next=newNode;
        newNode->next=head;
        tail=newNode;
        count++;
        //(void)e;
        //throw logic_error("TODO Q2: CircularLinkedList::add");
    }

    void add(int index, T e) override {
        if(index<0 || index>count){
            throw out_of_range("Index out of bounds");
        }
        if(index==count){
            add(e);
            return;
        }
        Node* newNode = new Node(e);
        if(index==0){
            newNode->next=head;
            tail->next=newNode;
            head=newNode;
            count++;
            return;
        }
        Node* prev=head;
        for(int i=0; i<index-1; i++){
            prev=prev->next;
        }
        newNode->next=prev->next;
        prev->next=newNode;
        count++;
        //(void)index; (void)e;
        //throw logic_error("TODO Q2: CircularLinkedList::add(index, e)");
    }

    T removeAt(int index) override {
        if(index<0 || index>=count){
            throw out_of_range("Index out of bounds");
        }
        if(count==1){
            Node *tmp=head;
            T value=tmp->data;
            head=tail=nullptr;
            delete tmp;
            count--;
            return value;
        }
        if(index==0){
            Node *tmp=head;
            T value=tmp->data;
            head=tmp->next;
            tail->next=head;
            delete tmp;
            count--;
            return value;
        }

        Node* prev=head;
        for(int i=0; i<index-1; i++){
            prev=prev->next;
        }
        Node *tmp=prev->next;
        T value=tmp->data;
        prev->next=tmp->next;
        if(index==count-1){
            tail=prev;
        }
        delete tmp;
        count--;
        return value;
        //(void)index;
        //throw logic_error("TODO Q2: CircularLinkedList::removeAt");
    }

    bool removeItem(T item, void (*removeItemData)(T) = 0) override {
        if(count==0) return 0;
        Node *prev=tail;
        Node *cur=head;
        for(int i=0; i<count; i++){
            if(equals(cur->data, item, itemEqual)){
                if(count==1){
                    head=tail=nullptr;
                }
                else{
                    prev->next=cur->next;
                    if(i==0) head=prev->next;
                    if(i==count-1) tail=prev;
                }
                T value=cur->data;
                delete cur;
                count--;
                if(removeItemData){
                    removeItemData(value);
                }
                return true;
            }
            prev=prev->next;
            cur=cur->next;
        }
        return 0;
        //(void)item; (void)removeItemData;
        //throw logic_error("TODO Q2: CircularLinkedList::removeItem");
    }

    void clear() override {
        removeInternalData();
        //throw logic_error("TODO Q2: CircularLinkedList::clear");
    }

    T& get(int index) override {
        if(index<0 || index>=count){
            throw out_of_range("Index out of bounds");
        }
        Node *cur=head;
        for(int i=0; i<index; i++){
            cur=cur->next;
        }
        return cur->data;
        //(void)index;
        //throw logic_error("TODO Q2: CircularLinkedList::get");
    }

    int indexOf(T item) override {
        if(count==0){
            return -1;
        }
        Node *cur=head;
        for(int i=0; i<count; i++){
            if(equals(cur->data, item, itemEqual)){
                return i;
            }
            cur=cur->next;
        }
        return -1;
        //(void)item;
        //throw logic_error("TODO Q2: CircularLinkedList::indexOf");
    }

    bool empty() override { return count == 0; }
    int size() override { return count; }
    bool contains(T item) override { return indexOf(item) >= 0; }

    string toString(string (*item2str)(T&) = 0) override {
        stringstream ss;
        ss << "[";
        Node* cur = head;
        for (int i = 0; i < count; ++i) {
            if (i > 0) ss << ", ";
            if (item2str) ss << item2str(cur->data);
            else ss << cur->data;
            cur = cur->next;
        }
        ss << "]";
        return ss.str();
    }

    void println(string (*item2str)(T&) = 0) {
        cout << toString(item2str) << endl;
    }

protected:
    static bool equals(T& lhs, T& rhs, bool (*itemEqual)(T&, T&)) {
        return itemEqual ? itemEqual(lhs, rhs) : (lhs == rhs);
    }

    void copyFrom(const CircularLinkedList<T>& list) {
        Node* cur = list.head;
        for (int i = 0; i < list.count; ++i) {
            add(cur->data);
            cur = cur->next;
        }
    }

    void removeInternalData() {
        if (deleteUserData != 0) deleteUserData(this);
        Node* cur = head;
        for (int i = 0; i < count; ++i) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = tail = nullptr;
        count = 0;
    }

public:
    class Node {
    public:
        T data;
        Node* next;
        Node(T data, Node* next = nullptr) : data(data), next(next) {}
    };
};

#endif
