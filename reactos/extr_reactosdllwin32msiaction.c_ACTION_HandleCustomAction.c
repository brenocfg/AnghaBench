#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int INT ;

/* Variables and functions */
 scalar_t__ ACTION_CustomAction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int ACTION_ShowDialog (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_FUNCTION_NOT_CALLED ; 
 scalar_t__ ERROR_INSTALL_ALREADY_RUNNING ; 
 scalar_t__ ERROR_INSTALL_FAILURE ; 
 scalar_t__ ERROR_INSTALL_PACKAGE_REJECTED ; 
 scalar_t__ ERROR_INSTALL_SUSPEND ; 
 scalar_t__ ERROR_INSTALL_USEREXIT ; 
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ ERROR_INVALID_HANDLE_STATE ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int IDCANCEL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ needs_ui_sequence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ui_actioninfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ui_actionstart (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT ACTION_HandleCustomAction(MSIPACKAGE *package, LPCWSTR action, UINT script)
{
    UINT arc;
    INT uirc;

    uirc = ui_actionstart(package, action, NULL, NULL);
    if (uirc == IDCANCEL)
        return ERROR_INSTALL_USEREXIT;
    ui_actioninfo(package, action, TRUE, 0);
    arc = ACTION_CustomAction( package, action, script );
    uirc = !arc;

    if (arc == ERROR_FUNCTION_NOT_CALLED && needs_ui_sequence(package))
    {
        uirc = ACTION_ShowDialog(package, action);
        switch (uirc)
        {
        case -1:
            return ERROR_SUCCESS; /* stop immediately */
        case 0: arc = ERROR_FUNCTION_NOT_CALLED; break;
        case 1: arc = ERROR_SUCCESS; break;
        case 2: arc = ERROR_INSTALL_USEREXIT; break;
        case 3: arc = ERROR_INSTALL_FAILURE; break;
        case 4: arc = ERROR_INSTALL_SUSPEND; break;
        case 5: arc = ERROR_MORE_DATA; break;
        case 6: arc = ERROR_INVALID_HANDLE_STATE; break;
        case 7: arc = ERROR_INVALID_DATA; break;
        case 8: arc = ERROR_INSTALL_ALREADY_RUNNING; break;
        case 9: arc = ERROR_INSTALL_PACKAGE_REJECTED; break;
        default: arc = ERROR_FUNCTION_FAILED; break;
        }
    }

    ui_actioninfo(package, action, FALSE, uirc);

    return arc;
}