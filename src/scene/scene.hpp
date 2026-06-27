#pragma once
#include <vector>
#include "object.hpp"

class Scene
{
private:
    std::vector<Object> mObjects;

public:
    Scene(/* args */);
    ~Scene();

    void addObject(const Object& obj);
    void update(float dt);
    void draw();
    const std::vector<Object>& getObjects() const;
};


