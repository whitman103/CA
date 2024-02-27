#ifndef SHAPE_ARRAY_HPP
#define SHAPE_ARRAY_HPP

#include "color.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <random>

class SquareSystem : public sf::Drawable, public sf::Transformable
{
  public:
    int total_shapes;
    int xSize, ySize;
    int width = 8;
    int spacing = 10;
    int vertexNumber{4};
    SquareSystem() : xSize(-1), ySize(-1){};
    SquareSystem(unsigned int xSize, unsigned int ySize) : xSize(xSize), ySize(ySize), total_shapes(xSize * ySize)
    {
        this->m_vertices.setPrimitiveType(sf::Quads);
        this->m_vertices.resize(xSize * ySize * 4);
    }
    sf::VertexArray m_vertices;

    void init()
    {
        for (int i{0}; i < xSize; i += 1)
        {
            for (int j{0}; j < ySize; j += 1)
            {
                this->m_vertices[(i * ySize + j) * 4].position = sf::Vector2f(i * spacing, j * spacing);
                this->m_vertices[(i * ySize + j) * 4 + 1].position = sf::Vector2f(i * spacing + width, j * spacing);
                this->m_vertices[(i * ySize + j) * 4 + 2].position =
                    sf::Vector2f(i * spacing + width, j * spacing + width);
                this->m_vertices[(i * ySize + j) * 4 + 3].position = sf::Vector2f(i * spacing, j * spacing + width);
                const sf::Color vertexColor(255, 255, 255, 175);
                for (int vertexIndex{0}; vertexIndex < this->vertexNumber; vertexIndex++)
                {
                    this->m_vertices[(i * ySize + j) * 4 + vertexIndex].color = vertexColor;
                }
            }
        }
    }

    void update(int xSite, int ySite, const RGBA color)
    {
        for (int quadIndex = 0; quadIndex < this->vertexNumber; ++quadIndex)
        {
            m_vertices[(xSite * ySize + ySite) * 4 + quadIndex].color = sf::Color(color[0], color[1], color[2], 255);
        }
    }

  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(m_vertices, states);
    }
};

double deg_cos(const double degrees)
{
    return cos(M_PI / 180 * degrees);
};

double deg_sin(const double degrees)
{
    return sin(M_PI / 180 * degrees);
};

class HexSystem : public sf::Drawable, public sf::Transformable
{
  public:
    int total_shapes;
    int xSize, ySize;
    int vertexNumber{12};
    double shrink_factor{0.90};
    double inRadius{6.5}, circumradius{2. / sqrt(3) * inRadius};
    double render_circumradius{shrink_factor * circumradius};
    HexSystem() : xSize(-1), ySize(-1){};
    HexSystem(unsigned int xSize, unsigned int ySize) : xSize(xSize), ySize(ySize), total_shapes(xSize * ySize)
    {
        this->m_vertices.setPrimitiveType(sf::Triangles);
        this->m_vertices.resize(xSize * ySize * this->vertexNumber);
    }
    sf::VertexArray m_vertices;
    void create_hexagon(sf::VertexArray &buffer_array, double xCenter, double yCenter, const int buffer_offset)
    {
        buffer_array[buffer_offset].position = sf::Vector2f(xCenter - this->render_circumradius, yCenter);
        buffer_array[buffer_offset + 1].position = sf::Vector2f(xCenter + this->render_circumradius * deg_cos(240),
                                                                yCenter + this->render_circumradius * deg_sin(240));
        buffer_array[buffer_offset + 2].position = sf::Vector2f(xCenter + this->render_circumradius * deg_cos(300),
                                                                yCenter + this->render_circumradius * deg_sin(300));

        buffer_array[buffer_offset + 3].position = sf::Vector2f(xCenter - this->render_circumradius, yCenter);
        buffer_array[buffer_offset + 4].position = sf::Vector2f(xCenter + this->render_circumradius * deg_cos(300),
                                                                yCenter + this->render_circumradius * deg_sin(300));
        buffer_array[buffer_offset + 5].position = sf::Vector2f(xCenter + this->render_circumradius, yCenter);

        buffer_array[buffer_offset + 6] = sf::Vector2f(xCenter - this->render_circumradius, yCenter);
        buffer_array[buffer_offset + 7] = sf::Vector2f(xCenter + this->render_circumradius, yCenter);
        buffer_array[buffer_offset + 8] = sf::Vector2f(xCenter + this->render_circumradius * deg_cos(60),
                                                       yCenter + this->render_circumradius * deg_sin(60));

        buffer_array[buffer_offset + 9] = sf::Vector2f(xCenter - this->render_circumradius, yCenter);
        buffer_array[buffer_offset + 10] = sf::Vector2f(xCenter + this->render_circumradius * deg_cos(120),
                                                        yCenter + this->render_circumradius * deg_sin(120));
        buffer_array[buffer_offset + 11] = sf::Vector2f(xCenter + this->render_circumradius * deg_cos(60),
                                                        yCenter + this->render_circumradius * deg_sin(60));
    };

    void init()
    {
        for (int i{0}; i < 100; i += 1)
        {
            for (int j{0}; j < 100; j += 1)
            {
                create_hexagon(this->m_vertices, i * 1.5 * this->circumradius,
                               2 * j * this->inRadius - i * sqrt(3) / 2 * this->circumradius,
                               (i * ySize + j) * this->vertexNumber);
                const sf::Color vertexColor(255, 255, 255, 150);
                for (int vertexIndex{0}; vertexIndex < this->vertexNumber; vertexIndex++)
                {
                    this->m_vertices[(i * ySize + j) * this->vertexNumber + vertexIndex].color = vertexColor;
                }
            }
        }
        std::cout << "Finished" << std::endl;
    }

    void update(int xSite, int ySite, const RGBA color)
    {
        for (int quadIndex = 0; quadIndex < this->vertexNumber; ++quadIndex)
        {
            m_vertices[(xSite * ySize + ySite) * this->vertexNumber + quadIndex].color =
                sf::Color(color[0], color[1], color[2], 255);
        }
    }

  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = NULL;
        target.draw(m_vertices, states);
    }
};

#endif