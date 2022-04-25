#include "QuickOptions.h"

#include "GameModel.h"
#include "GameController.h"

#include "simulation/Simulation.h"

SandEffectOption::SandEffectOption(GameModel *m) : QuickOption("P", "Sand effect", m, Toggle)
{
}
bool SandEffectOption::GetToggle()
{
	return m->GetSimulation()->pretty_powder;
}
void SandEffectOption::perform()
{
	m->GetSimulation()->pretty_powder = !m->GetSimulation()->pretty_powder;
}

DrawGravOption::DrawGravOption(GameModel *m) : QuickOption("G", "Draw gravity field \bg(ctrl+g)", m, Toggle)
{
}
bool DrawGravOption::GetToggle()
{
	return m->GetGravityGrid();
}
void DrawGravOption::perform()
{
	m->ShowGravityGrid(!m->GetGravityGrid());
}

DecorationsOption::DecorationsOption(GameModel *m) : QuickOption("D", "Draw decorations \bg(ctrl+b)", m, Toggle)
{
}
bool DecorationsOption::GetToggle()
{
	return m->GetDecoration();
}
void DecorationsOption::perform()
{
	m->SetDecoration(!m->GetDecoration());
}

NGravityOption::NGravityOption(GameModel *m) : QuickOption("N", "Newtonian Gravity \bg(n)", m, Toggle)
{
}
bool NGravityOption::GetToggle()
{
	return m->GetNewtonianGravity();
}
void NGravityOption::perform()
{
	m->SetNewtonianGravity(!m->GetNewtonianGravity());
}

AHeatOption::AHeatOption(GameModel *m) : QuickOption("A", "Ambient heat \bg(u)", m, Toggle)
{
}
bool AHeatOption::GetToggle()
{
	return m->GetAHeatEnable();
}
void AHeatOption::perform()
{
	m->SetAHeatEnable(!m->GetAHeatEnable());
}

TimeDilationOption::TimeDilationOption(GameModel *m) : QuickOption("T", "Time Dilation \bg(t)", m, Toggle)
{
}
bool TimeDilationOption::GetToggle()
{
	return m->GetTimeDilation();
}
void TimeDilationOption::perform()
{
	m->SetTimeDilation(!m->GetTimeDilation());
}

CompressibleGasesOption::CompressibleGasesOption(GameModel *m) : QuickOption("O", "Compressible Gases \bg(o)", m, Toggle)
{
}
bool CompressibleGasesOption::GetToggle()
{
	return m->GetCompressibleGases();
}
void CompressibleGasesOption::perform()
{
	m->SetCompressibleGases(!m->GetCompressibleGases());
}

DrawQuantumFieldsOption::DrawQuantumFieldsOption(GameModel *m) : QuickOption("Q", "Draw Quantum Fields \bg(q)", m, Toggle)
{
}
bool DrawQuantumFieldsOption::GetToggle()
{
	return m->GetDrawQuantumFields();
}
void DrawQuantumFieldsOption::perform()
{
	m->SetDrawQuantumFields(!m->GetDrawQuantumFields());
}

ConsoleShowOption::ConsoleShowOption(GameModel *m, GameController *c_) : QuickOption("C", "Show Console \bg(~)", m, Toggle)
{
	c = c_;
}
bool ConsoleShowOption::GetToggle()
{
	return 0;
}
void ConsoleShowOption::perform()
{
	c->ShowConsole();
}
