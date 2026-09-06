#pragma once
#include <glm/glm.hpp>


#include "input/input.hpp"
//#include "ui/viewport.hpp"


namespace editor::tools {

enum class LineToolState {
    WaitingForPointA,
    WaitingForPointB
};

class LineTool {
private:
    /* data */
public:
    LineToolState mState = LineToolState::WaitingForPointA;
    glm::vec3 mPointA{ 0.0f };
    glm::vec3 mCurrentPoint{ 0.0f };


    //void update(const input::Input& input, const ui::Viewport& viewport);
    void onMouseDown(const glm::vec3& worldpoint);
    void cancel();
    bool isInProgress() const;
    bool hasPreview() const;

    LineToolState getState() const;
    void getPreviewStart();
    void getPreviewEnd();
    glm::vec3 getPointA() const;

    LineTool(/* args */);
    ~LineTool();
};



} // namespace tools;
