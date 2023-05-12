#include <cstdio>
#include "07_Graph/GrpahSolutions.h"
#include "08_Serach/Search_02.hpp"
#include "08_Serach/Search_04.hpp"
#include "08_Serach/Search_07.hpp"
#include "09_Sort/Sort_01.hpp"
#include "UserInterface/Main.hpp"
#include "Tools/Random.hpp"

int main()
{
    auto& mainWindow = dsp::Main::getMain();
    mainWindow.addProj(
        'a',
        dsp::Proj{
            "Graph",
            {&graph::S01::getSolution(), &graph::S02::getSolution()}
        }
    );

    mainWindow.addProj(
        'b',
        dsp::Proj{
            "Search",
            {
                &search::Task02::getSolution(),
                &search::Task04::getSolution(),
                &search::Task07::getSolution()
            }
        }
    );

    mainWindow.addProj(
        'c',
        dsp::Proj{
            "Sort",
            {
                &dsp::sort::Task01::getSolution()
            }
        }
    );

    mainWindow.refresh_loop();

    sgc::setConColor();
}