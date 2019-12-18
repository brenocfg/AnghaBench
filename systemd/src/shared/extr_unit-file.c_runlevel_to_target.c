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
 scalar_t__ in_initrd () ; 
 char** rlmap ; 
 char** rlmap_initrd ; 
 char* startswith (char const*,char*) ; 
 scalar_t__ streq (char const*,char const* const) ; 

const char* runlevel_to_target(const char *word) {
        const char * const *rlmap_ptr;
        size_t i;

        if (!word)
                return NULL;

        if (in_initrd()) {
                word = startswith(word, "rd.");
                if (!word)
                        return NULL;
        }

        rlmap_ptr = in_initrd() ? rlmap_initrd : rlmap;

        for (i = 0; rlmap_ptr[i]; i += 2)
                if (streq(word, rlmap_ptr[i]))
                        return rlmap_ptr[i+1];

        return NULL;
}