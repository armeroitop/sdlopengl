#include "editor_context.hpp"

namespace editor {

EditorContext::EditorContext(/* args */)
{
}

EditorContext::~EditorContext()
{
}

Tool EditorContext::getTool() const {
    return mTool;
}

void EditorContext::setTool(Tool tool) {
    mTool = tool;
}
    
} // namespace editor

