//
//  Text.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  20/03/2017
//

#include "Visualizer/Text.hpp"

namespace robo {


void Font::load_from_file(const sky::Path& path, const int fontsize)
{
    path_ = path;
    ttf_ = TTF_OpenFont(path_.c_str(), fontsize);
    if ( ttf_ == nullptr ) {
        error_callback_("Font", TTF_GetError());
        return;
    }
}

void Font::set_error_callback(Font::error_callback_t error_callback)
{
    error_callback_ = error_callback;
}

Font::~Font()
{
    if ( TTF_WasInit() ) {
        TTF_CloseFont(ttf_);
    }
}


void TextRenderer::draw_string(const int x,
                               const int y,
                               const std::string& str,
                               Font& font,
                               const SDL_Color& color)
{
    auto surface = TTF_RenderText_Blended(font.ptr(), str.c_str(), color);
    if ( surface == nullptr ) {
        error_callback_("Text renderer", "Unable to generate surface for drawing");
        return;
    }

    auto texture = graphics_->generate_texture(surface);
    if ( texture == nullptr ) {
        error_callback_("Text renderer", "Unable to generate texture for drawing");
        return;
    }

    SDL_FreeSurface(surface);

    graphics_->draw_texture(texture, x, y);
}

void TextRenderer::set_error_callback(error_callback_t error_callback)
{
    error_callback_ = error_callback;
}


}