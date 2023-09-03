#pragma once

#include "wx/wx.h"
#include <random>

class Main : public wxFrame
{
public:
    Main();
    ~Main();

private:
    void onButtonClicked(wxCommandEvent& evt);
    const int nFieldsWidth = 10;
    const int nFieldsHeight = 10;
    wxButton** buttons;

    int* nMine;
    bool isFirstClick = true;

    std::mt19937 rng;
};

