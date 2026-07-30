// Created by SwiftWare Lab on 9/24.
// CE 4SP4 - High Performance Programming
// Copyright (c) 2024 SwiftWare Lab

#include "sort.h"
#include <algorithm>

LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

void LinkedList::push_front(int v) {
    Node* new_node = new Node{v, head};
    head = new_node;
    size++;
}

LinkedList LinkedList::from_vector(const std::vector<int>& v) {
    LinkedList list;
    for (int i = v.size() - 1; i >= 0; --i) {
        list.push_front(v[i]);
    }
    return list;
}

void sort_insertion(LinkedList& list) {
    if (list.head == nullptr || list.head->next == nullptr) { return; } //List is already sorted

    Node* sorted = nullptr;

    while (list.head != nullptr) {
        Node* current = list.head;
        list.head = list.head->next;
        if (sorted == nullptr || current->value < sorted->value) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->value < current->value) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }
    list.head = sorted;
}

Node* merge (Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (left->value <= right->value) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

void sort_merge(LinkedList& list) {
    if (list.head == nullptr || list.head->next == nullptr) {return;} //List is already sorted

    // Split the list into two halves
    Node* slow = list.head;
    Node* fast = list.head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = nullptr;

    LinkedList left;
    left.head = list.head;
    left.size = 0; // Size will be recalculated

    LinkedList right;
    right.head = mid;
    right.size = 0;

    //sort each half recursively
    sort_merge(left);
    sort_merge(right);

    //merge the halves
    list.head = merge(left.head, right.head);
    
    left.head = nullptr; // Avoid double deletion
    right.head = nullptr;
    
    list.size = 0; // Recalculate size
    Node* current = list.head;
    while (current != nullptr) {
        list.size++;
        current = current->next;
    }
}