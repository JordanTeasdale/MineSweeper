#pragma once
#include "wx/wx.h"
#include "WidgetsWindow.h"

class WidgetsApp : public wxApp
{
	WidgetsWindow* window = nullptr;

public:
	virtual bool OnInit();
};

