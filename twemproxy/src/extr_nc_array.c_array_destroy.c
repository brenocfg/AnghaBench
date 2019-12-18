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
struct array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_deinit (struct array*) ; 
 int /*<<< orphan*/  nc_free (struct array*) ; 

void
array_destroy(struct array *a)
{
    array_deinit(a);
    nc_free(a);
}