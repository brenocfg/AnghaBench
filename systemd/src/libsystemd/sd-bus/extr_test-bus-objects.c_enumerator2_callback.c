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
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (char**) ; 
 scalar_t__ object_path_startswith (char*,char const*) ; 
 char** strv_new (char*,char*,char*) ; 

__attribute__((used)) static int enumerator2_callback(sd_bus *bus, const char *path, void *userdata, char ***nodes, sd_bus_error *error) {

        if (object_path_startswith("/value/a", path))
                assert_se(*nodes = strv_new("/value/a/x", "/value/a/y", "/value/a/z"));

        return 1;
}