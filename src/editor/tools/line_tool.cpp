#include "line_tool.hpp"

#include <iostream>

namespace editor::tools {
/* void LineTool::update(const input::Input& input, const ui::Viewport& viewport) {

    if (mState == LineToolState::WaitingForPointB) {

        // Obtener punto 3D bajo el cursor que intersecte el plano y=0

        //mCurrentPoint = ...;
    }
} */

glm::vec3 LineTool::getCurrentPoint() const {
    return mCurrentPoint;
}

void LineTool::onMouseDown(const glm::vec3& worldpoint) {

    if (mState == LineToolState::WaitingForPointA) {

        mPointA = worldpoint;
        mCurrentPoint = worldpoint;

        mState = LineToolState::WaitingForPointB;
        //std::cout << "mState change for WaitingForPointB" << std::endl;

        //mCurrentPoint = ...;
    } else if (mState == LineToolState::WaitingForPointB) {

        mState = LineToolState::WaitingForPointA;
        //std::cout << "mState  change for WaitingForPointA" << std::endl;

    }
}

void LineTool::cancel() {
    mState = LineToolState::WaitingForPointA;
}

bool LineTool::isInProgress() const {
    return mState == LineToolState::WaitingForPointB;
}


LineToolState LineTool::getState() const {
    return mState;
}

glm::vec3 LineTool::getPointA() const {
    return mPointA;
}

void LineTool::update(const glm::vec3& worldPoint) {

    if (mState != LineToolState::WaitingForPointB) {
        return;
    }

    mCurrentPoint = worldPoint;
}

LineTool::LineTool() {
}

LineTool::~LineTool() {
}

} // namespace editor::tools
