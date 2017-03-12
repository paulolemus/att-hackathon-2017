#ifndef SHOVESTER_CORE_POINTERINPUT_H
#define SHOVESTER_CORE_POINTERINPUT_H

#include <chrono>

#include <SDL2/SDL.h>

#include "shovester/core/Input.h"

struct PointerOutput {

    /// @brief The tap represents a direction.
    enum class Action {
        TAP,
        HOLD,
        FLICK
    };

    /// @brief A helper structure to describe the X/Y coordinates.
    struct Vec2 {
        double x;
        double y;
    };

    /// @brief The type of action that occured.
    Action action;
    /// @brief The beginning position of the Tap or Hold.
    Vec2 position;
    /// @brief The veclocity of the Flick. Usually 0 otherwise.
    Vec2 velocity;
};

class PointerInput : public Input<SDL_Event&, PointerOutput>  {

    enum class State {
        IDLE,
        TAPPED_WAITING,
        HOLDING,
    };

    /// Setup the pointer input
    PointerInput() {
        state = State::IDLE;
        last_time = std::chrono::high_resolution_clock::now();
    }

    virtual void handle(SDL_Event& inputFormat) override {
        using clock = std::chrono::high_resolution_clock;
        SDL_PumpEvents();

        PointerOutput po;

        auto current_time = clock::now();
        std::chrono::duration<double> delta = current_time - last_time;

        if (delta.count() > 0.8 && state == State::TAPPED_WAITING) { 
            state = State::HOLDING;
            po.action = PointerOutput::Action::HOLD;
        }

        // If we have a mouse button down, then go into the
        // TAPPED_WAITING state if we are waiting to see
        // when it releases.
        if (inputFormat.type == SDL_MOUSEBUTTONDOWN) {
            if (inputFormat.button.button == SDL_BUTTON_LEFT) {
                // If we have pressed a button for the first
                // time, wait until we release it.
                if (state == State::IDLE) {
                    last_time = clock::now();
                    state = State::TAPPED_WAITING;
                } 
            }
        } else if (inputFormat.type == SDL_MOUSEBUTTONUP) {
            if (inputFormat.button.button == SDL_BUTTON_LEFT) {
                // If we are releasing while TAPPED_WAITING,
                // it's a move.
                if (state == State::TAPPED_WAITING) {
                    if (delta.count() <= 0.8) {
                        po.action = PointerOutput::Action::TAP;
                        po.position.x = inputFormat.motion.xrel;
                        po.position.y = inputFormat.motion.yrel;
                    }
                    
                }
            }
        } else if (inputFormat.type == SDL_MOUSEMOTION) {
            if (state == State::TAPPED_WAITING) {
                 
            }
        }
    }

    PointerOutput outputFormat; 
    std::chrono::high_resolution_clock::time_point last_time;
    State state;
};

#endif // SHOVESTER_CORE_POINTERINPUT_H
