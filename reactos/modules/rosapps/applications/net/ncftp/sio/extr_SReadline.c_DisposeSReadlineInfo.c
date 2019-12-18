#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bufSizeMax; scalar_t__ malloc; struct TYPE_5__* buf; } ;
typedef  TYPE_1__ SReadlineInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
DisposeSReadlineInfo(SReadlineInfo *srl)
{
	memset(srl->buf, 0, srl->bufSizeMax);
	if (srl->malloc != 0)
		free(srl->buf);
	memset(srl, 0, sizeof(SReadlineInfo));

	/* Note: it does not close(srl->fd). */
}