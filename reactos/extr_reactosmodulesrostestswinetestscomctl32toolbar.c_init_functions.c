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
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 void* pCreateToolbarEx ; 
 void* pImageList_Destroy ; 
 void* pImageList_GetIconSize ; 
 void* pImageList_GetImageCount ; 
 void* pImageList_LoadImageA ; 

__attribute__((used)) static void init_functions(void)
{
    HMODULE hComCtl32 = LoadLibraryA("comctl32.dll");

#define X(f) p##f = (void*)GetProcAddress(hComCtl32, #f);
    X(CreateToolbarEx);
    X(ImageList_GetIconSize);
    X(ImageList_GetImageCount);
    X(ImageList_LoadImageA);
    X(ImageList_Destroy);
#undef X
}