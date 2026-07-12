#pragma once
#include <vector>
#include "object.hpp"
#include "geometry/mesh_factory.hpp"

class Scene
{
private:
    std::vector<Object> mObjects;
    uint32_t mNextId = 1;

public:
    Scene(/* args */);
    ~Scene();

    void addObject(const Object& obj);
    void update(float dt);
    void draw();
    const std::vector<Object>& getObjects() const;

    Object& createCubeMesh(const Transform& transform);
};


