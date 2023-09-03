#include "Main.h"

constexpr int BASE_ID = 10000;

Main::Main() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(30, 30), wxSize(800, 600)), rng(std::random_device()())
{
    buttons = new wxButton * [nFieldsWidth * nFieldsHeight];
    nMine = new int[nFieldsWidth * nFieldsHeight];
    wxGridSizer* grid = new wxGridSizer(nFieldsHeight);

    wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    for (size_t i = 0; i < nFieldsHeight; i++)
    {
        for (size_t j = 0; j < nFieldsWidth; j++)
        {
            buttons[i * nFieldsHeight + j] = new wxButton(this, BASE_ID + i * nFieldsHeight + j);
            grid->Add(buttons[i * nFieldsHeight + j], 1, wxEXPAND | wxALL);
            buttons[i * nFieldsHeight + j]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Main::onButtonClicked, this);
            buttons[i * nFieldsHeight + j]->SetFont(font);
            nMine[i * nFieldsHeight + j] = 0;
        }
    }

    this->SetSizer(grid);
    grid->Layout();
}

Main::~Main()
{
    delete[] buttons;
    delete[] nMine;
}

void Main::onButtonClicked(wxCommandEvent& evt)
{
    int y = (evt.GetId() - BASE_ID) / nFieldsHeight;
    int x = (evt.GetId() - BASE_ID) % nFieldsWidth;

    if (isFirstClick)
    {
        // Init Mines
        int mineCount = 30;
        std::uniform_int_distribution<int> xDist(0, nFieldsWidth - 1);
        std::uniform_int_distribution<int> yDist(0, nFieldsHeight - 1);
        
        while (mineCount)
        {
            int rx = xDist(rng);
            int ry = yDist(rng);

            if (nMine[ry * nFieldsHeight + rx] != -1 && rx != x && ry != y)
            {
                nMine[ry * nFieldsHeight + rx] = -1;
                mineCount--;
            }
        }

        isFirstClick = false;
    }

    if (nMine[y * nFieldsHeight + x] == -1)
    {
        wxMessageBox("BOOM! Game Over", "You've hit a mine!");

        // Reset
        for (size_t i = 0; i < nFieldsHeight; i++)
        {
            for (size_t j = 0; j < nFieldsWidth; j++)
            {
                buttons[i * nFieldsHeight + j]->SetLabel("");
                buttons[i * nFieldsHeight + j]->Enable(true);
                nMine[i * nFieldsHeight + j] = 0;
            }
        }
        isFirstClick = true;
    }
    else
    {
        int detectedMines = 0;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if ((x + j) > 0 && (x + j) < nFieldsWidth && (y + i) > 0 && (y + i) < nFieldsHeight)
                {
                    if (nMine[(y + i) * nFieldsHeight + (x + j)] == -1)
                    {
                        detectedMines++;
                    }
                }
            }
        }
        buttons[y * nFieldsHeight + x]->SetLabel(detectedMines > 0 ? std::to_string(detectedMines) : "");
        buttons[y * nFieldsHeight + x]->Enable(false);
    }

    

    evt.Skip();
}
