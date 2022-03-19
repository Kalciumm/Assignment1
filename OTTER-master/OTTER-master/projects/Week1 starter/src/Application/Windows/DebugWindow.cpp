#include "DebugWindow.h"
#include "Application/Application.h"
#include "Application/ApplicationLayer.h"
#include "Application/Layers/RenderLayer.h"

DebugWindow::DebugWindow() :
	IEditorWindow()
{
	Name = "Debug";
	SplitDirection = ImGuiDir_::ImGuiDir_None;
	SplitDepth = 0.5f;
	Requirements = EditorWindowRequirements::Menubar;
}

DebugWindow::~DebugWindow() = default;

void DebugWindow::RenderMenuBar() 
{
	Application& app = Application::Get();
	RenderLayer::Sptr renderLayer = app.GetLayer<RenderLayer>();

	BulletDebugMode physicsDrawMode = app.CurrentScene()->GetPhysicsDebugDrawMode();
	if (BulletDebugDraw::DrawModeGui("Physics Debug Mode:", physicsDrawMode)) {
		app.CurrentScene()->SetPhysicsDebugDrawMode(physicsDrawMode);
	}

	ImGui::Separator();

	RenderFlags flags = renderLayer->GetRenderFlags();
	
	bool changed = false;
	bool temp = *(flags & RenderFlags::EnableColorCorrection);
	bool temp2 = *(flags & RenderFlags::EnableColorCorrectionWarm);
	bool temp3 = *(flags & RenderFlags::EnableColorCorrectionFunky);
	if (ImGui::Checkbox("Enable Color Correction Cool", &temp)) {
		changed = true;
		flags = (flags & ~*RenderFlags::EnableColorCorrection) | (temp ? RenderFlags::EnableColorCorrection : RenderFlags::None);
	}
	if (ImGui::Checkbox("Enable Color Correction Warm", &temp2)) {
		changed = true;
		flags = (flags & ~*RenderFlags::EnableColorCorrectionWarm) | (temp2 ? RenderFlags::EnableColorCorrectionWarm : RenderFlags::None);
	}
	if (ImGui::Checkbox("Enable Color Correction Funky", &temp3)) {
		changed = true;
		flags = (flags & ~*RenderFlags::EnableColorCorrectionFunky) | (temp3 ? RenderFlags::EnableColorCorrectionFunky : RenderFlags::None);
	}
	

	if (changed) {
		renderLayer->SetRenderFlags(flags);
	}
}
