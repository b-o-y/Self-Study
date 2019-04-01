/**
 * Integer linked list example
 * CSE 374
 */

#include <stdio.h>
#include <stdlib.h>

// A single list node that stores an integer as data.
typedef struct IntListNode {
  int data;
  struct IntListNode* next;
} IntListNode;


// Allocates a new node on the heap.
IntListNode* makeNode(int data, IntListNode* next);

// Builds a heap-allocated linked list with the values in the array.
IntListNode* fromArray(int* array, int length);

// Frees all nodes in the linked list.
void freeList(IntListNode* list);

// Prints the contents of the linked list.
void printList(IntListNode* list);

// Returns whether the list has a node with the given target value as data.
int contains(IntListNode* list, int target);

// Returns the number of elements in the linked list.
int size(IntListNode* list);

// Removes all nodes with the target value from the list. Returns the
// new front of the list (might be different if the removed node was
// at the front).
IntListNode* removeFromList(IntListNode* list, int target);

int main(int argc, char **argv) {
  int arr1[3] = {1, 2, 3};
  IntListNode* list1 = fromArray(arr1, 3);
  printList(list1);
  printf("Size of list = %d\n", size(list1));
  printf("List contains 4 = %d\n", contains(list1, 4));

  int arr2[4] = {4, 3, 2, 1};
  IntListNode* list2 = fromArray(arr2, 4);
  list2 = removeFromList(list2, 4);
  printList(list2);
  printf("Size of list = %d\n", size(list2));
  printf("List contains 4 = %d\n", contains(list2, 4));

  // If you comment out these two lines and run valgrind,
  // you will see that valgrind finds a memory leak!
  freeList(list1);
  freeList(list2);
  return EXIT_SUCCESS;
}

IntListNode* makeNode(int data, IntListNode* next) {
  IntListNode* n = (IntListNode*) malloc(sizeof(IntListNode));
  n->data = data;
  n->next = next;
  return n;
}

IntListNode* fromArray(int* array, int length) {
  IntListNode* front = NULL;
  for (int i = length - 1; i >= 0; i--) {
    front = makeNode(array[i], front);
  }
  return front;
}

void freeList(IntListNode* list) {
  while (list != NULL) {
    IntListNode* next = list->next;
    free(list);
    list = next;
  }
}

void printList(IntListNode* list) {
  printf("[");
  while (list != NULL) {
    printf(" %d", list->data);
    list = list->next;
  }
  printf(" ]\n");
}

int contains(IntListNode* list, int target) {
  while (list != NULL) {
    if (list->data == target) {
      return 1;
    }
    list = list->next;
  }
  return 0;
}

int size(IntListNode* list) {
  int numElements = 0;
  while (list != NULL) {
    numElements++;
    list = list->next;
  }
  return numElements;
}

IntListNode* removeFromList(IntListNode* list, int target) {
  // Remove from the front if target is at the front.
  while (list != NULL && list->data == target) {
    IntListNode* removed = list;
    list = list->next;
    free(removed);
  }
  // Iterate through the list, staying one step ahead so we
  // can change the "next" pointer to skip the removed node.
  IntListNode* current = list;
  while (current != NULL && current->next != NULL) {
    if (current->next->data == target) {
      IntListNode* removed = current->next;
      current->next = current->next->next;
      free(removed);
    } else {
      current = current->next;
    }
  }
  return list;
}
