#include "ui_manager.hpp"

#include <imgui.h>

namespace ui {
UIManager::UIManager(editor::EditorContext& context, Scene& scene)
    :mContext(context),
    mToolbar(mContext, scene),
    mHierarchy(mContext, scene),
    mScene(scene) {

}

UIManager::~UIManager() {
}

void UIManager::draw() {
    mToolbar.draw();
    mHierarchy.draw();
}

} // namespace ui

