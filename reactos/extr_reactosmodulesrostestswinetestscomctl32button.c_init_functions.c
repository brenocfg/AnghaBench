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
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/ * GetModuleHandleA (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* pDefSubclassProc ; 
 void* pImageList_Add ; 
 void* pImageList_Create ; 
 void* pImageList_Destroy ; 
 void* pRemoveWindowSubclass ; 
 void* pSetWindowSubclass ; 

__attribute__((used)) static void init_functions(void)
{
    HMODULE hmod = GetModuleHandleA("comctl32.dll");
    ok(hmod != NULL, "got %p\n", hmod);

#define MAKEFUNC_ORD(f, ord) (p##f = (void*)GetProcAddress(hmod, (LPSTR)(ord)))
    MAKEFUNC_ORD(SetWindowSubclass, 410);
    MAKEFUNC_ORD(RemoveWindowSubclass, 412);
    MAKEFUNC_ORD(DefSubclassProc, 413);
#undef MAKEFUNC_ORD

#define X(f) p##f = (void *)GetProcAddress(hmod, #f);
    X(ImageList_Create);
    X(ImageList_Add);
    X(ImageList_Destroy);
#undef X
}