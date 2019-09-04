#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  VCHANNEL ;
struct TYPE_4__ {scalar_t__ encryption; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_1__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_ENCRYPT ; 
 int /*<<< orphan*/  channel_hdr ; 
 int /*<<< orphan*/  s_push_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_init (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

STREAM
channel_init(RDPCLIENT * This, VCHANNEL * channel, uint32 length)
{
	STREAM s;

	s = sec_init(This, This->encryption ? SEC_ENCRYPT : 0, length + 8);
	s_push_layer(s, channel_hdr, 8);
	return s;
}