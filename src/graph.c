#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include "graph.h"

static Node nodes[MAX_RULES];
static int node_count = 0;

int file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0;
}

long file_mtime(const char* path) {
    struct stat st;
    if (stat(path, &st) != 0)
        return 0;
    return st.st_mtime;
}

Node* graph_get(const char* name) {
    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, name) == 0)
            return &nodes[i];
    }
    return NULL;
}

Node* graph_add(const char* name) {
    Node* existing = graph_get(name);
    if (existing) return existing;

    if (node_count >= MAX_RULES) {
        fprintf(stderr, "Too many rules\n");
        return NULL;
    }

    Node* n = &nodes[node_count++];
    memset(n, 0, sizeof(Node));
    strncpy(n->name, name, sizeof(n->name) - 1);
    return n;
}

Node* graph_first() {
    if (node_count == 0) return NULL;
    return &nodes[0];
}

void graph_reset_states() {
    for (int i = 0; i < node_count; i++)
        nodes[i].state = 0;
}
