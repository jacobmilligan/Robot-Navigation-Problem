//
//  VisualizerMain.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "Search/Methods/AStar.hpp"
#include "Visualizer/VisualizerApp.hpp"

int main(int argc, char** argv)
{
    robo::VisualizerApp app("Robo-visualizer", 1, 32, argv);
    app.run();
    return 0;
}