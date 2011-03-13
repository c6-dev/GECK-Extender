// UIComponents.cpp : main project file.

#include "TagBrowser.h"

using namespace UIComponents;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew TagBrowser());
	return 0;
}
