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
 scalar_t__ STR_IN_SET (char const*,char const*,char const*) ; 
 scalar_t__ startswith (char const*,char const*) ; 
 char* strjoina (char const*,char*) ; 

__attribute__((used)) static bool file_has_type_prefix(const char *prefix, const char *filename) {
        const char *full, *tilded, *atted;

        full = strjoina(prefix, ".journal");
        tilded = strjoina(full, "~");
        atted = strjoina(prefix, "@");

        return STR_IN_SET(filename, full, tilded) ||
               startswith(filename, atted);
}