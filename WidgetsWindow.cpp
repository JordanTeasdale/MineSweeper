#include "WidgetsWindow.h"

wxBEGIN_EVENT_TABLE(WidgetsWindow, wxFrame)
wxEND_EVENT_TABLE()

WidgetsWindow::WidgetsWindow() : wxFrame(nullptr, wxID_ANY, "Widgets!", wxPoint(30,30), wxSize(800,800)) {
	cell = new wxButton* [FieldWidth * FieldHeight];
	wxGridSizer* grid = new wxGridSizer(FieldWidth, FieldHeight, 0, 0);

	Field = new int[FieldWidth * FieldHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < FieldWidth; ++x) {
		for (int y = 0; y < FieldHeight; ++y) {
			cell[y * FieldWidth + x] = new wxButton(this, 10000 + (y * FieldWidth + x));
			cell[y * FieldWidth + x]->SetFont(font);
			grid->Add(cell[y * FieldWidth + x], 1, wxEXPAND | wxALL);

			cell[y * FieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &WidgetsWindow::OnButtonClicked, this);
			Field[y * FieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

void WidgetsWindow::OnButtonClicked(wxCommandEvent& evt) {
	// Get coordinate of button in field array
	int x = (evt.GetId() - 10000) % FieldWidth;
	int y = (evt.GetId() - 10000) / FieldWidth;

	if (FirstClick) {
		int mines = 30;

		while (mines) {
			int rx = rand() % FieldWidth;
			int ry = rand() % FieldHeight;

			if (Field[ry * FieldWidth + rx] == 0 && rx != x && ry != y) {
				Field[ry * FieldWidth + rx] = -1;
				--mines;
			}
		}
		FirstClick = false;
	}

	// Disable Button, preventing it being pressed again
	cell[y * FieldWidth + x]->Enable(false);

	if (Field[y * FieldWidth + x] == -1) {
		wxMessageBox("BOOOOOOOOOOOM!!! - Game Over :(");

		// Reset game
		FirstClick = true;
		for (int x = 0; x < FieldWidth; ++x) {
			for (int y = 0; y < FieldHeight; ++y) {
				Field[y * FieldWidth + x] = 0;
				cell[y * FieldWidth + x]->SetLabel("");
				cell[y * FieldWidth + x]->Enable(true);

			}
		}
	}
	else {
		// Count neighboring mines
		int mineCount = 0;
		for (int i = -1; i < 2; ++i) {
			for (int j = -1; j < 2; ++j) {
				if (x + 1 >= 0 && x + i < FieldWidth && y + j >= 0 && y + j < FieldHeight) {
					if (Field[(y + j) * FieldWidth + (x + i)] == -1)
						++mineCount;
				}
			}
			
			// Update buttons label to show mine cout if > 0
			if (mineCount > 0) 
				cell[y * FieldWidth + x]->SetLabel(std::to_string(mineCount));
			
		}
	}

	evt.Skip();
}