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
struct TYPE_5__ {int /*<<< orphan*/  null_cursor; } ;
struct TYPE_6__ {TYPE_1__ xwin; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  ui_set_cursor (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
ui_set_null_cursor(RDPCLIENT * This)
{
	ui_set_cursor(This, This->xwin.null_cursor);
}