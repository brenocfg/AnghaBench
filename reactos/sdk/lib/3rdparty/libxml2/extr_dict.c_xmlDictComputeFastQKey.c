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
typedef  int xmlChar ;

/* Variables and functions */

__attribute__((used)) static unsigned long
xmlDictComputeFastQKey(const xmlChar *prefix, int plen,
                       const xmlChar *name, int len, int seed)
{
    unsigned long value = (unsigned long) seed;

    if (plen == 0)
	value += 30 * (unsigned long) ':';
    else
	value += 30 * (*prefix);

    if (len > 10) {
        int offset = len - (plen + 1 + 1);
	if (offset < 0)
	    offset = len - (10 + 1);
	value += name[offset];
        len = 10;
	if (plen > 10)
	    plen = 10;
    }
    switch (plen) {
        case 10: value += prefix[9];
        /* Falls through. */
        case 9: value += prefix[8];
        /* Falls through. */
        case 8: value += prefix[7];
        /* Falls through. */
        case 7: value += prefix[6];
        /* Falls through. */
        case 6: value += prefix[5];
        /* Falls through. */
        case 5: value += prefix[4];
        /* Falls through. */
        case 4: value += prefix[3];
        /* Falls through. */
        case 3: value += prefix[2];
        /* Falls through. */
        case 2: value += prefix[1];
        /* Falls through. */
        case 1: value += prefix[0];
        /* Falls through. */
        default: break;
    }
    len -= plen;
    if (len > 0) {
        value += (unsigned long) ':';
	len--;
    }
    switch (len) {
        case 10: value += name[9];
        /* Falls through. */
        case 9: value += name[8];
        /* Falls through. */
        case 8: value += name[7];
        /* Falls through. */
        case 7: value += name[6];
        /* Falls through. */
        case 6: value += name[5];
        /* Falls through. */
        case 5: value += name[4];
        /* Falls through. */
        case 4: value += name[3];
        /* Falls through. */
        case 3: value += name[2];
        /* Falls through. */
        case 2: value += name[1];
        /* Falls through. */
        case 1: value += name[0];
        /* Falls through. */
        default: break;
    }
    return(value);
}