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
struct footnote_ref {int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufrelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct footnote_ref*) ; 

__attribute__((used)) static void
free_footnote_ref(struct footnote_ref *ref)
{
	bufrelease(ref->contents);
	free(ref);
}