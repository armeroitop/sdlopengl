#include "ui_manager.hpp"

#include <imgui.h>
#include <imgui_internal.h>

#ifndef IMGUI_HAS_DOCK
#error IMGUI_HAS_DOCK NO ESTA DEFINIDO
#endif

namespace ui {
UIManager::UIManager(editor::EditorContext& context, Scene& scene)
    :mContext(context),
    mScene(scene),
    mDockLayout(),
    mToolbar(mContext, scene),
    mHierarchy(mContext, scene),
    mInspector(mContext, scene),
    mViewport (mContext, scene) {

}

UIManager::~UIManager() {
}

void UIManager::draw() {

    mDockLayout.begin();

    mToolbar.draw();
    mHierarchy.draw();
    mInspector.draw();
    mViewport.draw();

    mDockLayout.end();
}

} // namespace ui

