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

/* Variables and functions */

__attribute__((used)) static int is_internal_uri(const char *uri)
{
	while (*uri >= 'a' && *uri <= 'z')
		++uri;
	if (uri[0] == ':' && uri[1] == '/' && uri[2] == '/')
		return 0;
	return 1;
}