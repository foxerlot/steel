#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "build.h"
#include "graph.h"
#include "utilities.h"

static int needs_rebuild(Node* node) {
    if (!file_exists(node->name))
        return 1;

    long target_time = file_mtime(node->name);

    for (int i = 0; i < node->dep_count; i++) {
        if (!file_exists(node->deps[i]))
            continue;

        if (file_mtime(node->deps[i]) > target_time)
            return 1;
    }

    return 0;
}

static int build_node(Node* node) {
    if (node->state == 1) {
        fprintf(stderr, COLOR_RED "Cycle detected at %s\n" COLOR_RESET, node->name);
        return 0;
    }

    if (node->state == 2)
        return 1;

    node->state = 1;

    for (int i = 0; i < node->dep_count; i++) {
        Node* dep = graph_get(node->deps[i]);
        if (dep) {
            if (!build_node(dep))
                return 0;
        }
    }

    if (needs_rebuild(node)) {
        printf(COLOR_GREEN "[BUILD] %s\n" COLOR_RESET, node->name);
        for (int i = 0; i < node->cmd_count; i++) {
            printf("  %s\n", node->commands[i]);
            if (system(node->commands[i]) != 0)
                return 0;
        }
    } else {
        printf(COLOR_GRAY "[SKIP] %s\n" COLOR_RESET, node->name);
    }

    node->state = 2;
    return 1;
}

int build_target(const char* target) {
    Node* node = graph_get(target);
    if (!node) {
        if (!file_exists(target)) {
            fprintf(stderr, "No rule for target '%s'\n", target);
            return 0;
        }
        return 1;
    }

    graph_reset_states();
    return build_node(node);
}
