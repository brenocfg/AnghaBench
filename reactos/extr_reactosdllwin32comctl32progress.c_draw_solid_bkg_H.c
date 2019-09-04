#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bottom; scalar_t__ left; int /*<<< orphan*/  top; } ;
struct TYPE_5__ {int /*<<< orphan*/  hbrBk; int /*<<< orphan*/  hdc; TYPE_1__ rect; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_2__ ProgressDrawInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void draw_solid_bkg_H (const ProgressDrawInfo* di, int start, int end)
{
    RECT r;
    SetRect(&r, di->rect.left + start, di->rect.top, di->rect.left + end, di->rect.bottom);
    FillRect (di->hdc, &r, di->hbrBk);
}