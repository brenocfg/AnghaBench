#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bits; int channels; int rate; int /*<<< orphan*/  byte_format; } ;
typedef  TYPE_1__ ao_sample_format ;
struct TYPE_5__ {int channels; scalar_t__ dsp_; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AO_FMT_LITTLE ; 
 int /*<<< orphan*/  False ; 
 TYPE_3__* This ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  ao_default_driver_id () ; 
 int /*<<< orphan*/  ao_initialize () ; 
 int /*<<< orphan*/ * ao_open_live (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_driver ; 
 int /*<<< orphan*/  g_reopened ; 
 int g_samplerate ; 
 int /*<<< orphan*/ * o_device ; 
 scalar_t__ queue_hi ; 
 scalar_t__ queue_lo ; 

BOOL
wave_out_open(void)
{
	ao_sample_format format;

	ao_initialize();
	default_driver = ao_default_driver_id();

	format.bits = 16;
	format.channels = 2;
	This->channels = 2;
	format.rate = 44100;
	g_samplerate = 44100;
	format.byte_format = AO_FMT_LITTLE;

	o_device = ao_open_live(default_driver, &format, NULL);
	if (o_device == NULL)
	{
		return False;
	}

	This->dsp_ = 0;
	queue_lo = queue_hi = 0;

	g_reopened = True;

	return True;
}