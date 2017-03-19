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
      is_evaluating_(false),
      is_start_moving_(false),
      is_goal_moving_(false),
      placing_walls_(false),
      tilesize_(tilesize),
      speed_(speed),
      timer_(speed_),
      current_node_(0),
      env_(1024 / tilesize, 800 / tilesize),
      current_method_(nullptr),
      method_str_("Breadth-first"),
      root_(sky::Path::bin_path(argv))
{
    methods_["Breadth-first"] = std::make_unique<robo::BreadthFirst>();
    methods_["Depth-first"] = std::make_unique<robo::DepthFirst>();
    methods_["Greedy Best-First"] = std::make_unique<robo::GreedyBestFirst>();
    methods_["A*"] = std::make_unique<robo::AStar>();

    env_.start = Point(1, 1);
    env_.set_cell(1, 1, Cell::start);
    env_.set_cell(10, 10, Cell::goal);
    start_ = get_tile(1, 1);
    goal_ = get_tile(10, 10);

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
        update();

        graphics_.clear();
        draw();
        graphics_.refresh();
    }
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
                    results_ = current_method_->search(env_);
                    is_evaluating_ = true;
                    visited_.clear();
                    break;
                case SDLK_SPACE:
                    current_method_ = nullptr;
                    current_node_ = 0;
                    is_evaluating_ = false;
                    visited_.clear();
                    break;
                default: break;
            }
        }

        if ( event_.type == SDL_MOUSEBUTTONDOWN ) {
            if ( event_.button.button == SDL_BUTTON_LEFT ) {
                toggle_wall();
            }
        }

        if ( event_.type == SDL_MOUSEMOTION ) {
            if ( event_.button.button == SDL_BUTTON_LEFT ) {
                batch_place_walls();
            }
        }

        if ( event_.type == SDL_MOUSEBUTTONUP ) {
            if ( event_.button.button == SDL_BUTTON_LEFT ) {
                is_start_moving_ = false;
                is_goal_moving_ = false;
                placing_walls_ = false;
            }
        }
    }
}

void VisualizerApp::update()
{
    if ( is_evaluating_ && current_method_ != nullptr ) {
        update_path();
    }
}

void VisualizerApp::draw()
{
    draw_tiles();
    if ( current_method_ != nullptr )
        draw_path();

    if ( is_evaluating_ ) {
        graphics_.fill_rectangle(node_rect_, Colors::orange);
    }

    graphics_.fill_rectangle(start_, Colors::red);
    graphics_.fill_rectangle(goal_, Colors::light_green);

    text_.draw_string(1, 1, method_str_, font_, Colors::black);
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
            if ( current_node_ >= current_method_->explored().size() - 1 ) {
                graphics_.fill_rectangle(rect, Colors::green);
            } else {
                graphics_.fill_rectangle(rect, Colors::light_yellow);
            }
        }
    }
}

void VisualizerApp::update_path()
{
    if ( timer_ <= 0 ) {
        timer_ = speed_;

        if ( current_node_ < current_method_->explored().size() - 1 ) {
            current_node_++;
            auto node = current_method_->explored().get(current_node_).state;
            node_rect_.x = node.x * tilesize_;
            node_rect_.y = node.y * tilesize_;
            visited_[node] = true;
        } else {
            is_evaluating_ = false;
        }
    }

    timer_--;
}

void VisualizerApp::toggle_wall()
{
    auto x = event_.button.x / tilesize_;
    auto y = event_.button.y / tilesize_;
    auto cell = env_.get_cell(Point(x, y));

    if ( is_start_moving_ || is_goal_moving_ ) {
        return;
    }

    if ( !placing_walls_ ) {
        if ( cell == Cell::goal || cell == Cell::start ) {
            is_start_moving_ = cell == Cell::start;
            is_goal_moving_ = cell == Cell::goal;
        }

        placing_walls_ = true;
    }

    auto new_val = ( cell == Cell::wall ) ? Cell::empty : Cell::wall;
    env_.set_cell(x, y, new_val);
}

void VisualizerApp::batch_place_walls()
{
    auto x = event_.button.x / tilesize_;
    auto y = event_.button.y / tilesize_;

    auto cell = env_.get_cell(Point(x, y));
    if ( !placing_walls_ ) {
        if ( cell == Cell::goal || cell == Cell::start ) {
            is_start_moving_ = cell == Cell::start;
            is_goal_moving_ = cell == Cell::goal;
        }

        placing_walls_ = true;
    }

    if ( is_start_moving_ ) {
        env_.set_cell(start_.x / tilesize_, start_.y / tilesize_, Cell::empty);
        start_.x = x * tilesize_;
        start_.y = y * tilesize_;
        env_.start = Point(x, y);
        env_.set_cell(x, y, Cell::start);
    } else if ( is_goal_moving_ ) {
        env_.set_cell(goal_.x / tilesize_, goal_.y / tilesize_, Cell::empty);
        goal_.x = x * tilesize_;
        goal_.y = y * tilesize_;
        env_.set_cell(x, y, Cell::goal);
    } else {
        env_.set_cell(x, y, Cell::wall);
    }

}

SDL_Rect VisualizerApp::get_tile(const int x, const int y)
{
    return graphics_.get_rect(x * tilesize_, y * tilesize_, tilesize_, tilesize_);
}

}