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
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RDPCLIENT ;

/* Variables and functions */
#define  LICENCE_TAG_AUTHREQ 132 
#define  LICENCE_TAG_DEMAND 131 
#define  LICENCE_TAG_ISSUE 130 
#define  LICENCE_TAG_REISSUE 129 
#define  LICENCE_TAG_RESULT 128 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  licence_process_authreq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_process_demand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_process_issue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unimpl (char*,int) ; 

void
licence_process(RDPCLIENT * This, STREAM s)
{
	uint8 tag;

	in_uint8(s, tag);
	in_uint8s(s, 3);	/* version, length */

	switch (tag)
	{
		case LICENCE_TAG_DEMAND:
			licence_process_demand(This, s);
			break;

		case LICENCE_TAG_AUTHREQ:
			licence_process_authreq(This, s);
			break;

		case LICENCE_TAG_ISSUE:
			licence_process_issue(This, s);
			break;

		case LICENCE_TAG_REISSUE:
		case LICENCE_TAG_RESULT:
			break;

		default:
			unimpl("licence tag 0x%x\n", tag);
	}
}