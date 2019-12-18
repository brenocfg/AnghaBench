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
struct TYPE_3__ {scalar_t__ bufLim; scalar_t__ bufPtr; scalar_t__ bufSizeMax; scalar_t__ buf; scalar_t__ bufSize; } ;
typedef  TYPE_1__ SReadlineInfo ;

/* Variables and functions */
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void
FlushSReadlineInfo(SReadlineInfo *srl)
{
	/* Discards any input left in the current buffer,
	 * and resets the buffer and its pointer.
	 */
	srl->bufSize = srl->bufSizeMax;
	memset(srl->buf, 0, srl->bufSize);
	srl->bufLim = srl->buf + srl->bufSizeMax;

	/* This line sets the buffer pointer
	 * so that the first thing to do is reset and fill the buffer
	 * using real I/O.
	 */
	srl->bufPtr = srl->bufLim;
}