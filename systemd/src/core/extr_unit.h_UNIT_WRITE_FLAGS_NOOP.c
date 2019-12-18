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
typedef  int UnitWriteFlags ;

/* Variables and functions */
 int UNIT_PERSISTENT ; 
 int UNIT_RUNTIME ; 

__attribute__((used)) static inline bool UNIT_WRITE_FLAGS_NOOP(UnitWriteFlags flags) {
        return (flags & (UNIT_RUNTIME|UNIT_PERSISTENT)) == 0;
}