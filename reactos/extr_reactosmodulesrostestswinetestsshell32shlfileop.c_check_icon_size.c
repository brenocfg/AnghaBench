#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bm ;
struct TYPE_8__ {scalar_t__ bmWidth; scalar_t__ bmHeight; } ;
struct TYPE_7__ {int /*<<< orphan*/  hbmColor; } ;
struct TYPE_6__ {scalar_t__ cx; scalar_t__ cy; } ;
typedef  TYPE_1__ SIZE ;
typedef  int /*<<< orphan*/  IImageList ;
typedef  TYPE_2__ ICONINFO ;
typedef  int /*<<< orphan*/  HICON ;
typedef  int DWORD ;
typedef  TYPE_3__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  GetIconInfo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GetObjectW (int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 void* GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IImageList ; 
 int /*<<< orphan*/  IImageList_GetIconSize (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  IImageList_Release (int /*<<< orphan*/ *) ; 
 int SHGFI_SHELLICONSIZE ; 
 int SHGFI_SMALLICON ; 
 int /*<<< orphan*/  SHGetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  SHIL_LARGE ; 
 int /*<<< orphan*/  SHIL_SMALL ; 
 int /*<<< orphan*/  SM_CXICON ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void check_icon_size( HICON icon, DWORD flags )
{
    ICONINFO info;
    BITMAP bm;
    SIZE list_size, metrics_size;
    IImageList *list;

    GetIconInfo( icon, &info );
    GetObjectW( info.hbmColor, sizeof(bm), &bm );

    SHGetImageList( (flags & SHGFI_SMALLICON) ? SHIL_SMALL : SHIL_LARGE,
                    &IID_IImageList, (void **)&list );
    IImageList_GetIconSize( list, &list_size.cx, &list_size.cy );
    IImageList_Release( list );

    metrics_size.cx = GetSystemMetrics( (flags & SHGFI_SMALLICON) ? SM_CXSMICON : SM_CXICON );
    metrics_size.cy = GetSystemMetrics( (flags & SHGFI_SMALLICON) ? SM_CYSMICON : SM_CYICON );


    if (flags & SHGFI_SHELLICONSIZE)
    {
        ok( bm.bmWidth == list_size.cx, "got %d expected %d\n", bm.bmWidth, list_size.cx );
        ok( bm.bmHeight == list_size.cy, "got %d expected %d\n", bm.bmHeight, list_size.cy );
    }
    else
    {
        ok( bm.bmWidth == metrics_size.cx, "got %d expected %d\n", bm.bmWidth, metrics_size.cx );
        ok( bm.bmHeight == metrics_size.cy, "got %d expected %d\n", bm.bmHeight, metrics_size.cy );
    }
}