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
typedef  scalar_t__ uint32_t ;
struct xxh32_state {scalar_t__ v4; scalar_t__ v3; scalar_t__ v2; scalar_t__ v1; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 scalar_t__ const PRIME32_1 ; 
 scalar_t__ const PRIME32_2 ; 
 int /*<<< orphan*/  memcpy (struct xxh32_state*,struct xxh32_state*,int) ; 
 int /*<<< orphan*/  memset (struct xxh32_state*,int /*<<< orphan*/ ,int) ; 

void xxh32_reset(struct xxh32_state *statePtr, const uint32_t seed)
{
	/* use a local state for memcpy() to avoid strict-aliasing warnings */
	struct xxh32_state state;

	memset(&state, 0, sizeof(state));
	state.v1 = seed + PRIME32_1 + PRIME32_2;
	state.v2 = seed + PRIME32_2;
	state.v3 = seed + 0;
	state.v4 = seed - PRIME32_1;
	memcpy(statePtr, &state, sizeof(state));
}