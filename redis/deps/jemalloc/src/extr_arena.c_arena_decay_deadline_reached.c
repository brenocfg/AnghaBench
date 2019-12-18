#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nstime_t ;
struct TYPE_3__ {int /*<<< orphan*/  deadline; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 scalar_t__ nstime_compare (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool
arena_decay_deadline_reached(const arena_decay_t *decay, const nstime_t *time) {
	return (nstime_compare(&decay->deadline, time) <= 0);
}