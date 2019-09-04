#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bmHeight; int /*<<< orphan*/  bmWidth; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBITMAP ;
typedef  TYPE_1__ BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateCompatibleBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  GetObjectW (scalar_t__,int,TYPE_1__*) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static HRESULT dup_bitmap(HBITMAP src, HBITMAP *pdest)
{
    HDC src_dc;
    HGDIOBJ orig_src_bitmap;
    BITMAP bm;
    HBITMAP dest;

    src_dc = CreateCompatibleDC(NULL);
    orig_src_bitmap = SelectObject(src_dc, src);
    GetObjectW(src, sizeof bm, &bm);
    dest = CreateCompatibleBitmap(src_dc, bm.bmWidth, bm.bmHeight);
    if (dest)
    {
        HDC dest_dc = CreateCompatibleDC(NULL);
        HGDIOBJ orig_dest_bitmap = SelectObject(dest_dc, dest);
        BitBlt(dest_dc, 0, 0, bm.bmWidth, bm.bmHeight, src_dc, 0, 0, SRCCOPY);
        SelectObject(dest_dc, orig_dest_bitmap);
        DeleteDC(dest_dc);
    }
    SelectObject(src_dc, orig_src_bitmap);
    DeleteDC(src_dc);
    *pdest = dest;
    return dest ? S_OK : E_FAIL;
}