#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dsp_; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  False ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 TYPE_1__* This ; 
 int /*<<< orphan*/  True ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  g_reopened ; 
 char* getenv (char*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ queue_hi ; 
 scalar_t__ queue_lo ; 
 char* xstrdup (char*) ; 

BOOL
wave_out_open(void)
{
	char *dsp_dev = getenv("AUDIODEV");

	if (dsp_dev == NULL)
	{
		dsp_dev = xstrdup("/dev/audio");
	}

	if ((This->dsp_ = open(dsp_dev, O_WRONLY | O_NONBLOCK)) == -1)
	{
		perror(dsp_dev);
		return False;
	}

	/* Non-blocking so that user interface is responsive */
	fcntl(This->dsp_, F_SETFL, fcntl(This->dsp_, F_GETFL) | O_NONBLOCK);

	queue_lo = queue_hi = 0;
	g_reopened = True;

	return True;
}