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
typedef  int /*<<< orphan*/  UnitFileInstallInfo ;
struct TYPE_3__ {int /*<<< orphan*/  root_dir; } ;
typedef  TYPE_1__ LookupPaths ;
typedef  char const InstallContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int install_info_add (char const*,char const*,char const*,int,int /*<<< orphan*/ **) ; 
 scalar_t__ path_is_absolute (char const*) ; 
 char* prefix_roota (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int install_info_add_auto(
                InstallContext *c,
                const LookupPaths *paths,
                const char *name_or_path,
                UnitFileInstallInfo **ret) {

        assert(c);
        assert(name_or_path);

        if (path_is_absolute(name_or_path)) {
                const char *pp;

                pp = prefix_roota(paths->root_dir, name_or_path);

                return install_info_add(c, NULL, pp, false, ret);
        } else
                return install_info_add(c, name_or_path, NULL, false, ret);
}