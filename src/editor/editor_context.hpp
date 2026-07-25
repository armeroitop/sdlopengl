#pragma once
#include <cstdint>
#include "tool.hpp"

namespace editor {

class EditorContext {
private:
    Tool mTool = Tool::Select;

    uint32_t mSelectedObjectId = mNoObjectIdSelected;
public:
    static constexpr uint32_t mNoObjectIdSelected = 0;

    EditorContext(/* args */);
    ~EditorContext();

    Tool getTool() const;
    void setTool(Tool tool);

    void setSelectedObjectId(uint32_t id);
    uint32_t getSelectedObjectId() const;

    bool hasSelection() const;
    void clearSelection();

};



}

