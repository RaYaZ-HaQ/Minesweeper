#include "App.h"

wxIMPLEMENT_APP(App);

App::App()
{
}

App::~App()
{
}

bool App::OnInit()
{
    pMain = new Main();
    pMain->Show();
    return true;
}
