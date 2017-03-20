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

namespace robo {

void print_error(const std::string& type, const std::string& msg)
{
    std::cerr << "[robonav] " << type
              << " error occurred: " << msg << std::endl;
}

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
      current_node_(0),
      path_(graphics_, tilesize),
      env_(1024 / tilesize, 800 / tilesize),
      current_method_(nullptr),
      method_str_("Breadth-first"),
      root_(sky::Path::bin_path(argv))
{
    methods_["Breadth-first"] = std::make_unique<robo::BreadthFirst>();
    methods_["Depth-first"] = std::make_unique<robo::DepthFirst>();
    methods_["Greedy Best-First"] = std::make_unique<robo::GreedyBestFirst>();
    methods_["A*"] = std::make_unique<robo::AStar>();

    path_.update_goal_position(env_, 10, 10);
    path_.update_start_position(env_, 1, 1);
    path_.update_current_node_position(0, 0);
    path_.clear();

    graphics_.set_error_callback(&print_error);
    window_.set_error_callback(&print_error);
    font_.set_error_callback(&print_error);
    text_.set_error_callback(&print_error);
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
}

void VisualizerApp::initialize()
{
    window_.initialize();
    graphics_.initialize(window_);
    graphics_.set_clear_color(Colors::white);

    font_.load_from_file(root_.get_relative("SourceCode.ttf"), 24);
}

void VisualizerApp::process_input()
{
    while ( window_.poll_events(event_) ) {

        if ( event_.type == SDL_QUIT ) {
            window_.close();
        }

        if ( event_.type == SDL_KEYDOWN ) {
            switch (event_.key.keysym.sym) {
                case SDLK_1:
                    method_str_ = "Breadth-first";
                    break;
                case SDLK_2:
                    method_str_ = "Depth-first";
                    break;
                case SDLK_3:
                    method_str_ = "Greedy Best-First";
                    break;
                case SDLK_4:
                    method_str_ = "A*";
                    break;
                case SDLK_ESCAPE:
                    window_.close();
                case SDLK_RETURN:
                    current_node_ = 0;
                    current_method_ = methods_[method_str_].get();
                    last_time_ = SDL_GetPerformanceCounter();
                    results_ = current_method_->search(env_);
                    last_time_ = get_delta(last_time_);
                    is_evaluating_ = true;
                    path_.clear();
                    break;
                case SDLK_SPACE:
                    current_method_ = nullptr;
                    current_node_ = 0;
                    is_evaluating_ = false;
                    last_time_ = 0.0;
                    path_.clear();
                    break;
                default: break;
            }
        }

        if ( event_.type == SDL_MOUSEBUTTONDOWN ) {
            if ( event_.button.button == SDL_BUTTON_LEFT ) {
                auto x = event_.button.x / tilesize_;
                auto y = event_.button.y / tilesize_;
                input_.toggle_walls(env_.get_cell(Point(x, y)));
                path_.toggle_wall(env_, x, y);
            }
        }

        if ( event_.type == SDL_MOUSEMOTION ) {
            if ( event_.button.button == SDL_BUTTON_LEFT ) {
                auto x = event_.button.x / tilesize_;
                auto y = event_.button.y / tilesize_;
                input_.toggle_walls(env_.get_cell(Point(x, y)));

                if ( input_.moving_start() ) {
                    path_.update_start_position(env_, x, y);
                } else if ( input_.moving_goal() ) {
                    path_.update_goal_position(env_, x, y);
                } else {
                    path_.update_walls(env_, x, y);
                }
            }
        }

        if ( event_.type == SDL_MOUSEBUTTONUP ) {
            if ( event_.button.button == SDL_BUTTON_LEFT ) {
                input_.toggle_all(false);
            }
        }
    }
}

void VisualizerApp::update()
{
    if ( is_evaluating_ && current_method_ != nullptr ) {
        if ( timer_ <= 0 ) {
            timer_ = speed_;

            if ( current_node_ < current_method_->explored().size() - 1 ) {
                current_node_++;
                auto node = current_method_->explored().get(current_node_);
                path_.update_current_node_position(node.state.x, node.state.y);
            } else {
                is_evaluating_ = false;
            }
        }

        timer_--;
    }
}

void VisualizerApp::draw()
{
    draw_tiles();
    if ( current_method_ != nullptr ) {
        path_.draw(results_, current_node_, current_method_->explored().size());
    }

    if ( is_evaluating_ ) {
        path_.draw_evaluating();
    }

    path_.draw_endpoints();

    text_.draw_string(1, 1, method_str_, font_, Colors::black);
    text_.draw_string(1, 750, "Execution time: " + std::to_string(last_time_) + "ms",
                      font_, Colors::black);
    text_.draw_string(800, 750, "Path length: " + std::to_string(results_.path.size()),
                      font_, Colors::black);
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

            if ( path_.has_visited(Point(x, y)) ) {
                graphics_.fill_rectangle(current, Colors::light_blue);
            }
        }
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
    if ( moving_goal_ || moving_start_ ) {
        return;
    }

    if ( !placing_walls_ ) {
        if ( cell == Cell::goal || cell == Cell::start ) {
            moving_start_ = cell == Cell::start;
            moving_goal_ = cell == Cell::goal;
        }

        placing_walls_ = true;
    }
}


}