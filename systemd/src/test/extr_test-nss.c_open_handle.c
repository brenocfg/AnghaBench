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
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlerror () ; 
 void* dlopen (char const*,int) ; 
 int /*<<< orphan*/  log_error (char*,char const*,int /*<<< orphan*/ ) ; 
 char* strjoina (char const*,char const*,char const*,...) ; 

__attribute__((used)) static void* open_handle(const char* dir, const char* module, int flags) {
        const char *path = NULL;
        void *handle;

        if (dir)
                path = strjoina(dir, "/libnss_", module, ".so.2");
        if (!path || access(path, F_OK) < 0)
                path = strjoina("libnss_", module, ".so.2");

        handle = dlopen(path, flags);
        if (!handle)
                log_error("Failed to load module %s: %s", module, dlerror());
        return handle;
}