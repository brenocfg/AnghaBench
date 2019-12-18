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
typedef  scalar_t__ zoneid_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ GLOBAL_ZONEID ; 
 int /*<<< orphan*/  GLOBAL_ZONEID_NAME ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

ssize_t
getzonenamebyid(zoneid_t id, char *buf, size_t buflen)
{
	if (id != GLOBAL_ZONEID)
		return (EINVAL);

	ssize_t ret = strlen(GLOBAL_ZONEID_NAME) + 1;

	if (buf == NULL || buflen == 0)
		return (ret);

	strncpy(buf, GLOBAL_ZONEID_NAME, buflen);
	buf[buflen - 1] = '\0';

	return (ret);
}