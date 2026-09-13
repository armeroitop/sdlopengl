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

Object& Scene::createLine(const glm::vec3& pointA, const glm::vec3& pointB) {
    std::string name = "line_" + std::to_string(mNextId);

    Transform transform;
    transform.position = pointA;

    mObjects.emplace_back(
        mNextId++,
        name,
        app::geometry::MeshFactory::createLine(glm::vec3{ 0 }, pointB - pointA),
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
