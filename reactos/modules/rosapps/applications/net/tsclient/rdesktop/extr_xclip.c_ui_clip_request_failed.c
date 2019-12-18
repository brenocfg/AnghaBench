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
struct TYPE_5__ {int /*<<< orphan*/  has_selection_request; int /*<<< orphan*/  selection_request; } ;
struct TYPE_6__ {TYPE_1__ xclip; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  xclip_refuse_selection (TYPE_2__*,int /*<<< orphan*/ *) ; 

void
ui_clip_request_failed(RDPCLIENT * This)
{
	xclip_refuse_selection(This, &This->xclip.selection_request);
	This->xclip.has_selection_request = False;
}