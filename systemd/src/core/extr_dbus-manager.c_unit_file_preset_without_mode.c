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
typedef  int /*<<< orphan*/  UnitFileFlags ;
typedef  int /*<<< orphan*/  UnitFileChange ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT_FILE_PRESET_FULL ; 
 int unit_file_preset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*) ; 

__attribute__((used)) static int unit_file_preset_without_mode(UnitFileScope scope, UnitFileFlags flags, const char *root_dir, char **files, UnitFileChange **changes, size_t *n_changes) {
        return unit_file_preset(scope, flags, root_dir, files, UNIT_FILE_PRESET_FULL, changes, n_changes);
}