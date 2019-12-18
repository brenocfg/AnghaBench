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
struct siphash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_TO_PTR (int) ; 
 int PTR_TO_INT (void const*) ; 
 void trivial_hash_func (int /*<<< orphan*/ ,struct siphash*) ; 

__attribute__((used)) static void crippled_hashmap_func(const void *p, struct siphash *state) {
        return trivial_hash_func(INT_TO_PTR(PTR_TO_INT(p) & 0xff), state);
}