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
 int PARTITION_ROOT ; 
 int PARTITION_ROOT_SECONDARY ; 
 int PARTITION_ROOT_SECONDARY_VERITY ; 
 int PARTITION_ROOT_VERITY ; 
 int _PARTITION_DESIGNATOR_INVALID ; 

__attribute__((used)) static inline int PARTITION_VERITY_OF(int p) {
        if (p == PARTITION_ROOT)
                return PARTITION_ROOT_VERITY;
        if (p == PARTITION_ROOT_SECONDARY)
                return PARTITION_ROOT_SECONDARY_VERITY;
        return _PARTITION_DESIGNATOR_INVALID;
}