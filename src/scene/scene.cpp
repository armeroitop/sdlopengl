#include "scene.hpp"

Scene::Scene(/* args */) {
}

Scene::~Scene() {
}

void Scene::addObject(const Object& obj) {
    mObjects.emplace_back(obj);
}

void Scene::update(float dt) {
    for (auto& obj : mObjects) {
        obj.update(dt);
    }
}

void Scene::draw() {
    for (auto& obj : mObjects) {
        obj.draw();
    }
}

const std::vector<Object>& Scene::getObjects() const {
    return mObjects;
}

Object& Scene::createCubeMesh(const Transform& transform) {

    std::string name = "cube_" + std::to_string(mNextId);

    mObjects.emplace_back(
        mNextId++,
        name,
        app::geometry::MeshFactory::createCubeMesh(),
        transform
    );

    return mObjects.back();
}

const Object* Scene::findObject(uint32_t id) const {
    
    for (const auto& object : mObjects) {
        if (object.getId() == id) {
            return &object;
        }
    }

    return nullptr;
}

Object* Scene::findObject(uint32_t id) {

    for (auto& object : mObjects) {
        if (object.getId() == id) {
            return &object;
        }
    }

    return nullptr;
}
