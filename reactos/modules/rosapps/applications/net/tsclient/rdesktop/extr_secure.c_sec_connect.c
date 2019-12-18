#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  uint8 ;
struct stream {int size; int /*<<< orphan*/ * data; int /*<<< orphan*/ * p; } ;
struct TYPE_6__ {int disconnect_reason; scalar_t__ encryption; } ;
typedef  TYPE_1__ RDPCLIENT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  mcs_connect (TYPE_1__*,char*,char*,struct stream*) ; 
 int /*<<< orphan*/  sec_establish_key (TYPE_1__*) ; 
 int /*<<< orphan*/  sec_out_mcs_data (TYPE_1__*,struct stream*,int /*<<< orphan*/ *) ; 

BOOL
sec_connect(RDPCLIENT * This, char *server, wchar_t *hostname, char *cookie)
{
	struct stream mcs_data;
	void * p = malloc(512);

	if(p == NULL)
	{
		This->disconnect_reason = 262;
		return False;
	}

	/* We exchange some RDP data during the MCS-Connect */
	mcs_data.size = 512;
	mcs_data.p = mcs_data.data = (uint8 *) p;
	sec_out_mcs_data(This, &mcs_data, hostname);

	if (!mcs_connect(This, server, cookie, &mcs_data))
		return False;

	/*      sec_process_mcs_data(&mcs_data); */
	if (This->encryption)
		sec_establish_key(This);
	free(mcs_data.data);
	return True;
}