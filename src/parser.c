/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilities.h"
#include "graph.h"

int parse_file(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) DIE("Failed to open Steelfile");

    char *line = NULL;
    Node* current = NULL;
    size_t len = 0;
    ssize_t nread;

    while ((nread = getline(&line, &len, f)) != -1) {
        if (line[0] == '\n' || line[0] == '#')
            continue;

        if (line[0] == '\t' || line[0] == ' ') {
            if (!current) continue;
            line[strcspn(line, "\n")] = 0;
            strcpy(current->commands[current->cmd_count++], line + 1);
            continue;
        }

        char* colon = strchr(line, ':');
        if (colon) {
            *colon = 0;

            char target[128];
            sscanf(line, "%127s", target);

            current = graph_add(target);

            char* dep = colon + 1;
            char* token = strtok(dep, " \n");
            while (token) {
                strcpy(current->deps[current->dep_count++], token);
                token = strtok(NULL, " \n");
            }
        }
    }

    fclose(f);
    return 1;
}
