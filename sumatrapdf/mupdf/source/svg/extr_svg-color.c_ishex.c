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

__attribute__((used)) static int ishex(int chr)
{
	if (chr >= '0' && chr <= '9') return 1;
	if (chr >= 'A' && chr <= 'F') return 1;
	if (chr >= 'a' && chr <= 'f') return 1;
	return 0;
}