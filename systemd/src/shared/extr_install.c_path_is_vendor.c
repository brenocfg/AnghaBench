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
typedef  char LookupPaths ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTEM_DATA_UNIT_PATH ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int path_equal (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ path_startswith (char const*,char*) ; 
 char* skip_root (char const*,char const*) ; 

__attribute__((used)) static int path_is_vendor(const LookupPaths *p, const char *path) {
        const char *rpath;

        assert(p);
        assert(path);

        rpath = skip_root(p, path);
        if (!rpath)
                return 0;

        if (path_startswith(rpath, "/usr"))
                return true;

#if HAVE_SPLIT_USR
        if (path_startswith(rpath, "/lib"))
                return true;
#endif

        return path_equal(rpath, SYSTEM_DATA_UNIT_PATH);
}