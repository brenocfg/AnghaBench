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

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  hComctl32 ; 
 void* pAddMRUData ; 
 void* pAddMRUStringA ; 
 void* pCreateMRUListA ; 
 void* pCreateMRUListLazyA ; 
 void* pCreateMRUListLazyW ; 
 void* pCreateMRUListW ; 
 void* pEnumMRUListA ; 
 void* pEnumMRUListW ; 
 void* pFindMRUData ; 
 void* pFreeMRUList ; 

__attribute__((used)) static void init_functions(void)
{
    hComctl32 = LoadLibraryA("comctl32.dll");

#define X2(f, ord) p##f = (void*)GetProcAddress(hComctl32, (const char *)ord);
    X2(CreateMRUListA, 151);
    X2(FreeMRUList, 152);
    X2(AddMRUStringA, 153);
    X2(EnumMRUListA, 154);
    X2(CreateMRUListLazyA, 157);
    X2(AddMRUData, 167);
    X2(FindMRUData, 169);
    X2(CreateMRUListW, 400);
    X2(EnumMRUListW, 403);
    X2(CreateMRUListLazyW, 404);
#undef X2
}