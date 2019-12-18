#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; char const* name; } ;
typedef  scalar_t__ FormatSubstitutionType ;

/* Variables and functions */
 size_t ELEMENTSOF (TYPE_1__*) ; 
 TYPE_1__* map ; 

__attribute__((used)) static const char *format_type_to_string(FormatSubstitutionType t) {
        for (size_t i = 0; i < ELEMENTSOF(map); i++)
                if (map[i].type == t)
                        return map[i].name;
        return NULL;
}