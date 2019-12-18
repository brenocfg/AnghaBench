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

/* Variables and functions */
 char* ModuleTypeNameCharSet ; 
 char* strchr (char const*,char const) ; 
 int strlen (char const*) ; 

uint64_t moduleTypeEncodeId(const char *name, int encver) {
    /* We use 64 symbols so that we can map each character into 6 bits
     * of the final output. */
    const char *cset = ModuleTypeNameCharSet;
    if (strlen(name) != 9) return 0;
    if (encver < 0 || encver > 1023) return 0;

    uint64_t id = 0;
    for (int j = 0; j < 9; j++) {
        char *p = strchr(cset,name[j]);
        if (!p) return 0;
        unsigned long pos = p-cset;
        id = (id << 6) | pos;
    }
    id = (id << 10) | encver;
    return id;
}