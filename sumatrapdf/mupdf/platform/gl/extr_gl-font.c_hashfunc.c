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
struct key {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int hashfunc(struct key *key)
{
	unsigned char *buf = (unsigned char *)key;
	unsigned int len = sizeof(struct key);
	unsigned int h = 0;
	while (len--)
		h = *buf++ + (h << 6) + (h << 16) - h;
	return h;
}