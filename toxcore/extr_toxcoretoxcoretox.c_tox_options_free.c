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
struct Tox_Options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct Tox_Options*) ; 

void tox_options_free(struct Tox_Options *options)
{
    free(options);
}