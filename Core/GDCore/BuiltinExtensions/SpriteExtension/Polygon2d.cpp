/*
 * GDevelop Core
 * Copyright 2008-2014 Florian Rival (Florian.Rival@gmail.com). All rights reserved.
 * This project is released under the GNU Lesser General Public License.
 */
#include "Polygon2d.h"
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>

void Polygon2d::Rotate(float angle)
{
    float t,
          cosa = cos(-angle),
          sina = sin(-angle); //We want a clockwise rotation

    for (unsigned int i = 0;i<vertices.size();++i)
    {
        t = vertices[i].x;
        vertices[i].x = t*cosa + vertices[i].y*sina;
        vertices[i].y = -t*sina + vertices[i].y*cosa;
    }
}

void Polygon2d::Move(float x, float y)
{
    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        vertices[i].x += x;
        vertices[i].y += y;
    }
    ComputeEdges();
}

void Polygon2d::ComputeEdges() const
{
    sf::Vector2f v1, v2;
    edges.clear();

    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        v1 = vertices[i];
        if ((i + 1) >= vertices.size()) v2 = vertices[0];
        else v2 = vertices[i + 1];

        edges.push_back(v2 - v1);
    }
}

bool Polygon2d::IsConvex() const
{
    ComputeEdges();
    if ( edges.size() < 3 ) return false;

    bool zProductIsPositive = (edges[0].x*edges[0+1].y - edges[0].y*edges[0+1].x) > 0;

    for (unsigned int i = 1;i<edges.size()-1;++i)
    {
        float zCrossProduct = edges[i].x*edges[i+1].y - edges[i].y*edges[i+1].x;
        if ( (zCrossProduct > 0) != zProductIsPositive ) return false;
    }

    float lastZCrossProduct = edges[edges.size()-1].x*edges[0].y - edges[edges.size()-1].y*edges[0].x;
    if ( (lastZCrossProduct > 0) != zProductIsPositive ) return false;

    return true;
}

sf::Vector2f Polygon2d::ComputeCenter() const
{
    sf::Vector2f center;

    for (unsigned int i = 0; i < vertices.size(); i++)
    {
        center.x += vertices[i].x;
        center.y += vertices[i].y;
    }
    center.x /= vertices.size();
    center.y /= vertices.size();

    return center;
}

Polygon2d Polygon2d::CreateRectangle(float width, float height)
{
    Polygon2d rect;
    rect.vertices.push_back(sf::Vector2f(-width/2.0f, -height/2.0f));
    rect.vertices.push_back(sf::Vector2f(+width/2.0f, -height/2.0f));
    rect.vertices.push_back(sf::Vector2f(+width/2.0f, +height/2.0f));
    rect.vertices.push_back(sf::Vector2f(-width/2.0f, +height/2.0f));

    return rect;
}

