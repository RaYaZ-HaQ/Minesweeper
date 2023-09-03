#pragma once

#include <memory>

#include "wx/wx.h"
#include "Main.h"

class App : public wxApp
{
public:
    App();
    ~App();
    virtual bool OnInit();
private:
    Main* pMain;
};

