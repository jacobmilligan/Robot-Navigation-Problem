//
//  Environment.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  14/03/2017
//


#pragma once

#include "Search/Core/Types.hpp"
#include "SearchMethod.hpp"

#include <vector>
#include <array>

namespace robo {

struct ExploredSet;

/// @brief Enumeration of all valid cell states
enum class Cell {
    /// @brief Empty cell
    empty = 0,
    /// @brief The starting position
    start,
    /// @brief The goal position
    goal,
    /// @brief A wall - unpassable
    wall
};

/// @brief Turns an action direction into its string representation
/// @param dir The direction to get a string representation of
/// @return String representation of the action
std::string direction_to_string(const Action dir);

/// @brief Environment represents a 2 dimensional grid with a start position,
/// goal position, and walls. It also defines several helper methods.
class Environment {
public:
    /// @brief The step cost of moving from one cell to another
    int step_cost;
    /// @brief The starting position
    Point start;
    /// @brief The goal position
    Point goal;

    /// @brief Default constructor
    Environment();

    /// @brief Initializes the environment with a given size
    /// @param cols Number of columns
    /// @param rows Number of rows
    Environment(const unsigned int cols, const unsigned int rows);

    /// @brief Gets a point representation of the size of the grid
    /// @return The size of the grid
    inline Point size() const
    {
        return size_;
    }

    /// @brief Overloads the subscript operator for direct access to cells
    /// @param index The index
    /// @return A vector of cells, the row
    std::vector<Cell>& operator[](const unsigned long index)
    {
        return grid_[index];
    }

    /// @brief Const overload for the subscript operator for direct access to cells
    /// @param index The index
    /// @return A vector of cells, the row
    const std::vector<Cell>& operator[](const unsigned long index) const
    {
        return grid_[index];
    }

    /// @brief Checks whether the grid is a valid specification or not
    /// @return True if valid grid, false otherwise
    inline bool valid()
    {
        return valid_;
    }

    /// @brief Gets a reference to a list of available actions for a search
    /// method to take in the grid
    /// @return The valid actions
    inline const std::array<Action, 4>& actions() const
    {
        return actions_;
    }

    /// @brief Checks if the given point is inside the grids bounds
    /// @param p The point to check
    /// @return True if in the bounds, false otherwise
    inline bool in_bounds (const Point& p) const
    {
        return (p.x >= 0 && p.x < size_.x && p.y >= 0 && p.y < size_.y);
    }

    /// @brief Checks if a given point in the grid is passable, i.e. no wall and
    /// inside the grids bounds
    /// @param p The point to check
    /// @return True if passable, false otherwise
    inline bool passable(const Point& p) const
    {
        return in_bounds(p) && grid_[p.y][p.x] != Cell::wall;
    }

    /// @brief Gets the cell enumeration for a given point in the grid
    /// @param p The point
    /// @return The cell at the point specified
    inline Cell get_cell(const Point& p) const
    {
        return grid_[p.y][p.x];
    }

    /// @brief Sets the cell state of a given point in the grid
    /// @param x The points x position
    /// @param y The points y position
    /// @param cell The cell state to assign
    inline void set_cell(const int x, const int y, const Cell cell)
    {
        grid_[y][x] = cell;
    }

    /// @brief Checks if a given point is the goal or not
    /// @param pos The point to check
    /// @return True if it's the goal, false otherwise
    bool goal_test(const Point& pos) const;

private:
    bool valid_;
    Point size_;
    std::vector<std::vector<Cell>> grid_;

    /// @brief Expands nodes in the order Up, left, down, right as according
    // to the assignment specs
    std::array<Action, 4> actions_ = {
        {Action::up, Action::left, Action::down, Action::right}
    };
};


}