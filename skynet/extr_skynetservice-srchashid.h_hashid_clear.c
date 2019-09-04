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
struct hashid {int hashmod; scalar_t__ count; scalar_t__ cap; int /*<<< orphan*/ * hash; int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hashid_clear(struct hashid *hi) {
	skynet_free(hi->id);
	skynet_free(hi->hash);
	hi->id = NULL;
	hi->hash = NULL;
	hi->hashmod = 1;
	hi->cap = 0;
	hi->count = 0;
}