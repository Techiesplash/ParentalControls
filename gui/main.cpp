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
 * @brief Saves the contents of a wxListBox to a file
 *
 * @param file The file to save to
 * @param listBox The list box to save
 */
void SaveListBoxToFile(string file, wxListBox *listBox)
{
    static char *line;
    static size_t len;
    static ssize_t read;
    remove(file.c_str());
    FILE *fp = fopen(file.c_str(), "w");
    if (fp != NULL)
    {

        for (int i = 0; i < listBox->GetCount(); i++)
        {
            fputs(listBox->GetString(i).mb_str(), fp);
        }

        fclose(fp);

        return;
    }

    puts("Failed to open file for wxListBox saving!");
}


/**
 * @brief Check if a string is composed solely of whitespace
 *
 * @param s String to check
 * @return true The string is empty
 * @return false The string is not empty
 */
bool isStrEmpty(const char *s)
{
    while (*s != '\0')
    {
        if (!isspace((unsigned char)*s))
            return false;
        s++;
    }
    return true;
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
        if (!isStrEmpty(this->m_textinput->GetValue().mb_str()))
        {
            bool exists = false;
            for (int i = 0; i < this->m_listBox4->GetCount(); i++)
            {
                if (this->m_textinput->GetValue() == this->m_listBox4->GetString(i))
                {
                    exists = true;
                }
            }
            if (!exists)
            {
                this->m_listBox4->Append(this->m_textinput->GetValue());
                SaveListBoxToFile("/pc.list", this->m_listBox4);
            }
        }
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
            SaveListBoxToFile("pc.list", this->m_listBox4);
        }
    }
    void m_syncOnButtonClick(wxCommandEvent &event)
    {
        FILE *fp = fopen("/refresh.msg", "w");
        if (fp != NULL)
        {
            fclose(fp);
        }
    }
    void m_activateOnButtonClick(wxCommandEvent &event)
    {

        Activate();
    }
    void m_deactivateOnButtonClick(wxCommandEvent &event)
    {
        Deactivate();
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
            remove(s"/access.test");

            frame = new Main(NULL);
            frame->Init();

            frame->Show(true);
            LoadListboxFromFile("/pc.list", frame->GetKillList());
        }
        return true;
    }
};

wxIMPLEMENT_APP(ParentalApp);
