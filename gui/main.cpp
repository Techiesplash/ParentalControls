#include "noname.h"
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#define FILES_PATH "/"
#include <string>
#include "window.h"
#include "../reusable/reusable.h"

using namespace std;

/**
 * @brief Loads the contents of a file into a wxListBox
 *
 * @param file The file to load
 * @param listBox The wxListBox to load into
 */
void LoadListboxFromFile(string file, wxListBox *listBox)
{
    static char *line;
    static size_t len;
    static ssize_t read;
    listBox->Clear();
    FILE *fp = fopen(file.c_str(), "r");
    if (fp != NULL)
    {

        while ((read = getline(&line, &len, fp)) != -1)
        {
            if (std::string(line).find_first_not_of(' ') != std::string::npos)
            {
                listBox->Append(wxString(line));
            }
        }

        fclose(fp);

        return;
    }

    puts("Failed to open file for wxListBox loading!");
}

/**
 * @brief Main window child class
 *
 */
class Main : public MainWindow
{
    using MainWindow::MainWindow;

public:
    void m_addOnButtonClick(wxCommandEvent &event)
    {
        AddWindow *a = new AddWindow(NULL);

        a->Show(true);
    }
    void m_removeOnButtonClick(wxCommandEvent &event)
    {

        int res = wxNOT_FOUND;

        for (int i = 0; i < this->m_listBox4->GetCount(); i++)
        {
            if (this->m_listBox4->IsSelected(i))
            {
                res = i;
            }
        }

        if (res != wxNOT_FOUND)
        {
            this->m_listBox4->Delete(res);
            SaveListBoxToFile("/pc.list", this->m_listBox4);
            RefreshKillList();
        }

    }

    void UpdateButtonStates()
    {
        int status = GetDaemonStatus();
        if (status == DaemonStatus::OFF || status == DaemonStatus::ERROR)
        {
            this->m_deactivate->Enable(false);
            this->m_activate->Enable(true);
        }
        else
        {
            this->m_deactivate->Enable(true);
            this->m_activate->Enable(false);
        }
    }

    void m_activateOnButtonClick(wxCommandEvent &event)
    {
        Activate();
        UpdateButtonStates();
    }
    void m_deactivateOnButtonClick(wxCommandEvent &event)
    {
        Deactivate();
        UpdateButtonStates();
    }
    void m_toggleStartupOnButtonClick(wxCommandEvent &event)
    {
        FILE *fp = fopen("/pc.startdisabled", "r");
        if (fp)
        {
            // Enable at startup
            fclose(fp);
            remove("/pc.startdisabled");
            this->m_toggleStartup->SetLabel(wxT("Auto-Disable"));
        }
        else
        {
            // Disable at startup
            fp = fopen("/pc.startdisabled", "w");
            fclose(fp);
            this->m_toggleStartup->SetLabel(wxT("Auto-Enable"));
        }
    }

    void OnClose()
    {
        mainWindowPtr = nullptr;
        exit(0);
    }

    void Init()
    {
        FILE *fp = fopen("/pc.startdisabled", "r");
        if (fp)
        {
            fclose(fp);
            this->m_toggleStartup->SetLabel(wxT("Auto-Enable"));
        }
        else
        {
            this->m_toggleStartup->SetLabel(wxT("Auto-Disable"));
        }
        UpdateButtonStates();
        mainWindowPtr = this;
    }

    wxListBox *GetKillList()
    {
        return this->m_listBox4;
    }
};

Main *frame;

/**
 * @brief Main application.
 *
 */
class ParentalApp : public wxApp
{
public:
    bool OnInit() override
    {

        // Run an access test to make sure we can access the files
        FILE *test = fopen("/access.test", "w");
        if (test == NULL)
        {
            Rootwarn *warn = new Rootwarn(NULL);

            warn->Show(true);
        }
        else
        {
            // Clean up from the access test
            fclose(test);
            remove("/access.test");

            frame = new Main(NULL);
            frame->Init();

            frame->Show(true);
            LoadListboxFromFile("/pc.list", frame->GetKillList());
        }

        return true;
    }
};

wxIMPLEMENT_APP(ParentalApp);
