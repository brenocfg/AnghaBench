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
typedef  int ExecCommandFlags ;

/* Variables and functions */
 size_t ELEMENTSOF (char const**) ; 
 char const** exec_command_strings ; 

const char* exec_command_flags_to_string(ExecCommandFlags i) {
        size_t idx;

        for (idx = 0; idx < ELEMENTSOF(exec_command_strings); idx++)
                if (i == (1 << idx))
                        return exec_command_strings[idx];

        return NULL;
}