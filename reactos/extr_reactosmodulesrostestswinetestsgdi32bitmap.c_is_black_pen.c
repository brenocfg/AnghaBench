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
typedef  scalar_t__ COLORREF ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ RGB (int,int,int) ; 

__attribute__((used)) static BOOL is_black_pen( COLORREF fg, COLORREF bg, int r, int g, int b )
{
    if (fg == 0 || bg == 0xffffff) return RGB(r,g,b) != 0xffffff && RGB(r,g,b) != bg;
    return RGB(r,g,b) == 0x000000 || RGB(r,g,b) == bg;
}