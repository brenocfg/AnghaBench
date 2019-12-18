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
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ catalog_dirs ; 
 int catalog_update (char const*,int /*<<< orphan*/ *,char const* const*) ; 
 char const* const* no_catalog_dirs ; 

__attribute__((used)) static void test_catalog_update(const char *database) {
        int r;

        /* Test what happens if there are no files. */
        r = catalog_update(database, NULL, NULL);
        assert_se(r == 0);

        /* Test what happens if there are no files in the directory. */
        r = catalog_update(database, NULL, no_catalog_dirs);
        assert_se(r == 0);

        /* Make sure that we at least have some files loaded or the
         * catalog_list below will fail. */
        r = catalog_update(database, NULL, (const char * const *) catalog_dirs);
        assert_se(r == 0);
}