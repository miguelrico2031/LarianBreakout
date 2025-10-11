#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

namespace Core
{
    class Game;
    class Text
    {
    public:
        Text() = default;
        void setString(const std::string& str, const sf::Font& font, unsigned int characterSize, bool centered);
        void clearString();
        void draw(sf::RenderTarget& target);
    public:
        sf::Vector2u Position;
    private:
        std::vector<std::unique_ptr<sf::Text>> m_lines;
        bool m_centered;
    };
}