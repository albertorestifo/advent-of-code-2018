#include <stdio.h>
#include <stdlib.h>

int fabric[1000][1000];

typedef struct fabric_alloc {
    int id;
    int x1;
    int x2;
    int y1;
    int y2;
} fabric_alloc_t;

typedef struct node {
    fabric_alloc_t* val;
    struct node* next;
} node_t;

/*
 * Initialize an empty linked list
 */
void list_init(node_t** head)
{
    node_t* new_list;
    new_list = malloc(sizeof(node_t));
    if (new_list == NULL) {
        printf("failed to malloc list");
        exit(EXIT_FAILURE);
    }
    new_list->val = NULL;
    new_list->next = NULL;

    *head = new_list;
}

void push(node_t* head, fabric_alloc_t* val)
{
    if (head == NULL) {
        printf("NOT INITIALIZED!\n");
    }

    /* The list is still empty so we allocate the first value */
    if (head->val == NULL) {
        head->val = val;
        return;
    }

    node_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* Add the new value at the end of the list */
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

void parse_line(char* line, node_t* list)
{
    fabric_alloc_t* alloc = NULL;
    alloc = malloc(sizeof(fabric_alloc_t));

    int size_x = 0;
    int size_y = 0;
    sscanf(line, "#%d @ %d,%d: %dx%d", &alloc->id, &alloc->x1,
        &alloc->y1, &size_x, &size_y);

    alloc->x2 = alloc->x1 + size_x;
    alloc->y2 = alloc->y1 + size_y;

    push(list, alloc);
}

/*
 * Parse file input into a linked list
 */
void parse_input(node_t* list)
{
    FILE* file = fopen("puzzle.in", "r");
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

void allocate_fabric(fabric_alloc_t* alloc)
{
    int x, y = 0;

    for (x = alloc->x1; x <= alloc->x2; ++x) {
        for (y = alloc->y1; y <= alloc->y2; ++y) {
            fabric[x][y] += 1;
        }
    }
}

int count_overlaps(node_t* head)
{
    int overlapping = 0;
    node_t* current = head;

    while (current != NULL) {
        allocate_fabric(current->val);
        current = current->next;
    }

    // Calculate the number of overlapping squares
    int x, y = 0;
    for (x = 0; x < 1000; x += 1) {
        for (y = 0; y < 1000; y += 1) {
            if (fabric[x][y] > 1) {
                overlapping += 1;
            }
        }
    }

    return overlapping;
}

void print_fabric()
{
    int x, y = 0;
    for (x = 0; x < 1000; x += 1) {
        for (y = 0; y < 1000; y += 1) {
            char* sign = ".";
            if (fabric[x][y] > 0) {
                sign = "x";
            }
            printf("%s", sign);
        }
        printf("\n");
    }
}

int main()
{
    int overlapping = 0;
    node_t* list = NULL;

    list_init(&list);

    parse_input(list);

    overlapping = count_overlaps(list);
    print_fabric();
    printf("Overlapping assignments: %d\n", overlapping);

    return EXIT_SUCCESS;
}
