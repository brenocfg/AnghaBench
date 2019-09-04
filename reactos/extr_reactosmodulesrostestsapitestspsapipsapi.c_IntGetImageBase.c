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
struct TYPE_4__ {int dwSize; int /*<<< orphan*/  modBaseAddr; int /*<<< orphan*/  szExePath; } ;
typedef  TYPE_1__ MODULEENTRY32 ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateToolhelp32Snapshot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  Module32First (scalar_t__,TYPE_1__*) ; 
 scalar_t__ Module32Next (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  TH32CS_SNAPMODULE ; 
 scalar_t__ lstrcmpiA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LPVOID IntGetImageBase(LPCSTR Image)
{
    HANDLE Snap;
    MODULEENTRY32 Module;

    Snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
    if (Snap == INVALID_HANDLE_VALUE)
    {
        return NULL;
    }

    Module.dwSize = sizeof(MODULEENTRY32);
    if(!Module32First(Snap, &Module))
    {
        CloseHandle(Snap);
        return NULL;
    }

    do
    {
        if (lstrcmpiA(Module.szExePath, Image) == 0)
        {
            CloseHandle(Snap);
            return (LPVOID)Module.modBaseAddr;
        }
    } while(Module32Next(Snap, &Module));

    CloseHandle(Snap);
    return NULL;
}