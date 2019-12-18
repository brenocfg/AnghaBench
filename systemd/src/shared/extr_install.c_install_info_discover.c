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
typedef  int /*<<< orphan*/  UnitFileScope ;
typedef  int /*<<< orphan*/  UnitFileInstallInfo ;
typedef  int /*<<< orphan*/  UnitFileChange ;
typedef  int /*<<< orphan*/  SearchFlags ;
typedef  char LookupPaths ;
typedef  char const InstallContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int install_info_add_auto (char const*,char const*,char const*,int /*<<< orphan*/ **) ; 
 int install_info_traverse (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  unit_file_changes_add (int /*<<< orphan*/ **,size_t*,int,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int install_info_discover(
                UnitFileScope scope,
                InstallContext *c,
                const LookupPaths *paths,
                const char *name,
                SearchFlags flags,
                UnitFileInstallInfo **ret,
                UnitFileChange **changes,
                size_t *n_changes) {

        UnitFileInstallInfo *i;
        int r;

        assert(c);
        assert(paths);
        assert(name);

        r = install_info_add_auto(c, paths, name, &i);
        if (r >= 0)
                r = install_info_traverse(scope, c, paths, i, flags, ret);

        if (r < 0)
                unit_file_changes_add(changes, n_changes, r, name, NULL);
        return r;
}