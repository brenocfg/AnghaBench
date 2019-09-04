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

/* Variables and functions */
 int FALSE ; 
 int HDR_BITRATE_VAL (unsigned long) ; 
 int /*<<< orphan*/  HDR_LAYER_VAL (unsigned long) ; 
 int HDR_SAMPLERATE_VAL (unsigned long) ; 
 unsigned long HDR_SYNC ; 
 int TRUE ; 

__attribute__((used)) static int head_check(unsigned long head)
{
	if
	(
		((head & HDR_SYNC) != HDR_SYNC)
		||
		/* layer: 01,10,11 is 1,2,3; 00 is reserved */
		(!(HDR_LAYER_VAL(head)))
		||
		/* 1111 means bad bitrate */
		(HDR_BITRATE_VAL(head) == 0xf)
		||
		/* sampling freq: 11 is reserved */
		(HDR_SAMPLERATE_VAL(head) == 0x3)
		/* here used to be a mpeg 2.5 check... re-enabled 2.5 decoding due to lack of evidence that it is really not good */
	)
	{
		return FALSE;
	}
	/* if no check failed, the header is valid (hopefully)*/
	else
	{
		return TRUE;
	}
}