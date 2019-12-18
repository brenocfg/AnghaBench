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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static inline int efi_get_boot_option(uint16_t nr, char **title, sd_id128_t *part_uuid, char **path, bool *active) {
        return -EOPNOTSUPP;
}