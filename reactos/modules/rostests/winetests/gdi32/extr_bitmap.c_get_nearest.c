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
typedef  int COLORREF ;

/* Variables and functions */

__attribute__((used)) static COLORREF get_nearest( int r, int g, int b )
{
    return (r*r + g*g + b*b < (255-r)*(255-r) + (255-g)*(255-g) + (255-b)*(255-b)) ? 0x000000 : 0xffffff;
}