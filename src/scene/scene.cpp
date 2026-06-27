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
