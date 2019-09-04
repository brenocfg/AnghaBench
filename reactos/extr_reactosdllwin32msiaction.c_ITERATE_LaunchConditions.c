#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int ui_level; } ;
typedef  int /*<<< orphan*/  MSIRECORD ;
typedef  TYPE_1__ MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  TYPE_1__* LPVOID ;
typedef  int /*<<< orphan*/ * LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_INSTALL_FAILURE ; 
 scalar_t__ ERROR_SUCCESS ; 
 int INSTALLUILEVEL_MASK ; 
 int INSTALLUILEVEL_NONE ; 
 int /*<<< orphan*/  MB_OK ; 
 scalar_t__ MSICONDITION_FALSE ; 
 scalar_t__ MSI_EvaluateConditionW (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MSI_RecordGetString (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MessageBoxW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deformat_string (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static UINT ITERATE_LaunchConditions(MSIRECORD *row, LPVOID param)
{
    MSIPACKAGE* package = param;
    LPCWSTR cond = NULL; 
    LPCWSTR message = NULL;
    UINT r;

    static const WCHAR title[]=
        {'I','n','s','t','a','l','l',' ','F','a', 'i','l','e','d',0};

    cond = MSI_RecordGetString(row,1);

    r = MSI_EvaluateConditionW(package,cond);
    if (r == MSICONDITION_FALSE)
    {
        if ((package->ui_level & INSTALLUILEVEL_MASK) != INSTALLUILEVEL_NONE)
        {
            LPWSTR deformated;
            message = MSI_RecordGetString(row,2);
            deformat_string(package,message,&deformated);
            MessageBoxW(NULL,deformated,title,MB_OK);
            msi_free(deformated);
        }

        return ERROR_INSTALL_FAILURE;
    }

    return ERROR_SUCCESS;
}