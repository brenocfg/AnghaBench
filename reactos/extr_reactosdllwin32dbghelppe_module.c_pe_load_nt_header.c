#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dos ;
struct TYPE_5__ {scalar_t__ e_magic; scalar_t__ Signature; scalar_t__ e_lfanew; } ;
typedef  TYPE_1__ IMAGE_NT_HEADERS ;
typedef  TYPE_1__ IMAGE_DOS_HEADER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD64 ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ IMAGE_DOS_SIGNATURE ; 
 scalar_t__ IMAGE_NT_SIGNATURE ; 
 scalar_t__ ReadProcessMemory (int /*<<< orphan*/ ,char*,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

BOOL pe_load_nt_header(HANDLE hProc, DWORD64 base, IMAGE_NT_HEADERS* nth)
{
    IMAGE_DOS_HEADER    dos;

    return ReadProcessMemory(hProc, (char*)(DWORD_PTR)base, &dos, sizeof(dos), NULL) &&
        dos.e_magic == IMAGE_DOS_SIGNATURE &&
        ReadProcessMemory(hProc, (char*)(DWORD_PTR)(base + dos.e_lfanew),
                          nth, sizeof(*nth), NULL) &&
        nth->Signature == IMAGE_NT_SIGNATURE;
}