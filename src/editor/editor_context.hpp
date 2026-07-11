#pragma once

#include "tool.hpp"

namespace editor {

class EditorContext
{
private:
    Tool mTool = Tool::Select;
public:
    EditorContext(/* args */);
    ~EditorContext();

    Tool getTool() const;
    void setTool(Tool tool);

};



}

