#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdc; int /*<<< orphan*/  theme; TYPE_1__ rect; } ;
struct TYPE_7__ {scalar_t__ right; int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; scalar_t__ left; } ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ ProgressDrawInfo ;

/* Variables and functions */
 int /*<<< orphan*/  DrawThemeBackground (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PP_CHUNK ; 

__attribute__((used)) static void draw_theme_bar_H (const ProgressDrawInfo* di, int start, int end)
{
    RECT r;
    r.left = di->rect.left + start;
    r.top = di->rect.top;
    r.bottom = di->rect.bottom;
    r.right = di->rect.left + end;
    DrawThemeBackground (di->theme, di->hdc, PP_CHUNK, 0, &r, NULL);
}