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
struct TYPE_4__ {scalar_t__ bottom; int /*<<< orphan*/  top; scalar_t__ right; int /*<<< orphan*/  left; } ;
struct TYPE_5__ {TYPE_1__ format_rect; } ;
typedef  int /*<<< orphan*/ * LPINT ;
typedef  TYPE_2__ EDITSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void EDIT_ConfinePoint(const EDITSTATE *es, LPINT x, LPINT y)
{
	*x = min(max(*x, es->format_rect.left), es->format_rect.right - 1);
	*y = min(max(*y, es->format_rect.top), es->format_rect.bottom - 1);
}