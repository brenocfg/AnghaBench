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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int GetLayout (int /*<<< orphan*/ ) ; 
 int LAYOUT_BITMAPORIENTATIONPRESERVED ; 
 int LAYOUT_RTL ; 
 int /*<<< orphan*/  SetLayout (int /*<<< orphan*/ ,int) ; 

VOID PreserveBitmapInRTL(HDC hdc)
{
    if (GetLayout(hdc) == LAYOUT_RTL)
        SetLayout(hdc, LAYOUT_RTL | LAYOUT_BITMAPORIENTATIONPRESERVED);
}