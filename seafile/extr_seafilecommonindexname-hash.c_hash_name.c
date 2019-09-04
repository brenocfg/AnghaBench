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

/* Variables and functions */
 unsigned char icase_hash (unsigned char) ; 

unsigned int hash_name(const char *name, int namelen)
{
    unsigned int hash = 0x123;

    do {
        unsigned char c = *name++;
        c = icase_hash(c);
        hash = hash*101 + c;
    } while (--namelen);
    return hash;
}