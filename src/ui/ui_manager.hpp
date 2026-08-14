#pragma once 

#include "ui/toolbar.hpp"
#include "ui/hierarchy.hpp"
#include "ui/inspector.hpp"
#include "ui/viewport.hpp"
#include "ui/dock_layout.hpp"

namespace ui {
class UIManager {

private:
    editor::EditorContext& mContext;
    Scene& mScene;

    DockLayout mDockLayout;
    Toolbar mToolbar;
    Hierarchy mHierarchy;
    Inspector mInspector;
    Viewport mViewport;

public:
    UIManager(editor::EditorContext& context, Scene& scene, Camera& camera);
    ~UIManager();
    void draw();
    void begin();
    void end();

    void beginViewportRender();
    void endViewportRender();

    void update(const input::Input& input);

    Viewport& getViewport();
    const Viewport& getViewport() const;

};
} // namespace ui




