// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
  
  private:
    struct Item {
      T data;
      Item* next;
      Item* last;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);

  public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;
};

typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
    Item* item = new Item;
    item->data = data;
    item->last = nullptr;
    item->next = nullptr;
    return item;
}

T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("TPQueue is empty!");
    } else {
        Item* item1 = head->next;
        T data = head->data;
        delete head;
        head = item1;
        return data;
    }
}

TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

void TPQueue<T>::print() const {
    Item* item2 = head;
    while (item2) {
        std::cout << item2->data << " ";
        item2 = item2->next;
    }
    std::cout << std::endl;
}

void TPQueue<T>::push(const T& value) {
    if (head == nullptr) {
        head = create(value);
        tail = head;
    } else if (tail->data.prior >= value.prior) {
        if (tail->data.ch == value.ch) {
            tail->data = value;
        } else {
            tail->next = create(value);
            tail->next->last = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->last = create(value);
        head = tail->last;
        head->next = tail;
    } else {
        Item* item3 = tail;
        while (item3 != head && item3->data.prior < value.prior) {
            item3 = item3->last;
        }
        if (item3->data.prior > value.prior) {
            Item* item4 = new Item;
            item4->next = item3->next;
            item4->last = item3;
            item4->data = value;
            item4->next->last = item4;
            item3->next = item4;
        }
        if (item3 == head && item3->data.prior < value.prior) {
            head->last = create(value);
            head = head->last;
            head->next = item3;
        }
    }
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
