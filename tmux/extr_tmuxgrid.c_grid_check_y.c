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
typedef  scalar_t__ u_int ;
struct grid {scalar_t__ hsize; scalar_t__ sy; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_debug (char*,char const*,scalar_t__) ; 

__attribute__((used)) static int
grid_check_y(struct grid *gd, const char* from, u_int py)
{
	if (py >= gd->hsize + gd->sy) {
		log_debug("%s: y out of range: %u", from, py);
		return (-1);
	}
	return (0);
}