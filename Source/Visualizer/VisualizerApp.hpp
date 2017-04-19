//
//  VisualizerApp.hpp
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

#include "Search/Core/SearchMethod.hpp"
#include "Visualizer/Text.hpp"
#include "Visualizer/PathRenderer.hpp"

namespace robo {

/// @brief InputState is a helper function for checking the current state of the
/// mouse and moving object
class InputState {
public:
    InputState() {}

    /// @brief Sets the input state to either moving all objects or moving none
    /// @param state The state
    void toggle_all(const bool state);

    /// @brief Sets the input state to moving a cell around
    /// @param cell Cell being placed
    void toggle_walls(const Cell cell);

    /// @brief Checks whether the start is being moved currently
    /// @return True if moving start, false otherwise
    inline bool moving_start()
    {
        return moving_start_;
    }

    /// @brief Checks whether the goal is being moved currently
    /// @return True if moving goal, false otherwise
    inline bool moving_goal()
    {
        return moving_goal_;
    }

private:
    bool placing_walls_;
    bool moving_start_;
    bool moving_goal_;
};

/// @brief VisualizerApp deines the main frame loop for the visualizer and
/// manages the lifetime and functionality of the application
class VisualizerApp {
public:
    /// @brief Initializes the visualizer and allocates resources
    /// @param app_name The applications name used for windowing
    /// @param speed The speed to animate each search method (number of frames per state)
    /// @param tilesize The size to make each tile
    /// @param argv The command line arguments
    VisualizerApp(const std::string& app_name, const int speed,
                  const int tilesize, char** argv);

    /// @brief Starts the main loop of the application - launching a window
    void run();
private:
    /// @brief Typedef for a map between keys and search methods
    using MethodKeyMap = std::unordered_map<SDL_Keycode, std::unique_ptr<robo::SearchMethod>>;

    /// @brief The applications name
    std::string app_name_;
    /// @brief The main window
    Window window_;
    /// @brief The graphics driver used for drawing
    GraphicsDriver graphics_;
    /// @brief The text renderer used for drawing strings
    TextRenderer text_;
    /// @brief The font to use in drawing text
    Font font_;

    SDL_Event event_;
    double last_time_; // used for calculating run-time

    bool is_evaluating_; ///< Whether the path is currently animating
    int tilesize_;
    int speed_;
    int timer_;

    /// @brief The renderer for drawing the search path
    PathRenderer path_;
    InputState input_;
    MethodKeyMap methods_; ///< maps keys to search methods

    Environment env_; ///< The current search environment being drawn
    Solution results_; ///< results from the last search executed
    robo::SearchMethod* current_method_; ///< pointer to the search method the user has chosen
    std::string method_str_; ///< string representation of the chosen search method
    sky::Path root_; ///< path to the application root
    std::vector<Node>::iterator operations_; ///< iterator for rendering search operations in order

    /// @brief Launches the window and initializes the graphics driver
    void initialize();
    /// @brief Handles all input processing
    void process_input();
    /// @brief Updates the visualizer, changing node positions and placing walls
    void update();
    /// @brief Draws the application
    void draw();
    /// @brief Draws the underlying grid to the window
    void draw_grid();
    /// @brief Draws walls and endpoints to the window
    void draw_features();

    /// @brief Gets the time delta for recording the execution time of the last
    /// search
    /// @param last The last time recorded
    /// @return The execution time
    double get_delta(const double last)
    {
        return ((SDL_GetPerformanceCounter() - last) * 1000) / SDL_GetPerformanceFrequency();
    }

    /// @brief Gets the statistics about the last search executed
    void evaluate_path();
    /// @brief Clears the path and its current animation from the window
    void clear_path();
    /// @brief Draws all of the information text to the window
    void draw_information();
};


}


