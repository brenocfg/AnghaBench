#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  channel; } ;
struct TYPE_10__ {TYPE_1__ rdpsnd; } ;
struct TYPE_9__ {scalar_t__ channel_hdr; scalar_t__ end; } ;
typedef  TYPE_2__* STREAM ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  channel_send (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
rdpsnd_send(RDPCLIENT * This, STREAM s)
{
#ifdef RDPSND_DEBUG
	printf("RDPSND send:\n");
	hexdump(s->channel_hdr + 8, s->end - s->channel_hdr - 8);
#endif

	channel_send(This, s, This->rdpsnd.channel);
}