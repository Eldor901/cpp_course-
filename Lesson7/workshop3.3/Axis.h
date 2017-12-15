#pragma once

#include <SFML/Graphics.hpp>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

static const sf::Vector2f CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

void init(sf::VertexArray &axis, sf::RectangleShape &square);
void updateAxis(sf::VertexArray &axis, sf::Vector2f &mousePosition);