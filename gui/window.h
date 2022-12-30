#pragma once

#include "noname.h"
#include "interface.h"

/**
 * @brief Child class for Root permissions warning
 *
 */
class Rootwarn : public noroot
{
    using noroot::noroot;
    void m_okOnButtonClick(wxCommandEvent &event)
    {
        this->Close();
        exit(1);
    }
};