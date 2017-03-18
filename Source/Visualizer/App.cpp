//
//  App.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "Visualizer/App.hpp"

namespace robo {


void VisualizerApp::initialize()
{
    clear_color = sky::Color(254, 254, 254);
}

void VisualizerApp::process_input()
{
    input.poll_events();
    if ( input.key_typed(sky::Key::escape) ) {
        is_running = false;
    }
}

void VisualizerApp::update(const float dt)
{
    
}

void VisualizerApp::draw(const float dt)
{
    shapes_.begin();

    for ( int x = 0; x < env_.size().x; ++x ) {
        for ( int y = 0; y < env_.size().y; ++y ) {
            shapes_.draw_rectangle(x * tilesize_,
                                   y * tilesize_,
                                   tilesize_,
                                   tilesize_,
                                   1,
                                   sky::Color::blue);

            if ( env_.get_cell(Point(x, y)) == Cell::wall ) {
                shapes_.fill_rectangle(x * tilesize_,
                                       y * tilesize_,
                                       tilesize_,
                                       tilesize_,
                                       sky::Color::gray);
            }

            if ( visited_.find(Point(x, y)) != visited_.end() ) {
                shapes_.fill_rectangle(x * tilesize_,
                                       y * tilesize_,
                                       tilesize_,
                                       tilesize_,
                                       sky::Color(175, 238, 238));
            }
        }
    }

    if ( current_node_ >= explored_.size() - 1 ) {
        for ( auto& n : results_.path ) {
            shapes_.fill_rectangle(n.state.x * tilesize_,
                                   n.state.y * tilesize_,
                                   tilesize_,
                                   tilesize_,
                                   sky::Color(255, 254, 106));
        }
    }

    shapes_.fill_rectangle(noderect_, sky::Color::orange);
    shapes_.fill_rectangle(start_, sky::Color::red);
    shapes_.fill_rectangle(goal_, sky::Color(152, 251, 152));

    timer_--;
    if ( timer_ < 0 ) {
        timer_ = speed_;

        if ( current_node_ < explored_.size() - 1 ) {
            current_node_++;
            auto node = explored_.get(current_node_).state;
            noderect_.position = sky::Vector2f(node.x * tilesize_, node.y * tilesize_);
            visited_[node] = true;
        }
    }

    shapes_.end();

}

void VisualizerApp::cleanup()
{

}


}
