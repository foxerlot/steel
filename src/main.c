#include <stdio.h>
#include "parser.h"
#include "graph.h"
#include "build.h"

int main(int argc, char* argv[]) {
    if (!parse_file("Steelfile"))
        return 1;

    Node* first = graph_first();
    if (!first) DIE("No rules found.");

    const char* target = (argc > 1) ? argv[1] : first->name;

    if (!build_target(target))
        return 1;

    return 0;
}
