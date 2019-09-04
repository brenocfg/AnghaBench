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
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;
struct TYPE_6__ {TYPE_1__ rdpsnd; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  channel_init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint16_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static STREAM
rdpsnd_init_packet(RDPCLIENT * This, uint16 type, uint16 size)
{
	STREAM s;

	s = channel_init(This, This->rdpsnd.channel, size + 4);
	out_uint16_le(s, type);
	out_uint16_le(s, size);
	return s;
}