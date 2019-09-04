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
typedef  int uint64_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int BFOVERFLOW_SAT ; 
 int BFOVERFLOW_WRAP ; 
 int UINT64_MAX ; 

int checkUnsignedBitfieldOverflow(uint64_t value, int64_t incr, uint64_t bits, int owtype, uint64_t *limit) {
    uint64_t max = (bits == 64) ? UINT64_MAX : (((uint64_t)1<<bits)-1);
    int64_t maxincr = max-value;
    int64_t minincr = -value;

    if (value > max || (incr > 0 && incr > maxincr)) {
        if (limit) {
            if (owtype == BFOVERFLOW_WRAP) {
                goto handle_wrap;
            } else if (owtype == BFOVERFLOW_SAT) {
                *limit = max;
            }
        }
        return 1;
    } else if (incr < 0 && incr < minincr) {
        if (limit) {
            if (owtype == BFOVERFLOW_WRAP) {
                goto handle_wrap;
            } else if (owtype == BFOVERFLOW_SAT) {
                *limit = 0;
            }
        }
        return -1;
    }
    return 0;

handle_wrap:
    {
        uint64_t mask = ((uint64_t)-1) << bits;
        uint64_t res = value+incr;

        res &= ~mask;
        *limit = res;
    }
    return 1;
}