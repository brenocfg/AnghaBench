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
 scalar_t__ UNIT_TARGET ; 
 int strcasecmp (char* const,char* const) ; 
 scalar_t__ unit_name_to_type (char* const) ; 

__attribute__((used)) static int list_dependencies_compare(char * const *a, char * const *b) {
        if (unit_name_to_type(*a) == UNIT_TARGET && unit_name_to_type(*b) != UNIT_TARGET)
                return 1;
        if (unit_name_to_type(*a) != UNIT_TARGET && unit_name_to_type(*b) == UNIT_TARGET)
                return -1;

        return strcasecmp(*a, *b);
}