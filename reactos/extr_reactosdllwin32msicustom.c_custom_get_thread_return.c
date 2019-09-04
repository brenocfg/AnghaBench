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
typedef  int UINT ;
typedef  int /*<<< orphan*/  MSIPACKAGE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_ForceReboot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  ERROR_FUNCTION_NOT_CALLED 133 
#define  ERROR_INSTALL_FAILURE 132 
#define  ERROR_INSTALL_SUSPEND 131 
#define  ERROR_INSTALL_USEREXIT 130 
#define  ERROR_NO_MORE_ITEMS 129 
#define  ERROR_SUCCESS 128 
 int /*<<< orphan*/  GetExitCodeThread (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static UINT custom_get_thread_return( MSIPACKAGE *package, HANDLE thread )
{
    DWORD rc = 0;

    GetExitCodeThread( thread, &rc );

    switch (rc)
    {
    case ERROR_FUNCTION_NOT_CALLED:
    case ERROR_SUCCESS:
    case ERROR_INSTALL_USEREXIT:
    case ERROR_INSTALL_FAILURE:
        return rc;
    case ERROR_NO_MORE_ITEMS:
        return ERROR_SUCCESS;
    case ERROR_INSTALL_SUSPEND:
        ACTION_ForceReboot( package );
        return ERROR_SUCCESS;
    default:
        ERR("Invalid Return Code %d\n",rc);
        return ERROR_INSTALL_FAILURE;
    }
}