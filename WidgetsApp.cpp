#include "WidgetsApp.h"

wxIMPLEMENT_APP(WidgetsApp);

bool WidgetsApp::OnInit() {
	window = new WidgetsWindow();
	window->Show();
	return true;
}