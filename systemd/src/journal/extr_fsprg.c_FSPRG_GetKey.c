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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  det_randomize (void*,size_t,void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initialize_libgcrypt (int) ; 
 int read_secpar (void const*) ; 

void FSPRG_GetKey(const void *state, void *key, size_t keylen, uint32_t idx) {
        uint16_t secpar;

        initialize_libgcrypt(false);

        secpar = read_secpar(state + 0);
        det_randomize(key, keylen, state + 2, 2 * secpar / 8 + 8, idx);
}