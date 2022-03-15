/**
 * @file main.cpp
 * @author Max Monciardini
 * @brief CSCI 14 - Merge Sort Assignment
 * @date 2022-03-15
 *
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

struct Node
{
    int data;
    struct Node *next;
};

struct LinkedList
{
    Node *head;
    Node *tail;
    int length;
};

void ListAppend(LinkedList *list, Node *newNode)
{
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->length++;
}

void ListRemoveAfter(LinkedList *list, Node *curNode)
{
    Node *sucNode;
    // Remove Head
    if (!curNode && list->head)
    {
        sucNode = list->head->next;
        list->head = sucNode;

        // Removed last item
        if (!sucNode)
        {
            list->tail = NULL;
        }
    }
    // Otherwise, remove node after current node
    else if (curNode->next)
    {
        sucNode = curNode->next->next;
        curNode->next = sucNode;

        // Removed the tail
        if (!sucNode)
        {
            list->tail = curNode;
        }
    }

    list->length--;
}

void ListPrint(LinkedList *list)
{
    Node *curNode = list->head;

    while (curNode)
    {
        cout << curNode->data << " ";
        curNode = curNode->next;
    }

    cout << endl;
}

LinkedList *CreateLinkedList()
{
    LinkedList *list = new LinkedList();
    int length;

    cout << "How many values would you like to add to your list? Enter -1 to use a randomly generated list" << endl;
    cin >> length;

    if (length == -1)
    {
        for (int i = 0; i < 10; i++)
        {
            Node *newNode = new Node();
            newNode->data = rand() % 100;
            ListAppend(list, newNode);
        }
    }

    for (int i = 0; i < length; i++)
    {
        int data;
        cout << "What value would you like to put into Node " << i << "?" << endl;
        cin >> data;
        Node *newNode = new Node();
        newNode->data = data;
        ListAppend(list, newNode);
    }

    return list;
}

void split(LinkedList *list, LinkedList *leftList, LinkedList *rightList)
{
    int midpoint = (list->length / 2) - 1;
    Node *curNode = list->head;
    for (int i = 0; i < list->length; i++)
    {
        // Store the nextNode in a temporary variable and
        // remove the current node's next pointer
        Node *nextNode = curNode->next;
        curNode->next = NULL;

        // Create the left and right lists
        if (i <= midpoint)
        {
            ListAppend(leftList, curNode);
        }
        else
        {
            ListAppend(rightList, curNode);
        }

        curNode = nextNode;
    }
}

LinkedList *merge(LinkedList *leftList, LinkedList *rightList)
{
    LinkedList *newList = new LinkedList();

    while (leftList->head && rightList->head)
    {
        // If the head of leftList is greater than the head of rightList,
        // then remove head node from rightList and add it to our newList
        if (leftList->head->data > rightList->head->data)
        {
            Node *rightListHead = rightList->head;
            ListRemoveAfter(rightList, NULL);
            ListAppend(newList, rightListHead);
        }
        // If the head of leftList is less than or equal to the head of rightList,
        // then remove head node from leftList and add it to our newList
        else
        {
            Node *leftListHead = leftList->head;
            ListRemoveAfter(leftList, NULL);
            ListAppend(newList, leftListHead);
        }
    }

    // If there are any elements left in leftList then empty it
    // into the newList
    while (leftList->head)
    {
        Node *leftListHead = leftList->head;
        ListRemoveAfter(leftList, NULL);
        ListAppend(newList, leftListHead);
    }

    // If there are any element left in rightList then empty it
    // into the newList
    while (rightList->head)
    {
        Node *rightListHead = rightList->head;
        ListRemoveAfter(rightList, NULL);
        ListAppend(newList, rightListHead);
    }

    return newList;
}

LinkedList *mergesort(LinkedList *list)
{
    LinkedList *leftList = new LinkedList();
    LinkedList *rightList = new LinkedList();

    // Base case! If the list has a length of one then
    // there is no need to continue
    if (!list->head->next)
    {
        return list;
    }

    split(list, leftList, rightList);

    leftList = mergesort(leftList);
    rightList = mergesort(rightList);

    return merge(leftList, rightList);
}

int main()
{
    LinkedList *list = CreateLinkedList();
    cout << "List: ";
    ListPrint(list);
    LinkedList *newList = mergesort(list);
    cout << "Sorted List: ";
    ListPrint(newList);
}