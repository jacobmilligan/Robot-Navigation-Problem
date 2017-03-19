//
//  VisualizerApp.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "VisualizerApp.hpp"

namespace robo {


VisualizerApp::VisualizerApp(const std::string& app_name, Environment& env,
                             ExploredSet& explored, SearchResults& results)
    : app_name_(app_name),
      window_(app_name, 100, 100, 1024, 800),
      graphics_(app_name),
      env_(env),
      explored_(explored),
      results_(results),
      tilesize_(64),
      speed_(2),
      timer_(speed_),
      current_node_(0)
{
    start_ = graphics_.get_rect(env.start.x * tilesize_, env.start.y * tilesize_, tilesize_, tilesize_);
    goal_ = graphics_.get_rect(env.goal.x * tilesize_, env.goal.y * tilesize_, tilesize_, tilesize_);
    node_rect_ = graphics_.get_rect(start_.x, start_.y, start_.w, start_.h);
}

void VisualizerApp::run()
{
    window_.initialize();
    graphics_.initialize(window_);
    graphics_.set_clear_color(Colors::white);

    while ( window_.is_open() ) {
        process_input();
        update();

        graphics_.clear();
        draw();
        graphics_.refresh();
    }
}

void VisualizerApp::process_input()
{
    while ( window_.poll_events(event_) ) {

        if ( event_.type == SDL_QUIT ) {
            window_.close();
        }

        if ( event_.type == SDL_KEYDOWN ) {

            switch (event_.key.keysym.sym) {
                case SDLK_ESCAPE:
                    window_.close();
                default: break;
            }

        }
    }
}

void VisualizerApp::update()
{
    if ( timer_ <= 0 ) {
        timer_ = speed_;

        if ( current_node_ < explored_.size() - 1 ) {
            current_node_++;
            auto node = explored_.get(current_node_).state;
            node_rect_.x = node.x * tilesize_;
            node_rect_.y = node.y * tilesize_;
            visited_[node] = true;
        }
    }

    timer_--;
}

void VisualizerApp::draw()
{
    draw_tiles();
    draw_path();

    graphics_.fill_rectangle(node_rect_, Colors::orange);
    graphics_.fill_rectangle(start_, Colors::red);
    graphics_.fill_rectangle(goal_, Colors::light_green);
}

void VisualizerApp::draw_tiles()
{
    SDL_Rect current;
    for ( int x = 0; x < env_.size().x; ++x ) {
        for ( int y = 0; y < env_.size().y; ++y ) {
            current.x = x * tilesize_;
            current.y = y * tilesize_;
            current.w = tilesize_;
            current.h = tilesize_;

            graphics_.draw_rectangle(current, Colors::black);

            if ( env_.get_cell(Point(x, y)) == Cell::wall ) {
                graphics_.fill_rectangle(current, Colors::gray);
            }

            if ( visited_.find(Point(x, y)) != visited_.end() ) {
                graphics_.fill_rectangle(current, Colors::light_blue);
            }
        }
    }
}

void VisualizerApp::draw_path()
{
    SDL_Rect rect;
    for ( auto& n : results_.path ) {
        rect.x = n.state.x * tilesize_;
        rect.y = n.state.y * tilesize_;
        rect.w = tilesize_;
        rect.h = tilesize_;

        if ( visited_.find(n.state) != visited_.end() ) {
            if ( current_node_ >= explored_.size() - 1 ) {
                graphics_.fill_rectangle(rect, Colors::green);
            } else {
                graphics_.fill_rectangle(rect, Colors::light_yellow);
            }
        }
    }
}

void VisualizerApp::set_tilesize(const int size)
{
    tilesize_ = size;

    start_.w = tilesize_;
    start_.h = tilesize_;
    start_.x = env_.start.x * tilesize_;
    start_.y = env_.start.y * tilesize_;

    goal_.w = tilesize_;
    goal_.h = tilesize_;
    goal_.x = env_.goal.x * tilesize_;
    goal_.y = env_.goal.y * tilesize_;

    node_rect_.w = tilesize_;
    node_rect_.h = tilesize_;
}

void VisualizerApp::set_speed(const int speed)
{
    speed_ = speed;
}


}