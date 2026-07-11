#include "ui_manager.hpp"

namespace ui {
UIManager::UIManager(editor::EditorContext& context , Scene& scene)
    :mContext(context),
    mToolbar(mContext, scene) {

}

UIManager::~UIManager() {
}
void UIManager::draw() {
    mToolbar.draw();
}

} // namespace ui

