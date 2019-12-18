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
typedef  int int32 ;

/* Variables and functions */
 int /*<<< orphan*/  RENDEZVOUS_BGW_LOADER_API_VERSION ; 
 void** find_rendezvous_variable (int /*<<< orphan*/ ) ; 

extern int
ts_bgw_loader_api_version(void)
{
	void **versionptr = find_rendezvous_variable(RENDEZVOUS_BGW_LOADER_API_VERSION);

	if (*versionptr == NULL)
		return 0;
	return *((int32 *) *versionptr);
}