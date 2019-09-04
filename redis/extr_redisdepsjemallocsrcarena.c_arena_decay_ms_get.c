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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  arena_decay_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_decay_ms_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
arena_decay_ms_get(arena_decay_t *decay) {
	return arena_decay_ms_read(decay);
}