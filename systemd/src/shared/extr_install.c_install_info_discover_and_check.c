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
typedef  int /*<<< orphan*/  LookupPaths ;
typedef  int /*<<< orphan*/  InstallContext ;

/* Variables and functions */
 int install_info_discover (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t*) ; 
 int install_info_may_process (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static int install_info_discover_and_check(
                        UnitFileScope scope,
                        InstallContext *c,
                        const LookupPaths *paths,
                        const char *name,
                        SearchFlags flags,
                        UnitFileInstallInfo **ret,
                        UnitFileChange **changes,
                        size_t *n_changes) {

        int r;

        r = install_info_discover(scope, c, paths, name, flags, ret, changes, n_changes);
        if (r < 0)
                return r;

        return install_info_may_process(ret ? *ret : NULL, paths, changes, n_changes);
}