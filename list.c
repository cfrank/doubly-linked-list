#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/* Static functions */
static list_t *create_list(void);
static node_t *create_node(void *data);

/*
 * Initialize a new list
 */
list_t *create_list(void) {
    list_t *list = malloc(sizeof(list_t));
    list->head = NULL;
    list->size = 0;
    return list;
}

/*
 * Initialize a new node
 */
node_t *create_node(void *data) {
    node_t *node = malloc(sizeof(node_t));
    node->prev = NULL;
    node->next = NULL;
    node->data = data;
    return node;
}

/*
 * Function for creating a new list
 */
list_t *new_list(void) {
    return create_list();
}

/*
 * Push a node to the front of the list
 */
void push_front(list_t *list, void *data) {
    node_t *node = create_node(data);
    
    /* Check if the list is empty */
    if(list->size == 0) {
        /* In an empty list prev and next are the first node */
        node->prev = node;
        node->next = node;
    } else {
        node_t *head = list->head;
        
        /* Set the new nodes prev and next pointers */
        node->next = head;
        node->prev = head->prev;
        
        /* Set the previous and next pointer to the new node */
        head->prev = node;
        head->next = node;
    }
    
    list->head = node;
    ++list->size;
}

/*
 * Push a node to the back of the list
 *
 * This is almost identical to push_front
 * but the lists head is not set to the new node
 * (unless the list was empty)
 */
void push_back(list_t *list, void *data) {
    node_t *node = create_node(data);
    
    if(list->size == 0) {
        node->prev = node;
        node->next = node;
        
        /* Since this is the only node it will be the head by default */
        list->head = node;
    } else {
        node_t *head = list->head;
        
        node->next = head;
        node->prev = head->prev;
        
        head->prev = node;
        head->next = node;
    }
    
    ++list->size;
}

/*
 * Removes the first node in the list
 */
int remove_front(list_t *list, list_op free_func) {
    if(list->size == 0) {
        /* Can't remove anything from an empty list */
        return -1;
    }
    
    node_t *head = list->head;
    
    if(list->size == 1) {
        list->head = NULL;
    } else {
        node_t *next = head->next;
        node_t *prev = head->prev;
        
        list->head = next;
        
        next->prev = prev;
        prev->next = prev;
    }
    
    /* Provided free function */
    free_func(head->data);
    free(head);
    
    --list->size;
    
    return 0;
}

/*
 * Remove a node at the specified index
 */
int remove_index(list_t *list, unsigned int index, list_op free_func) {
    if(list->size == 0) {
        return -1;
    }
    
    // Start at index 0
    node_t *current_node = list->head;
    
    if(list->size == 1) {
        list->head = NULL;
    } else {
        /* Loop through until you get to the specified index */
        for(unsigned int i = 1; i < index; ++i) {
            current_node = current_node->next;
        }
        
        node_t *next = current_node->next;
        node_t *prev = current_node->prev;
        
        /* Update the pointers to remove the node */
        prev->next = next;
        next->prev = prev;
        
        free_func(current_node->data);
    }
    
    free_func(current_node->data);
    free(current_node);
    
    --list->size;
    
    return 0;
}

/*
 * Remove the last node in the list
 */
int remove_back(list_t *list, list_op free_func) {
    if(list->size == 0) {
        return -1;
    }
    
    node_t *head = list->head;
    node_t *to_remove = head->prev; /* Node which will be removed */
    
    if(list->size == 1) {
        list->head = NULL;
    } else {
        node_t *new_back = to_remove->prev; /* The new back */
        
        /* Update to reflect the new back */
        head->prev = new_back;
        new_back->prev = head;
    }
    
    free_func(to_remove->data);
    free(to_remove);
    
    --list->size;
    
    return 0;
}

/*
 * Get data from the front of the list
 */
void *get_front(list_t *list) {
    if(list->size == 0) {
        return NULL;
    }
    
    return list->head->data;
}

/*
 * Get data from an index in the list
 */
void *get_index(list_t *list, unsigned int index) {
    /* Check to make sure the is data at the index */
    if(!list->size || index >= list->size) {
        return NULL;
    }
    
    /* Loop through until you reach the requested index */
    node_t *current_node = list->head;
    for(unsigned int i = 0; i < index; ++i) {
        current_node = current_node->next;
    }
    
    return current_node->data;
}

/*
 * Get data from the back of the list
 */
void *get_back(list_t *list) {
    if(list->size == 0) {
        return NULL;
    }
    
    node_t *end = list->head->prev;
    return end->data;
}

/*
 * Check if the list is empty
 */
int is_empty(list_t *list) {
    return list->size == 0 && list->head == NULL;
}

/*
 * Return the length of the list
 */
int get_size(list_t *list) {
    return list->size;
}

void empty_list(list_t *list, list_op free_func) {
    if(list->size == 0) {
        return;
    }
    
    node_t *current_node = list->head;
    node_t *next = current_node->next;
    
    /* Loop through the list and free all the nodes */
    for(unsigned int i = 0; i < list->size; ++i) {
        free_func(current_node->data);
        free(current_node);
        current_node = next;
        
        /* If it's not the end of the list next needs to be reset */
        if(i < list->size - 1) {
            next = current_node->next;
        }
    }
    
    /* Reset the list to a clean state */
    list->head = NULL;
    list->size = 0;
}
