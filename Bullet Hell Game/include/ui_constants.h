#pragma once
#ifndef __UI_CONSTANTS_H__
#define __UI_CONSTANTS_H__

#include <imgui.h>
#include <rlImGui.h>


constexpr float FONT_SIZE_SM = 64.0f;
constexpr float FONT_SIZE_LG = 72.0f;

constexpr float GUI_WINDOW_ALPHA = 0.0f;

constexpr ImVec4 GUI_TEXT_COL = ImVec4(0.95f, 0.95f, 0.95f, 1);
constexpr ImVec4 GUI_TEXT_BG_COL = ImVec4(0.1f, 0.1f, 0.1f, 1);
constexpr float GUI_TEXT_CENTER_Y = 4.0f;

// Turn off the slider control by hiding it
constexpr ImU32 GUI_GRAB_DEFAULT = IM_COL32(255, 255, 255, 0);

constexpr ImU32 GUI_GAUGE_BG = IM_COL32(62, 40, 25, 255);
constexpr ImU32 GUI_INNER_GAUGE_FINE = IM_COL32(70, 139, 45, 255);
constexpr ImU32 GUI_INNER_GAUGE_WARN = IM_COL32(195, 155, 74, 255);
constexpr ImU32 GUI_INNER_GAUGE_HOT = IM_COL32(172, 61, 34, 255);

constexpr float GUI_PADDING = 20.0f;
constexpr float GUI_INNER_PADDING = 5.0f;
constexpr float GUI_GAUGE_HEIGHT = 20.0f;
constexpr float GUI_INNER_GAUGE_HEIGHT = GUI_GAUGE_HEIGHT - GUI_INNER_PADDING;
constexpr float GUI_INNER_GAUGE_DEFAULT_WIDTH = 10.0f;

constexpr float GUI_ROUNDING = 8.0f;

namespace bts
{
    namespace ui
    {

        void PrintImGuiText(ImGuiIO& io, const ImVec2& pos, const ImVec4& col, const char* fmt, ...) {
            va_list args;
            va_start(args, fmt);
            ImGui::PushFont(io.Fonts->Fonts[1]);
            ImGui::SetCursorPos(pos);
            ImGui::TextColoredV(GUI_TEXT_BG_COL, fmt, args);
            ImGui::PopFont();

            ImGui::PushFont(io.Fonts->Fonts[2]);
            ImVec2 center_pos = pos;
            center_pos.y += GUI_TEXT_CENTER_Y;
            ImGui::SetCursorPos(center_pos);
            ImGui::TextColoredV(col, fmt, args);
            ImGui::PopFont();
            va_end(args);
        }


        void DisplayGauge(Vector2 gauge_data)
        {
            static float slider_value = 0.0f;
            slider_value = gauge_data.x;

            // Gauge Container Color
            ImGui::PushStyleColor(ImGuiCol_FrameBg, GUI_GAUGE_BG);
            // Makes Slider Control Invisible because we make out custom one later
            ImGui::PushStyleColor(ImGuiCol_SliderGrab, GUI_GRAB_DEFAULT);

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, GUI_GAUGE_HEIGHT));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, GUI_ROUNDING);
            ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, GUI_ROUNDING);

            ImGui::BeginDisabled();

            // Gauge Container, Keeps it level with Score y position
            ImGui::SetCursorPos({ GUI_PADDING, ImGui::GetItemRectMin().y });
            ImGui::SliderFloat("##hidden", &slider_value, 0, gauge_data.y, "", ImGuiSliderFlags_NoInput);

            float gauge_ratio = (slider_value / gauge_data.y);

            ImU32 inner_color = GUI_INNER_GAUGE_FINE;
            if (gauge_ratio > 0.75f) {
                inner_color = GUI_INNER_GAUGE_HOT;
            }
            else if (gauge_ratio > 0.5f) {
                inner_color = GUI_INNER_GAUGE_WARN;
            }

            ImGui::PushStyleColor(ImGuiCol_FrameBg, inner_color);

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, GUI_INNER_GAUGE_HEIGHT));

            // Caculates where the slider control should be, to make it the width of the inner gauge
            float inner_gauge_width = (ImGui::GetItemRectSize().x - GUI_INNER_PADDING - GUI_INNER_PADDING);
            float grab_width = (gauge_ratio < 0.05f) ? GUI_INNER_GAUGE_DEFAULT_WIDTH : gauge_ratio * inner_gauge_width;

            ImGui::SetCursorPos({ GUI_PADDING + GUI_INNER_PADDING , ImGui::GetItemRectMin().y + GUI_INNER_PADDING });
            ImGui::SetNextItemWidth(grab_width);
            ImGui::SliderFloat("##hiddenslider", &slider_value, 0, gauge_data.y, "", ImGuiSliderFlags_NoInput);

            ImGui::PopStyleVar();
            ImGui::PopStyleColor();

            ImGui::EndDisabled();

            ImGui::PopStyleVar(3);
            ImGui::PopStyleColor(2);
        }

    }
}


#endif // !__UI_CONSTANTS_H__
