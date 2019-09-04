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
 void* pHIMAGELIST_QueryInterface ; 
 void* pImageList_Add ; 
 void* pImageList_BeginDrag ; 
 void* pImageList_CoCreateInstance ; 
 void* pImageList_Copy ; 
 void* pImageList_Create ; 
 void* pImageList_Destroy ; 
 void* pImageList_Draw ; 
 void* pImageList_DrawIndirect ; 
 void* pImageList_EndDrag ; 
 void* pImageList_GetDragImage ; 
 void* pImageList_GetFlags ; 
 void* pImageList_GetIconSize ; 
 void* pImageList_GetImageCount ; 
 void* pImageList_GetImageInfo ; 
 void* pImageList_LoadImageW ; 
 void* pImageList_Merge ; 
 void* pImageList_Read ; 
 void* pImageList_Remove ; 
 void* pImageList_Replace ; 
 void* pImageList_ReplaceIcon ; 
 void* pImageList_SetColorTable ; 
 void* pImageList_SetDragCursorImage ; 
 void* pImageList_SetImageCount ; 
 void* pImageList_Write ; 

__attribute__((used)) static void init_functions(void)
{
    HMODULE hComCtl32 = LoadLibraryA("comctl32.dll");

#define X(f) p##f = (void*)GetProcAddress(hComCtl32, #f);
#define X2(f, ord) p##f = (void*)GetProcAddress(hComCtl32, (const char *)ord);
    X(ImageList_Create);
    X(ImageList_Destroy);
    X(ImageList_Add);
    X(ImageList_DrawIndirect);
    X(ImageList_SetImageCount);
    X(ImageList_SetImageCount);
    X2(ImageList_SetColorTable, 390);
    X(ImageList_GetFlags);
    X(ImageList_BeginDrag);
    X(ImageList_GetDragImage);
    X(ImageList_EndDrag);
    X(ImageList_GetImageCount);
    X(ImageList_SetDragCursorImage);
    X(ImageList_GetIconSize);
    X(ImageList_Remove);
    X(ImageList_ReplaceIcon);
    X(ImageList_Replace);
    X(ImageList_Merge);
    X(ImageList_GetImageInfo);
    X(ImageList_Write);
    X(ImageList_Read);
    X(ImageList_Copy);
    X(ImageList_LoadImageW);
    X(ImageList_CoCreateInstance);
    X(HIMAGELIST_QueryInterface);
    X(ImageList_Draw);
#undef X
#undef X2
}