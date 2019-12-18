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
 int atoi (char*) ; 
 int /*<<< orphan*/  parseClusterNodeAddress (char*,char**,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int getClusterHostFromCmdArgs(int argc, char **argv,
                                     char **ip_ptr, int *port_ptr) {
    int port = 0;
    char *ip = NULL;
    if (argc == 1) {
        char *addr = argv[0];
        if (!parseClusterNodeAddress(addr, &ip, &port, NULL)) return 0;
    } else {
        ip = argv[0];
        port = atoi(argv[1]);
    }
    if (!ip || !port) return 0;
    else {
        *ip_ptr = ip;
        *port_ptr = port;
    }
    return 1;
}