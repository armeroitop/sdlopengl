#include "editor_context.hpp"

namespace editor {

EditorContext::EditorContext(/* args */) {
}

EditorContext::~EditorContext() {
}

Tool EditorContext::getTool() const {
    return mTool;
}

void EditorContext::setTool(Tool tool) {
    mTool = tool;
}

TransformMode EditorContext::getTransformMode() const {
    return mTransformode;
}

void EditorContext::setTransformMode(TransformMode mode) {
    mTransformode = mode;
}

void EditorContext::setSelectedObjectId(uint32_t id) {
    mSelectedObjectId = id;
}

uint32_t EditorContext::getSelectedObjectId() const {
    return mSelectedObjectId;
}

bool EditorContext::hasSelection() const {
    return (mSelectedObjectId != mNoObjectIdSelected) ? true : false;
}

void EditorContext::clearSelection() {
    mSelectedObjectId = mNoObjectIdSelected;
}

} // namespace editor

