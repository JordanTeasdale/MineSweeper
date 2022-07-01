#pragma once
#include "wx/wx.h"

class WidgetsWindow : public wxFrame
{
private:
	int FieldWidth = 10;
	int FieldHeight = 10;
	wxButton** cell;
	int* Field = nullptr;
	bool FirstClick = true;

public:
	WidgetsWindow();

	void OnButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

