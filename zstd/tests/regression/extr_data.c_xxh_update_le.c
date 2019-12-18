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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  XXH64_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_isLittleEndian () ; 
 int /*<<< orphan*/  MEM_swap64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void xxh_update_le(XXH64_state_t* state, uint64_t data) {
    if (!MEM_isLittleEndian())
        data = MEM_swap64(data);
    XXH64_update(state, &data, sizeof(data));
}