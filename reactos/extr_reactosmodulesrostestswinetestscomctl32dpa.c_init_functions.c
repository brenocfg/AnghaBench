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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 void* pDPA_Clone ; 
 void* pDPA_Create ; 
 void* pDPA_CreateEx ; 
 void* pDPA_DeleteAllPtrs ; 
 void* pDPA_DeletePtr ; 
 void* pDPA_Destroy ; 
 void* pDPA_DestroyCallback ; 
 void* pDPA_EnumCallback ; 
 void* pDPA_GetPtr ; 
 void* pDPA_GetPtrIndex ; 
 void* pDPA_Grow ; 
 void* pDPA_InsertPtr ; 
 void* pDPA_LoadStream ; 
 void* pDPA_Merge ; 
 void* pDPA_SaveStream ; 
 void* pDPA_Search ; 
 void* pDPA_SetPtr ; 
 void* pDPA_Sort ; 

__attribute__((used)) static void init_functions(void)
{
    HMODULE hComCtl32 = LoadLibraryA("comctl32.dll");

#define X2(f, ord) p##f = (void*)GetProcAddress(hComCtl32, (const char *)ord);
    /* 4.00+ */
    X2(DPA_Clone, 331);
    X2(DPA_Create, 328);
    X2(DPA_CreateEx, 340);
    X2(DPA_DeleteAllPtrs, 337);
    X2(DPA_DeletePtr, 336);
    X2(DPA_Destroy, 329);
    X2(DPA_GetPtr, 332);
    X2(DPA_GetPtrIndex, 333);
    X2(DPA_Grow, 330);
    X2(DPA_InsertPtr, 334);
    X2(DPA_Search, 339);
    X2(DPA_SetPtr, 335);
    X2(DPA_Sort, 338);

    /* 4.71+ */
    X2(DPA_DestroyCallback, 386);
    X2(DPA_EnumCallback, 385);
    X2(DPA_LoadStream, 9);
    X2(DPA_Merge, 11);
    X2(DPA_SaveStream, 10);
#undef X2
}