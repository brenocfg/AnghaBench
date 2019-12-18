#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ biCompression; int biBitCount; } ;
struct TYPE_6__ {TYPE_1__ bmiHeader; scalar_t__ bmiColors; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_2__ BITMAPINFO ;

/* Variables and functions */
 scalar_t__ BI_BITFIELDS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  draw_text_2 (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_text( HDC hdc, const BITMAPINFO *bmi, BYTE *bits )
{
    draw_text_2( hdc, bmi, bits, FALSE );

    /* Rounding errors make these cases hard to test */
    if ((bmi->bmiHeader.biCompression == BI_BITFIELDS && ((DWORD*)bmi->bmiColors)[0] == 0x3f000) ||
        (bmi->bmiHeader.biBitCount == 16))
        return;

    draw_text_2( hdc, bmi, bits, TRUE );
}