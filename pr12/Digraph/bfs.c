#include "bfs.h"
#include "paths_helper.h"
#include "queue.h"

void bfs_search(const DigraphPtr g, PathsPtr p, vertex_t s) {
    QueuePtr q = QueueInit();

    p->marked[s] = true;
    enqueue(q, s);

    while (!QueueEmpty(q)) {
        vertex_t v = dequeue(q);
        int size = 0;
        const vertex_t *adj = DigraphAdj(g, v, &size);

        for (int i = 0; i < size; ++i) {
            vertex_t w = adj[i];
            if (!p->marked[w]) {
                enqueue(q, w);
                p->marked[w] = true;
                p->edge_to[w] = v;
            }
        }
    }

    QueueDestroy(q);
}

PathsPtr bfs(const DigraphPtr g, vertex_t s) {
    PathsPtr p = fromDigraph(g, s);

    bfs_search(g, p, s);
    return p;
}
