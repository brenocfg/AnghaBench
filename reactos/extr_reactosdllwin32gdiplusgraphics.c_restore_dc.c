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
struct TYPE_3__ {int /*<<< orphan*/  hdc; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_1__ GpGraphics ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_PEN ; 
 int /*<<< orphan*/  RestoreDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void restore_dc(GpGraphics *graphics, INT state)
{
    DeleteObject(SelectObject(graphics->hdc, GetStockObject(NULL_PEN)));
    RestoreDC(graphics->hdc, state);
}