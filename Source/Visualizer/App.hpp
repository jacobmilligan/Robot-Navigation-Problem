//
//  App.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#pragma once

#include "Search/SearchMethod.hpp"

#include <Skyrocket/Framework/Application.hpp>

namespace robo {


class VisualizerApp : public sky::Application {
public:
    VisualizerApp(const std::string& path, Environment& env, ExploredSet& explored,
                  SearchResults& results)
        : Application(path.c_str()),
          timer_(speed_),
          current_node_(0),
          env_(env),
          explored_(explored),
          results_(results),
          shapes_(graphics_driver),
          start_(env.start.x * tilesize_, env.start.y * tilesize_, tilesize_, tilesize_),
          goal_(env.goal.x * tilesize_, env.goal.y * tilesize_, tilesize_, tilesize_),
          noderect_(start_.position, start_.width, start_.height)
    {}

protected:

    void initialize() override;

    void process_input() override;

    void update(const float dt) override;

    void draw(const float dt) override;

    void cleanup() override;

private:
    static const int tilesize_ = 64;
    static const int speed_ = 2;
    int timer_;
    int current_node_;

    Environment& env_;
    ExploredSet& explored_;
    SearchResults& results_;

    sky::ShapeBatch shapes_;

    sky::FloatRect start_;
    sky::FloatRect goal_;
    sky::FloatRect noderect_;

    std::unordered_map<Point, bool, PointHash> visited_;
};


}


