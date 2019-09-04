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
 char* DEFAULT_SERVER_PATH ; 
 char* getenv (char*) ; 

__attribute__((used)) static const char *
get_server_path(void) {
    const char *server_path = getenv("SCRCPY_SERVER_PATH");
    if (!server_path) {
        server_path = DEFAULT_SERVER_PATH;
    }
    return server_path;
}