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
typedef  int reentrancy_t ;

/* Variables and functions */
#define  arena_new_reentrant 130 
#define  libc_reentrant 129 
#define  non_reentrant 128 
 int /*<<< orphan*/  unreachable () ; 

__attribute__((used)) static const char *
reentrancy_t_str(reentrancy_t r) {
	switch (r) {
	case non_reentrant:
		return "non-reentrant";
	case libc_reentrant:
		return "libc-reentrant";
	case arena_new_reentrant:
		return "arena_new-reentrant";
	default:
		unreachable();
	}
}