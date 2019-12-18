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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int SD_ID128_STRING_MAX ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int rmdir_one (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int remove_machine_id_directory(const char *root, sd_id128_t machine_id) {
        char buf[SD_ID128_STRING_MAX];

        assert(root);

        return rmdir_one(root, sd_id128_to_string(machine_id, buf));
}