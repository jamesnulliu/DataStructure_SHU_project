#include "OrthogonalList/OrthogonalList.h"

#include "GrpahSolutions.h"

namespace graph {
    bool S02::solve(std::istream& in) const {
        orthogonal::Graph<char, int> graph(nullptr, 0);
        int option;
        while (true) {
            sgc::cout() << "\n1: insert vertex\n2: erase vertex\n3: insert arc\n4: erase arc\n"
                << "5: display graph\n6: topological sorting\n7: exit\n";
            sgc::cin(7) >> option;
            switch (option) {
            case 1: {
                int vertNum{};
                sgc::cout() << "Vertex Number: ";
                sgc::cin(2) >> vertNum;
                while (vertNum--) {
                    char vertex;
                    sgc::cin(2) >> vertex;
                    graph.InsertVertex(vertex);
                }
                break;
            }
            case 2: {
                char vertex;
                sgc::cin(2) >> vertex;
                graph.DeleteVertex(vertex);
                break;
            }
            case 3: {
                int arcNum{};
                sgc::cout() << "Arc Number: ";
                sgc::cin(2) >> arcNum;
                while (arcNum--) {
                    int v1, v2;
                    int weight;
                    sgc::cin() >> v1 >> v2 >> weight;
                    graph.InsertArc(v1, v2, weight);
                }
                break;
            }
            case 4: {
                int v1, v2;
                sgc::cin() >> v1 >> v2;
                graph.DeleteArc(v1, v2);
                break;
            }
            case 5: {
                graph.Display();
                break;
            }
            case 6: {
                int vertNum = graph.GetVertexNum();
                int* result = new int[vertNum] {0};
                graph.topologicalSorting(result);
                for (int i = 1; i <= vertNum; i++) {
                    for (int j = 0; j < vertNum; j++) {
                        if (result[j] == i) {
                            sgc::cout(4) << graph.GetElem(j) << "-->";
                        }
                    }
                }
                sgc::cout() << "\b\b\b   \n";
                break;
            }
            case 7: {
                return false;
            }
            default:
                break;
            }
        }
        return true;
    }
}