#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_5__ {int /*<<< orphan*/  mcs_userid; } ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  False ; 
 int MCS_CJRQ ; 
 int /*<<< orphan*/ * iso_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/  iso_send (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_uint16_be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
mcs_send_cjrq(RDPCLIENT * This, uint16 chanid)
{
	STREAM s;

	DEBUG_RDP5(("Sending CJRQ for channel #%d\n", chanid));

	s = iso_init(This, 5);

	if(s == NULL)
		return False;

	out_uint8(s, (MCS_CJRQ << 2));
	out_uint16_be(s, This->mcs_userid);
	out_uint16_be(s, chanid);

	s_mark_end(s);
	return iso_send(This, s);
}