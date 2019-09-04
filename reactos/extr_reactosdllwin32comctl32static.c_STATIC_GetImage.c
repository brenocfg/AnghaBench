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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HICON_GWL_OFFSET ; 
 int /*<<< orphan*/  IMAGE_BITMAP ; 
 int /*<<< orphan*/  IMAGE_CURSOR ; 
 int /*<<< orphan*/  IMAGE_ENHMETAFILE ; 
 int /*<<< orphan*/  IMAGE_ICON ; 
#define  SS_BITMAP 130 
#define  SS_ENHMETAFILE 129 
#define  SS_ICON 128 
 int SS_TYPEMASK ; 

__attribute__((used)) static HANDLE STATIC_GetImage( HWND hwnd, WPARAM wParam, DWORD style )
{
    switch (style & SS_TYPEMASK)
    {
        case SS_ICON:
            if ((wParam != IMAGE_ICON) &&
                (wParam != IMAGE_CURSOR)) return NULL;
            break;
        case SS_BITMAP:
            if (wParam != IMAGE_BITMAP) return NULL;
            break;
        case SS_ENHMETAFILE:
            if (wParam != IMAGE_ENHMETAFILE) return NULL;
            break;
        default:
            return NULL;
    }
    return (HANDLE)GetWindowLongPtrW( hwnd, HICON_GWL_OFFSET );
}