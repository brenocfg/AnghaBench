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
typedef  int /*<<< orphan*/ * HDC ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CreateDCW (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OsThunkDdCreateDirectDrawObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  show_status (int,char*) ; 
 int /*<<< orphan*/  testing_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  testing_noteq (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 

HANDLE
test_NtGdiDdCreateDirectDrawObject()
{
    HANDLE retValue=0;
    int fails=0;
    HDC hdc=CreateDCW(L"Display",NULL,NULL,NULL);

    if (hdc == NULL)
    {
        printf("No hdc was created with Display, trying now with DISPLAY\n");
        hdc=CreateDCW(L"DISPLAY",NULL,NULL,NULL);
        if (hdc == NULL)
        {
            printf("No hdc was created with DISPLAY, trying now with NULL\n");
            hdc=CreateDCW(NULL,NULL,NULL,NULL);
        }
    }

    if (hdc == NULL)
    {
        printf("No hdc was created at all perpare all test will fail\n");
        return NULL;
    }

    printf("Start testing of NtGdiDdCreateDirectDrawObject\n");

    retValue = OsThunkDdCreateDirectDrawObject(NULL);
    testing_noteq(retValue,NULL,fails,"NtGdiDdCreateDirectDrawObject(NULL);\0");

    retValue = OsThunkDdCreateDirectDrawObject(hdc);
    testing_eq(retValue,NULL,fails,"NtGdiDdCreateDirectDrawObject(hdc);\0");

    show_status(fails, "NtGdiDdCreateDirectDrawObject\0");

    return retValue;
}