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
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int MCS_AURQ ; 
 int /*<<< orphan*/ * iso_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iso_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_uint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  s_mark_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
mcs_send_aurq(RDPCLIENT * This)
{
	STREAM s;

	s = iso_init(This, 1);

	if(s == NULL)
		return False;

	out_uint8(s, (MCS_AURQ << 2));

	s_mark_end(s);
	return iso_send(This, s);
}