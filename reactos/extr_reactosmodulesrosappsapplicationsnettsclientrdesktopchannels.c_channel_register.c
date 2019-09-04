#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_8__ {void (* process ) (TYPE_1__*,STREAM) ;int /*<<< orphan*/  flags; int /*<<< orphan*/  name; scalar_t__ mcs_id; } ;
typedef  TYPE_2__ VCHANNEL ;
struct TYPE_7__ {size_t num_channels; TYPE_2__* channels; int /*<<< orphan*/  use_rdp5; } ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 size_t MAX_CHANNELS ; 
 scalar_t__ MCS_GLOBAL_CHANNEL ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

VCHANNEL *
channel_register(RDPCLIENT * This, char *name, uint32 flags, void (*callback) (RDPCLIENT *, STREAM))
{
	VCHANNEL *channel;

	if (!This->use_rdp5)
		return NULL;

	if (This->num_channels >= MAX_CHANNELS)
	{
		error("Channel table full, increase MAX_CHANNELS\n");
		return NULL;
	}

	channel = &This->channels[This->num_channels];
	channel->mcs_id = MCS_GLOBAL_CHANNEL + 1 + This->num_channels;
	strncpy(channel->name, name, 8);
	channel->flags = flags;
	channel->process = callback;
	This->num_channels++;
	return channel;
}