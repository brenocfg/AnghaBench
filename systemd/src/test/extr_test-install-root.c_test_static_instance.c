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
typedef  scalar_t__ UnitFileState ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ UNIT_FILE_DISABLED ; 
 scalar_t__ UNIT_FILE_STATIC ; 
 int /*<<< orphan*/  UNIT_FILE_SYSTEM ; 
 int /*<<< orphan*/  WRITE_STRING_FILE_CREATE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 char* strjoina (char const*,char*) ; 
 scalar_t__ symlink (char*,char const*) ; 
 int /*<<< orphan*/  unit_file_get_state (int /*<<< orphan*/ ,char const*,char*,scalar_t__*) ; 
 scalar_t__ write_string_file (char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_static_instance(const char *root) {
        UnitFileState state;
        const char *p;

        assert_se(unit_file_get_state(UNIT_FILE_SYSTEM, root, "static-instance@.service", &state) == -ENOENT);
        assert_se(unit_file_get_state(UNIT_FILE_SYSTEM, root, "static-instance@foo.service", &state) == -ENOENT);

        p = strjoina(root, "/usr/lib/systemd/system/static-instance@.service");
        assert_se(write_string_file(p,
                                    "[Install]\n"
                                    "WantedBy=multi-user.target\n", WRITE_STRING_FILE_CREATE) >= 0);

        assert_se(unit_file_get_state(UNIT_FILE_SYSTEM, root, "static-instance@.service", &state) >= 0 && state == UNIT_FILE_DISABLED);
        assert_se(unit_file_get_state(UNIT_FILE_SYSTEM, root, "static-instance@foo.service", &state) >= 0 && state == UNIT_FILE_DISABLED);

        p = strjoina(root, "/usr/lib/systemd/system/static-instance@foo.service");
        assert_se(symlink("static-instance@.service", p) >= 0);

        assert_se(unit_file_get_state(UNIT_FILE_SYSTEM, root, "static-instance@.service", &state) >= 0 && state == UNIT_FILE_DISABLED);
        assert_se(unit_file_get_state(UNIT_FILE_SYSTEM, root, "static-instance@foo.service", &state) >= 0 && state == UNIT_FILE_STATIC);
}