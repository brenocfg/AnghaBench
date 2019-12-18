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
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_4__ {int request; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int REQ_UNKNOWN ; 
 scalar_t__ enum_equals (TYPE_1__,char const*,int) ; 
 TYPE_1__* req_info ; 
 int strlen (char const*) ; 

enum request
get_request(const char *name)
{
	int namelen = strlen(name);
	int i;

	for (i = 0; i < ARRAY_SIZE(req_info); i++)
		if (enum_equals(req_info[i], name, namelen))
			return req_info[i].request;

	return REQ_UNKNOWN;
}