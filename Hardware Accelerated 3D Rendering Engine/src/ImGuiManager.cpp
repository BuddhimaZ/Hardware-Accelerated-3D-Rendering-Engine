#include "ImGuiManager.h"

size_t ImGuiManager::nRefCount = 0;

ImGuiManager::ImGuiManager()
{
	if (nRefCount++ == 0) {
		ImGui::CreateContext();
		IMGUI_CHECKVERSION();
	}
}

ImGuiManager::~ImGuiManager()
{
	if (--nRefCount == 0) {
		ImGui::DestroyContext();
	}
}
