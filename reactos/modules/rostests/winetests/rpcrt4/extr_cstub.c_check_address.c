#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int e_lfanew; } ;
struct TYPE_4__ {int SizeOfImage; } ;
struct TYPE_5__ {TYPE_1__ OptionalHeader; } ;
typedef  TYPE_2__* PIMAGE_NT_HEADERS ;
typedef  TYPE_3__* PIMAGE_DOS_HEADER ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GetModuleHandleA (char*) ; 
 int TRUE ; 

__attribute__((used)) static BOOL check_address(void *actual, void *expected)
{
    static void *ole32_start = NULL;
    static void *ole32_end = NULL;
    static void *combase_start = NULL;
    static void *combase_end = NULL;

    if (actual == expected)
        return TRUE;

    /* On Win7, actual can be located inside ole32.dll */
    if (ole32_start == NULL || ole32_end == NULL)
    {
        PIMAGE_NT_HEADERS nt_headers;
        ole32_start = (void *) GetModuleHandleA("ole32.dll");
        if (ole32_start == NULL)
            return FALSE;
        nt_headers = (PIMAGE_NT_HEADERS)((char *) ole32_start + ((PIMAGE_DOS_HEADER) ole32_start)->e_lfanew);
        ole32_end = (void *)((char *) ole32_start + nt_headers->OptionalHeader.SizeOfImage);
    }

    if (ole32_start <= actual && actual < ole32_end)
        return TRUE;

    /* On Win8, actual can be located inside combase.dll */
    if (combase_start == NULL || combase_end == NULL)
    {
        PIMAGE_NT_HEADERS nt_headers;
        combase_start = (void *) GetModuleHandleA("combase.dll");
        if (combase_start == NULL)
            return FALSE;
        nt_headers = (PIMAGE_NT_HEADERS)((char *) combase_start + ((PIMAGE_DOS_HEADER) combase_start)->e_lfanew);
        combase_end = (void *)((char *) combase_start + nt_headers->OptionalHeader.SizeOfImage);
    }

    return (combase_start <= actual && actual < combase_end);
}