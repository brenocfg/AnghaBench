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
typedef  unsigned long xmlChar ;

/* Variables and functions */

__attribute__((used)) static unsigned long
xmlDictComputeFastKey(const xmlChar *name, int namelen, int seed) {
    unsigned long value = seed;

    if (name == NULL) return(0);
    value = *name;
    value <<= 5;
    if (namelen > 10) {
        value += name[namelen - 1];
        namelen = 10;
    }
    switch (namelen) {
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
        default: break;
    }
    return(value);
}