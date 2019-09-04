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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  GetExitCodeProcess (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 

__attribute__((used)) static UINT custom_get_process_return( HANDLE process )
{
    DWORD rc = 0;

    GetExitCodeProcess( process, &rc );
    TRACE("exit code is %u\n", rc);
    if (rc != 0)
        return ERROR_FUNCTION_FAILED;
    return ERROR_SUCCESS;
}