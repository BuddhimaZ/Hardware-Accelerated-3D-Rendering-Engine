#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

//Third party Includes
#include <imgui/imgui.h>

//Local Includes
#include "D3DIncludes.h"

//Standard Includes

class ImGuiManager {
public:
	ImGuiManager();
	~ImGuiManager();

private:
	static size_t nRefCount;
};


#endif // !IMGUIMANAGER_H
