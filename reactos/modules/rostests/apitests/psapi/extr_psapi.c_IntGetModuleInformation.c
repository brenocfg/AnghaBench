#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Path; void* Len; int /*<<< orphan*/  ImageBase; } ;
typedef  TYPE_1__ TEST_MODULE_INFO ;
typedef  char* LPCSTR ;
typedef  char CHAR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int GetSystemWindowsDirectory (char*,int) ; 
 int /*<<< orphan*/  IntGetImageBase (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 void* strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN IntGetModuleInformation(LPCSTR Module, BOOLEAN IsDriver, BOOLEAN IsProcMod, BOOLEAN BaseName, TEST_MODULE_INFO * Info)
{
    CHAR System[255];
    UINT Len;

    memset(Info, 0, sizeof(TEST_MODULE_INFO));

    /* Get system path */
    Len = GetSystemWindowsDirectory(System, 255);
    if (Len > 255 || Len == 0)
    {
        printf("GetSystemWindowsDirectory failed\n");
        return FALSE;
    }

    /* Make path to module */
    strcat(System, "\\system32\\");
    if (IsDriver) strcat(System, "drivers\\");
    strcat(System, Module);

    /* Get base address */
    if (IsProcMod)
    {
        Info->ImageBase = IntGetImageBase(System);
        if (!Info->ImageBase)
        {
            printf("IntGetImageBase failed\n");
            return FALSE;
        }
    }
    else
    {
        /* FIXME */
        printf("Not supported yet!\n");
        return FALSE;
    }

    if (BaseName)
    {
        strcpy(Info->Path, Module);
        Info->Len = strlen(Info->Path);
    }
    else
    {
        /* Skip disk */
        strcpy(Info->Path, System + 2);
        Info->Len = strlen(Info->Path);
    }

    return TRUE;
}