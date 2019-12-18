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
struct TYPE_3__ {int class; char const* name; } ;
typedef  int ExitStatusClass ;

/* Variables and functions */
 size_t ELEMENTSOF (TYPE_1__*) ; 
 TYPE_1__* exit_status_mappings ; 

const char* exit_status_to_string(int code, ExitStatusClass class) {
        if (code < 0 || (size_t) code >= ELEMENTSOF(exit_status_mappings))
                return NULL;
        return class & exit_status_mappings[code].class ? exit_status_mappings[code].name : NULL;
}