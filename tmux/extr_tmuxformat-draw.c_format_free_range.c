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
struct format_ranges {int dummy; } ;
struct format_range {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (struct format_ranges*,struct format_range*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct format_range*) ; 

__attribute__((used)) static void
format_free_range(struct format_ranges *frs, struct format_range *fr)
{
	TAILQ_REMOVE(frs, fr, entry);
	free(fr);
}