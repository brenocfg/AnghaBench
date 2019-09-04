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
typedef  size_t varInds_t ;

/* Variables and functions */
 size_t* rangetable ; 
 size_t const strt_ind ; 

__attribute__((used)) static size_t memoTableLen(const varInds_t* varyParams, const size_t varyLen) {
    size_t arrayLen = 1;
    size_t i;
    for(i = 0; i < varyLen; i++) {
        if(varyParams[i] == strt_ind) continue; /* strategy separated by table */
        arrayLen *= rangetable[varyParams[i]];
    }
    return arrayLen;
}