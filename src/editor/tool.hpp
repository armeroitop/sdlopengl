#pragma once

namespace editor {

enum class Tool {
    None,
    Select,
    Move,
    Rotate,
    Scale,
    Line,
    Extrude,
    Bevel,
    Knife
};

enum class TransformMode {
    Local,
    World
};
}