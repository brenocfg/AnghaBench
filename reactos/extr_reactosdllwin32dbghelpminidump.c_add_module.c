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
struct dump_context {int alloc_modules; int num_modules; TYPE_1__* modules; int /*<<< orphan*/  hProcess; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ is_elf; void* checksum; void* timestamp; void* size; scalar_t__ base; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  scalar_t__ DWORD_PTR ;
typedef  scalar_t__ DWORD64 ;
typedef  void* DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetModuleFileNameExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcpynW (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static BOOL add_module(struct dump_context* dc, const WCHAR* name,
                       DWORD64 base, DWORD size, DWORD timestamp, DWORD checksum,
                       BOOL is_elf)
{
    if (!dc->modules)
    {
        dc->alloc_modules = 32;
        dc->modules = HeapAlloc(GetProcessHeap(), 0,
                                dc->alloc_modules * sizeof(*dc->modules));
    }
    else if(dc->num_modules >= dc->alloc_modules)
    {
        dc->alloc_modules *= 2;
        dc->modules = HeapReAlloc(GetProcessHeap(), 0, dc->modules,
                                  dc->alloc_modules * sizeof(*dc->modules));
    }
    if (!dc->modules)
    {
        dc->alloc_modules = dc->num_modules = 0;
        return FALSE;
    }
    if (is_elf ||
        !GetModuleFileNameExW(dc->hProcess, (HMODULE)(DWORD_PTR)base,
                              dc->modules[dc->num_modules].name,
                              sizeof(dc->modules[dc->num_modules].name) / sizeof(WCHAR)))
        lstrcpynW(dc->modules[dc->num_modules].name, name,
                  sizeof(dc->modules[dc->num_modules].name) / sizeof(WCHAR));
    dc->modules[dc->num_modules].base = base;
    dc->modules[dc->num_modules].size = size;
    dc->modules[dc->num_modules].timestamp = timestamp;
    dc->modules[dc->num_modules].checksum = checksum;
    dc->modules[dc->num_modules].is_elf = is_elf;
    dc->num_modules++;

    return TRUE;
}