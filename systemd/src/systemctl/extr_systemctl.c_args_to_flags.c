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
typedef  int UnitFileFlags ;

/* Variables and functions */
 int UNIT_FILE_FORCE ; 
 int UNIT_FILE_RUNTIME ; 
 scalar_t__ arg_force ; 
 scalar_t__ arg_runtime ; 

__attribute__((used)) static UnitFileFlags args_to_flags(void) {
        return (arg_runtime ? UNIT_FILE_RUNTIME : 0) |
               (arg_force   ? UNIT_FILE_FORCE   : 0);
}