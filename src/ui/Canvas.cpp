#include "ui/Canvas.h"
#include <imgui.h>

void Canvas::addNode(const std::shared_ptr<Node> &node)
{
    nodes.push_back(node);
}

void Canvas::addConnection(const std::shared_ptr<Connection> &connection)
{
    connections.push_back(connection);
}

const std::vector<std::shared_ptr<Node>> &Canvas::getNodes() const
{
    return nodes;
}

const std::vector<std::shared_ptr<Connection>> &Canvas::getConnections() const
{
    return connections;
}

void Canvas::draw()
{
    // Canvas size
    ImVec2 canvasSize = ImGui::GetContentRegionAvail();
    ImVec2 canvasPos = ImGui::GetCursorScreenPos();

    // Background
    ImDrawList *drawList = ImGui::GetWindowDrawList();
    drawList->AddRectFilled(canvasPos,
                            ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y),
                            IM_COL32(40, 40, 40, 255));

    // Dummy node
    ImVec2 nodeTopLeft = ImVec2(canvasPos.x + demoNodePos.x, canvasPos.y + demoNodePos.y);
    ImVec2 nodeBottomRight = ImVec2(nodeTopLeft.x + demoNodeSize.x, nodeTopLeft.y + demoNodeSize.y);

    ImU32 nodeColor = demoNodeSelected ? IM_COL32(100, 180, 255, 255) : IM_COL32(70, 70, 70, 255);
    drawList->AddRectFilled(nodeTopLeft, nodeBottomRight, nodeColor, 8.0f);
    drawList->AddRect(nodeTopLeft, nodeBottomRight, IM_COL32(255, 255, 255, 40), 8.0f);

    // Node title
    drawList->AddText(ImVec2(nodeTopLeft.x + 10, nodeTopLeft.y + 10), IM_COL32_WHITE, "Image Input");

    // Mouse click = toggle selection
    ImVec2 mousePos = ImGui::GetIO().MousePos;
    if (ImGui::IsMouseClicked(0))
    {
        if (mousePos.x >= nodeTopLeft.x && mousePos.x <= nodeBottomRight.x &&
            mousePos.y >= nodeTopLeft.y && mousePos.y <= nodeBottomRight.y)
        {
            demoNodeSelected = !demoNodeSelected;
        }
        else
        {
            demoNodeSelected = false;
        }
    }

    // Drag node
    if (demoNodeSelected && ImGui::IsMouseDragging(0))
    {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        demoNodePos.x += delta.x;
        demoNodePos.y += delta.y;
    }
}