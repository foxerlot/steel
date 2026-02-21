#ifndef GRAPH_H
#define GRAPH_H

#include "utilities.h"

typedef struct Node {
    char name[128];

    char deps[MAX_DEPS][128];
    int dep_count;

    char commands[MAX_CMDS][256];
    int cmd_count;

    int state; // 0 = unvisited, 1 = visiting, 2 = done
} Node;

Node* graph_get(const char* name);
Node* graph_add(const char* name);
Node* graph_first();
void graph_reset_states();

int file_exists(const char* path);
long file_mtime(const char* path);

#endif
