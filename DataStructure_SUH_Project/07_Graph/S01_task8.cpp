#include "GrpahSolutions.h"

namespace graph {
    using int64 = long long;

    constexpr int64 maxVertNum = 109;

    int64 vertNum, lineNum;
    int64 dist[maxVertNum][maxVertNum];
    double I[maxVertNum];
    int64 cnt[maxVertNum][maxVertNum];

    void graphInit()
    {
        std::fill(dist[0], dist[0] + maxVertNum * maxVertNum, LLONG_MAX / 2);
        for (int64 i = 1; i <= vertNum; ++i) {
            dist[i][i] = 0;
        }
        std::fill(cnt[0], cnt[0] + maxVertNum * maxVertNum, 0);
        std::fill(I, I + maxVertNum * maxVertNum, 0);
    }

    void floyd()
    {
        for (int64 k = 1; k <= vertNum; ++k) {
            for (int64 i = 1; i <= vertNum; ++i) {
                for (int64 j = 1; j <= vertNum; ++j) {
                    int64 tempDist = dist[i][k] + dist[k][j];
                    // If dist[i][j] is already the shortest path:
                    if (dist[i][j] == tempDist) {
                        // Add the number of paths from i to j that pass through k to origin number of paths.
                        cnt[i][j] += cnt[i][k] * cnt[k][j];
                    }
                    // Or if dist[i][j] is not the shortest path:
                    else if (dist[i][j] > tempDist) {
                        // Update dist[i][j].
                        dist[i][j] = tempDist;
                        // Update the number of paths from i to j that pass through k.
                        cnt[i][j] = cnt[i][k] * cnt[k][j];
                    }
                }
            }
        }

        // [Note] ======================================================================
        // Given formula:
        // I(v) = sigma(s != v && t != v && t != s) { (cnt[s][v] * cnt[v][t]) / cnt[s][t] }
        // v and s and t are vertices in the graph.
        // =============================================================================

        // For every vertex v, calculate I[v]:
        for (int64 v = 1; v <= vertNum; ++v) {
            for (int64 s = 1; s <= vertNum; ++s) {
                if (s == v) continue;
                for (int64 t = 1; t <= vertNum; ++t) {
                    if (t == v || t == s) continue;
                    // If dist[s][t] is not the shortest path, continue.
                    if (dist[s][t] != dist[s][v] + dist[v][t]) continue;
                    // Calculate I[v].
                    I[v] += (double)cnt[s][v] * cnt[v][t] / cnt[s][t];
                }
            }
        }
    }

    void S01::solve(std::istream& in) const
    {
        if (&in == &std::cin) {
            sgc::cout() << "Input number of vertices and number of lines, saperated by space or enter: ";
            sgc::setConColor(2);
        }
        in >> vertNum >> lineNum;
        graphInit();
        for (int64 i = 1; i <= lineNum; ++i) {
            int64 a, b, c;
            in >> a >> b >> c;
            dist[a][b] = dist[b][a] = c;
            cnt[a][b] = cnt[b][a] = 1;
        }
        if (&in == &std::cin) { sgc::flushInputBuffer(); }
        floyd();
        sgc::cout(4) << "\nResult:\n";
        for (int64 i = 1; i <= vertNum; ++i) {
            printf("%.3lf\n", I[i]);
        }
        sgc::setConColor();
        std::cin.get();
    }
}