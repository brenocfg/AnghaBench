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

__attribute__((used)) static UnitFileFlags unit_file_bools_to_flags(bool runtime, bool force) {
        return (runtime ? UNIT_FILE_RUNTIME : 0) |
               (force   ? UNIT_FILE_FORCE   : 0);
}