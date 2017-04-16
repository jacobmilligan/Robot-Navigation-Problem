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

#include "Visualizer/VisualizerApp.hpp"

#include "Search/Methods/BreadthFirst.hpp"
#include "Search/Methods/DepthFirst.hpp"
#include "Search/Methods/GreedyBestFirst.hpp"
#include "Search/Methods/AStar.hpp"
#include "Search/Methods/IDS.hpp"
#include "Search/Methods/IDAStar.hpp"

namespace robo {

VisualizerApp::VisualizerApp(const std::string& app_name, const int speed, const int tilesize, char** argv)
    : app_name_(app_name),
      window_(app_name, 100, 100, 1024, 800),
      graphics_(app_name),
      text_(graphics_),
      last_time_(0),
      is_evaluating_(false),
      tilesize_(tilesize),
      speed_(speed),
      timer_(speed_),
      path_(graphics_, tilesize),
      env_(1024 / tilesize, 800 / tilesize),
      method_str_("BFS"),
      root_(sky::Path::bin_path(argv))
{
    path_.update_goal_position(env_, 10, 10);
    path_.update_start_position(env_, 1, 1);
    path_.update_current_node_position(0, 0);
    path_.clear();

    methods_[SDLK_1] = std::make_unique<BreadthFirst>();
    methods_[SDLK_2] = std::make_unique<DepthFirst>();
    methods_[SDLK_3] = std::make_unique<GreedyBestFirst>();
    methods_[SDLK_4] = std::make_unique<AStar>();
    methods_[SDLK_5] = std::make_unique<IDS>();
    methods_[SDLK_6] = std::make_unique<IDAStar>();

    current_method_ = methods_[SDLK_1].get();
}

void VisualizerApp::run()
{
    initialize();

    while ( window_.is_open() ) {
        process_input();

        if ( !window_.is_open() )
            break;

        update();

        graphics_.clear();
        draw();
        graphics_.refresh();
    }

    path_.clear();

    SDL_Quit();
}

void VisualizerApp::initialize()
{
    window_.initialize();
    graphics_.initialize(window_);
    graphics_.set_clear_color(Colors::white);

    font_.load_from_file(root_.get_relative("SOURCECODEPRO.ttf"), 24);
}

void VisualizerApp::process_input()
{
    while ( window_.poll_events(event_) ) {

        if ( event_.type == SDL_QUIT ) {
            window_.close();
            return;
        }

        if ( event_.type == SDL_KEYDOWN ) {
            auto key = event_.key.keysym.sym;
            auto method = methods_.find(key);

            if ( method != methods_.end() ) {
                is_evaluating_ = false;
                current_method_ = method->second.get();
            }

            if ( key == SDLK_ESCAPE ) {
                window_.close();
                return;
            }

            if ( key == SDLK_RETURN )
                evaluate_path();

            if ( key == SDLK_SPACE )
                clear_path();
        }

        auto button = event_.button.button;
        auto x = event_.button.x / tilesize_;
        auto y = event_.button.y / tilesize_;

        if ( event_.type == SDL_MOUSEBUTTONDOWN && button == SDL_BUTTON_LEFT ) {
            input_.toggle_walls(env_.get_cell(Point(x, y)));
            path_.toggle_wall(env_, x, y);
        }

        if ( event_.type == SDL_MOUSEMOTION && button == SDL_BUTTON_LEFT ) {
            input_.toggle_walls(env_.get_cell(Point(x, y)));

            if ( input_.moving_start() )
                path_.update_start_position(env_, x, y);
            if ( input_.moving_goal() )
                path_.update_goal_position(env_, x, y);

            path_.update_walls(env_, x, y);
        }

        if ( event_.type == SDL_MOUSEBUTTONUP && button == SDL_BUTTON_LEFT )
            input_.toggle_all(false);
    }
}

void VisualizerApp::update()
{
    if ( !is_evaluating_ )
        return;

    if ( timer_ <= 0 ) {
        timer_ = speed_;

        if ( operations_->state != current_method_->explored().last_state()) {
            auto node = *operations_++;
            path_.update_current_node_position(node.state.x, node.state.y);
        } else {
            is_evaluating_ = false;
        }
    }

    timer_--;
}

void VisualizerApp::draw()
{
    draw_features();

    if ( path_.size() > 0 )
        path_.draw(results_, *operations_, env_);

    if ( is_evaluating_ )
        path_.draw_evaluating();

    path_.draw_endpoints();

    draw_grid();

    draw_information();
}

void VisualizerApp::draw_grid()
{
    SDL_Rect current;
    Cell curcel;
    Point curpoint;
    for ( int x = 0; x < env_.size().x; ++x ) {
        for ( int y = 0; y < env_.size().y; ++y ) {
            current.x = x * tilesize_;
            current.y = y * tilesize_;
            current.w = tilesize_;
            current.h = tilesize_;

            curpoint = Point(x, y);
            curcel = env_.get_cell(curpoint);

            if ( curcel == Cell::wall ) {
                graphics_.draw_rectangle(current, Colors::black);
            } else {
                graphics_.draw_rectangle(current, Colors::light_gray);
            }
        }
    }
}

void VisualizerApp::draw_features()
{
    SDL_Rect current;
    for ( int x = 0; x < env_.size().x; ++x ) {
        for ( int y = 0; y < env_.size().y; ++y ) {
            current.x = x * tilesize_;
            current.y = y * tilesize_;
            current.w = tilesize_;
            current.h = tilesize_;

            if ( env_.get_cell(Point(x, y)) == Cell::wall )
                graphics_.fill_rectangle(current, Colors::gray);

            if ( path_.has_visited(Point(x, y)) )
                graphics_.fill_rectangle(current, Colors::light_blue);
        }
    }
}

void VisualizerApp::clear_path()
{
    is_evaluating_ = false;
    last_time_ = 0.0;
    path_.clear();
}

void VisualizerApp::evaluate_path()
{
    last_time_ = SDL_GetPerformanceCounter();
    results_ = current_method_->search(env_);
    operations_ = current_method_->explored().operations_iterator();
    last_time_ = get_delta(last_time_);
    is_evaluating_ = true;
    path_.clear();
}

void VisualizerApp::draw_information()
{
    auto execution = "Execution time: " + std::to_string(last_time_) + "ms";
    auto pathlen = "Path length: " + std::to_string(results_.path.size());

    text_.draw_string(10, 1, current_method_->name(), font_, Colors::black);
    text_.draw_string(10, 750, execution, font_, Colors::black);
    text_.draw_string(720, 750, pathlen, font_, Colors::black);

    if ( path_.size() > 0 ) {
        auto nodes = "Nodes expanded: " + std::to_string(results_.node_count);
        text_.draw_string(720, 700, nodes, font_, Colors::black);

        auto frontier = "Largest frontier: " + std::to_string(results_.largest_frontier);
        text_.draw_string(720, 650, frontier, font_, Colors::black);
    }
}

void InputState::toggle_all(const bool state)
{
    placing_walls_ = state;
    moving_goal_ = state;
    moving_start_ = state;
}

void InputState::toggle_walls(const Cell cell)
{
    if ( moving_goal_ || moving_start_ )
        return;

    if ( !placing_walls_ ) {
        if ( cell == Cell::goal || cell == Cell::start ) {
            moving_start_ = (cell == Cell::start);
            moving_goal_ = (cell == Cell::goal);
        }

        placing_walls_ = true;
    }
}


}