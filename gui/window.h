#pragma once

#include "noname.h"
#include "../reusable/reusable.h"

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