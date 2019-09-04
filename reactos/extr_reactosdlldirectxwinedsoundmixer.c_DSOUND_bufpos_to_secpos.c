#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int buflen; int /*<<< orphan*/  tmp_buffer_len; scalar_t__ freqAccNext; scalar_t__ freqAdjust; TYPE_1__* pwfx; TYPE_2__* device; } ;
struct TYPE_8__ {int nBlockAlign; } ;
struct TYPE_7__ {TYPE_3__* pwfx; } ;
struct TYPE_6__ {int nBlockAlign; } ;
typedef  TYPE_4__ IDirectSoundBufferImpl ;
typedef  int DWORD64 ;
typedef  int DWORD ;

/* Variables and functions */
 int DSOUND_FREQSHIFT ; 
 int /*<<< orphan*/  TRACE (char*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static DWORD DSOUND_bufpos_to_secpos(const IDirectSoundBufferImpl *dsb, DWORD bufpos)
{
	DWORD oAdv = dsb->device->pwfx->nBlockAlign, iAdv = dsb->pwfx->nBlockAlign, pos;
	DWORD64 framelen;
	DWORD64 acc;

	framelen = bufpos/oAdv;
	acc = framelen * (DWORD64)dsb->freqAdjust + (DWORD64)dsb->freqAccNext;
	acc = acc >> DSOUND_FREQSHIFT;
	pos = (DWORD)acc * iAdv;
	if (pos >= dsb->buflen)
		/* Because of differences between freqAcc and freqAccNext, this might happen */
		pos = dsb->buflen - iAdv;
	TRACE("Converted %d/%d to %d/%d\n", bufpos, dsb->tmp_buffer_len, pos, dsb->buflen);
	return pos;
}