#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16 ;
typedef  int uint ;
struct TYPE_6__ {int gain; int balance; } ;
struct TYPE_7__ {TYPE_1__ play; } ;
typedef  TYPE_2__ audio_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  dsp_; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_INITINFO (TYPE_2__*) ; 
 int AUDIO_MAX_GAIN ; 
 int AUDIO_MID_BALANCE ; 
 int /*<<< orphan*/  AUDIO_SETINFO ; 
 TYPE_4__* This ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  perror (char*) ; 

void
wave_out_volume(uint16 left, uint16 right)
{
	audio_info_t info;
	uint balance;
	uint volume;

	AUDIO_INITINFO(&info);

	volume = (left > right) ? left : right;

	if (volume / AUDIO_MID_BALANCE != 0)
	{
		balance =
			AUDIO_MID_BALANCE - (left / (volume / AUDIO_MID_BALANCE)) +
			(right / (volume / AUDIO_MID_BALANCE));
	}
	else
	{
		balance = AUDIO_MID_BALANCE;
	}

	info.play.gain = volume / (65536 / AUDIO_MAX_GAIN);
	info.play.balance = balance;

	if (ioctl(This->dsp_, AUDIO_SETINFO, &info) == -1)
	{
		perror("AUDIO_SETINFO");
		return;
	}
}