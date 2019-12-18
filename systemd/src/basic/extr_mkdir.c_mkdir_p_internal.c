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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int (* mkdir_func_t ) (char const*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ is_dir (char const*,int) ; 
 int mkdir (char const*,int /*<<< orphan*/ ) ; 
 int mkdir_parents_internal (char const*,char const*,int /*<<< orphan*/ ,int (*) (char const*,int /*<<< orphan*/ )) ; 

int mkdir_p_internal(const char *prefix, const char *path, mode_t mode, mkdir_func_t _mkdir) {
        int r;

        /* Like mkdir -p */

        assert(_mkdir != mkdir);

        r = mkdir_parents_internal(prefix, path, mode, _mkdir);
        if (r < 0)
                return r;

        r = _mkdir(path, mode);
        if (r < 0 && (r != -EEXIST || is_dir(path, true) <= 0))
                return r;

        return 0;
}