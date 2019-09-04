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
 char* strrchr (char*,char) ; 

__attribute__((used)) static int parseClusterNodeAddress(char *addr, char **ip_ptr, int *port_ptr,
                                   int *bus_port_ptr)
{
    char *c = strrchr(addr, '@');
    if (c != NULL) {
        *c = '\0';
        if (bus_port_ptr != NULL)
            *bus_port_ptr = atoi(c + 1);
    }
    c = strrchr(addr, ':');
    if (c != NULL) {
        *c = '\0';
        *ip_ptr = addr;
        *port_ptr = atoi(++c);
    } else return 0;
    return 1;
}