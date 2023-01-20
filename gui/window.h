#pragma once

#include "noname.h"
#include "../reusable/reusable.h"
#include <string>

using namespace std;
MainWindow *mainWindowPtr = nullptr;

/**
 * @brief Child class for Root permissions warning
 *
 */
class Rootwarn : public NoRootPopup
{
    using NoRootPopup::NoRootPopup;
    void m_okOnButtonClick(wxCommandEvent &event)
    {
        this->Close();
        exit(1);
    }
};

/**
 * @brief Saves the contents of a wxListBox to a file
 *
 * @param file The file to save to
 * @param listBox The list box to save
 */
static void SaveListBoxToFile(string file, wxListBox *listBox)
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

class AddWindow : public AddProgram
{

    
    using AddProgram::AddProgram;
    void m_addOnButtonClick(wxCommandEvent &event)
    {
        if (mainWindowPtr)
        {
            if (!isStrEmpty(this->inputprogram->GetValue().mb_str()))
            {
                bool exists = false;
                for (int i = 0; i < mainWindowPtr->m_listBox4->GetCount(); i++)
                {
                    if (this->inputprogram->GetValue() == mainWindowPtr->m_listBox4->GetString(i))
                    {
                        exists = true;
                    }
                }
                if (!exists)
                {
                    mainWindowPtr->m_listBox4->Append(this->inputprogram->GetValue());
                    SaveListBoxToFile("/pc.list", mainWindowPtr->m_listBox4);
                    RefreshKillList();
                }
            }
        }
    }
};