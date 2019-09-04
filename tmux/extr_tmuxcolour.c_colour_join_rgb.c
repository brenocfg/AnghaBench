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
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ r ;
typedef  scalar_t__ g ;
typedef  scalar_t__ b ;

/* Variables and functions */
 int COLOUR_FLAG_RGB ; 

int
colour_join_rgb(u_char r, u_char g, u_char b)
{
	return ((((int)((r) & 0xff)) << 16) |
	    (((int)((g) & 0xff)) << 8) |
	    (((int)((b) & 0xff))) | COLOUR_FLAG_RGB);
}