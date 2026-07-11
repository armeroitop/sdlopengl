#pragma once 

#include "ui/toolbar.hpp"

namespace ui
{
class UIManager
{
private:
    Toolbar mToolbar;
public:
    UIManager(/* args */);
    ~UIManager();
    void draw();
};
} // namespace ui




