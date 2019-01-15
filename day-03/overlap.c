#include <stdio.h>
#include <stdlib.h>

#define ALLOCATED 1
#define NOT_ALLOCATED 0

int fabric[1000][1000];

typedef struct fabric_alloc {
        int id;
        int x1;
        int x2;
        int y1;
        int y2;
} fabric_alloc_t;

typedef struct node {
        fabric_alloc_t *val;
        struct node *next;
} node_t;

/*
 * Initialize an empty linked list
 */
void list_init(node_t *list) {
        list = malloc(sizeof(node_t));
        if (list == NULL) {
                printf("failed to malloc list");
                exit(EXIT_FAILURE);
        }
        list->val = NULL;
        list->next = NULL;
}

void push(node_t *list, fabric_alloc_t *val) {
        /* The list is still empty so we allocate the first value */
        if (list->val == NULL) {
                list->val = val;
                return;
        }

        node_t *current = list;
        while (current->next != NULL) {
                current = current->next;
        }

        /* Add the new value at the end of the list */
        current->next = malloc(sizeof(node_t));
        current->next->val = val;
        current->next->next = NULL;
}

/*
 * Parse file input into a linked list
 */
void parse_input(node_t *list) {
        FILE *file = fopen("puzzle.in", "r");
        if (!file) {
                fprintf(stderr, "could not open input file");
                exit(EXIT_FAILURE);
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
                parse_line(line, list);
        }
        fclose(file);
}

void parse_line(char *line, node_t *list) {}

int main() {}
