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
typedef  int ULONG_PTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HINSTANCE ;
typedef  scalar_t__ HICON ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IMAGE_ICON ; 
 int /*<<< orphan*/  LR_SHARED ; 
 scalar_t__ LoadCursorW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadIconW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ LoadImageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SS_REALSIZEIMAGE ; 

__attribute__((used)) static HICON STATIC_LoadIconW( HINSTANCE hInstance, LPCWSTR name, DWORD style )
{
    HICON hicon = 0;

    if (hInstance && ((ULONG_PTR)hInstance >> 16))
    {
        if ((style & SS_REALSIZEIMAGE) != 0)
            hicon = LoadImageW(hInstance, name, IMAGE_ICON, 0, 0, LR_SHARED);
        else
        {
            hicon = LoadIconW( hInstance, name );
            if (!hicon) hicon = LoadCursorW( hInstance, name );
        }
    }
    if (!hicon) hicon = LoadIconW( 0, name );
    /* Windows doesn't try to load a standard cursor,
       probably because most IDs for standard cursors conflict
       with the IDs for standard icons anyway */
    return hicon;
}