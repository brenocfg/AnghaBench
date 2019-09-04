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
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int DCB_ENABLE ; 
 int DCB_RESET ; 
 int /*<<< orphan*/  SetBoundsRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_bounds ; 
 int /*<<< orphan*/  graphics_bounds ; 

__attribute__((used)) static void reset_bounds( HDC hdc )
{
    current_bounds = graphics_bounds;
    SetBoundsRect( hdc, NULL, DCB_RESET | DCB_ENABLE );
}