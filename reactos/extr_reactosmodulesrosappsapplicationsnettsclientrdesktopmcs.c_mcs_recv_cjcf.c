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
typedef  int uint8 ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int MCS_CJCF ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * iso_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_check_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
mcs_recv_cjcf(RDPCLIENT * This)
{
	uint8 opcode, result;
	STREAM s;

	s = iso_recv(This, NULL);
	if (s == NULL)
		return False;

	in_uint8(s, opcode);
	if ((opcode >> 2) != MCS_CJCF)
	{
		error("expected CJcf, got %d\n", opcode);
		return False;
	}

	in_uint8(s, result);
	if (result != 0)
	{
		error("CJrq: %d\n", result);
		return False;
	}

	in_uint8s(s, 4);	/* mcs_userid, req_chanid */
	if (opcode & 2)
		in_uint8s(s, 2);	/* join_chanid */

	return s_check_end(s);
}