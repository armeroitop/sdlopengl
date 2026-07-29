#include "dock_layout.hpp"
#include <imgui.h>
#include <imgui_internal.h>


namespace ui {
DockLayout::DockLayout() {
}

DockLayout::~DockLayout() {
}

void DockLayout::begin() {
    beginDockSpace();

    if (!mInitialized) {
        // Esperamos un frame para que las ventanas existan.
        static bool firstFrame = true;

        if (firstFrame) {
            firstFrame = false;
        } else {
            buildDefaultLayout();
            mInitialized = true;
        }
    }
}

void DockLayout::beginDockSpace() {

    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoDocking
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoBackground;

    //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // importante

    ImGui::Begin("MainDockSpace", nullptr, windowFlags);

    mDockspaceID = ImGui::GetID("MainDockSpace");

    ImGui::DockSpace(
        mDockspaceID,
        ImVec2(0.0f, 0.0f),
        ImGuiDockNodeFlags_PassthruCentralNode
    );
}

void DockLayout::buildDefaultLayout() {
    //ImGuiID dockspaceID = ImGui::GetID("MainDockSpace");

     ImGui::DockBuilderRemoveNode(mDockspaceID);
     ImGui::DockBuilderAddNode(
         mDockspaceID,
         ImGuiDockNodeFlags_DockSpace
     );
    printf("dockspace = %08X\n", mDockspaceID);
    // Imgui debe conocer el tamaño de la ventana
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::DockBuilderSetNodeSize(
        mDockspaceID,
        viewport->WorkSize
    );

    // Dividimos una fila arriba
    ImGuiID toolbarDock;
    ImGuiID restanteAbajoDock;

    ImGui::DockBuilderSplitNode(
        mDockspaceID,
        ImGuiDir_Up,
        0.06f,   // ~36 px en una ventana de 600 px
        &toolbarDock,
        &restanteAbajoDock
    );

    // Dividimos una columna a la izquierda
    ImGuiID leftDock;
    ImGuiID centerDock;

    ImGui::DockBuilderSplitNode(
        restanteAbajoDock,
        ImGuiDir_Left,
        0.20f,
        &leftDock,
        &centerDock
    );
    printf("left   = %08X\n", leftDock);
    printf("center = %08X\n", centerDock);

    // Dividimos el centro con una columna a la derecha
    ImGuiID rightDock;
    ImGuiID viewportDock;

    ImGui::DockBuilderSplitNode(
        centerDock,
        ImGuiDir_Right,
        0.25f,
        &rightDock,
        &viewportDock
    );
    printf("right  = %08X\n", rightDock);

    // Asociar ventanas a los nodos
    ImGui::DockBuilderDockWindow("Toolbar", toolbarDock);
    ImGui::DockBuilderDockWindow("Hierarchy", leftDock);
    ImGui::DockBuilderDockWindow("Inspector", rightDock);

    // Aunque todavía no exista, la reservamos
    ImGui::DockBuilderDockWindow("Viewport", viewportDock);

    // Aplicar el layout
    ImGui::DockBuilderFinish(mDockspaceID);
}

void DockLayout::end() {
    ImGui::End();
}



} // namespace ui

