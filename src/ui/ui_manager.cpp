#include "ui_manager.hpp"

#include <imgui.h>
#include <imgui_internal.h>

#ifndef IMGUI_HAS_DOCK
#error IMGUI_HAS_DOCK NO ESTA DEFINIDO
#endif

namespace ui {
UIManager::UIManager(editor::EditorContext& context, Scene& scene, Camera& camera)
    :mContext(context),
    mScene(scene),
    mDockLayout(),
    mToolbar(mContext, scene),
    mHierarchy(mContext, scene),
    mInspector(mContext, scene),
    mViewport (mContext, scene, camera) {

}

UIManager::~UIManager() {
}

void UIManager::draw() {

    //mDockLayout.begin();

    mToolbar.draw();
    mHierarchy.draw();
    mInspector.draw();
    //mViewport.draw();

    mDockLayout.end();
}

void UIManager::begin() {

    mDockLayout.begin();
    mViewport.begin();
}

void UIManager::end() {
    mToolbar.draw();
    mHierarchy.draw();

    mViewport.end();

    mInspector.draw();

    mDockLayout.end();
}

void UIManager::beginViewportRender() {
    mViewport.beginRender();
}

void UIManager::endViewportRender() {
    mViewport.endRender();
}

void UIManager::update(const input::Input& input) {
    mViewport.update(input);
}

Viewport& UIManager::getViewport() {
    return mViewport;
}

const Viewport& UIManager::getViewport() const {
    return mViewport;
}

} // namespace ui

