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
 int /*<<< orphan*/  addcchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbuffer ; 
 char* xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *get_buffered_cstring(void)
{
	addcchar(0);
	return xstrdup(cbuffer);
}