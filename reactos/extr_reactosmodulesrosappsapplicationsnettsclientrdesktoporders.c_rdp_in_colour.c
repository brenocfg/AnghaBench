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
typedef  int uint32 ;
typedef  int /*<<< orphan*/  STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rdp_in_colour(STREAM s, uint32 * colour)
{
	uint32 i;
	in_uint8(s, i);
	*colour = i;
	in_uint8(s, i);
	*colour |= i << 8;
	in_uint8(s, i);
	*colour |= i << 16;
}