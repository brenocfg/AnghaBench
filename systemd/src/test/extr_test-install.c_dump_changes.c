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
struct TYPE_3__ {scalar_t__ type; char* path; char* source; } ;
typedef  TYPE_1__ UnitFileChange ;

/* Variables and functions */
 scalar_t__ UNIT_FILE_SYMLINK ; 
 scalar_t__ UNIT_FILE_UNLINK ; 
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 

__attribute__((used)) static void dump_changes(UnitFileChange *c, unsigned n) {
        unsigned i;

        assert_se(n == 0 || c);

        for (i = 0; i < n; i++) {
                if (c[i].type == UNIT_FILE_UNLINK)
                        printf("rm '%s'\n", c[i].path);
                else if (c[i].type == UNIT_FILE_SYMLINK)
                        printf("ln -s '%s' '%s'\n", c[i].source, c[i].path);
        }
}