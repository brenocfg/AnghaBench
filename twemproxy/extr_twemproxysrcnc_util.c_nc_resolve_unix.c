#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string {size_t len; int /*<<< orphan*/  data; } ;
struct sockaddr_un {char* sun_path; void* sun_family; } ;
struct TYPE_2__ {struct sockaddr_un un; } ;
struct sockinfo {int addrlen; void* family; TYPE_1__ addr; } ;

/* Variables and functions */
 void* AF_UNIX ; 
 size_t NC_UNIX_ADDRSTRLEN ; 
 int /*<<< orphan*/  nc_memcpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
nc_resolve_unix(struct string *name, struct sockinfo *si)
{
    struct sockaddr_un *un;

    if (name->len >= NC_UNIX_ADDRSTRLEN) {
        return -1;
    }

    un = &si->addr.un;

    un->sun_family = AF_UNIX;
    nc_memcpy(un->sun_path, name->data, name->len);
    un->sun_path[name->len] = '\0';

    si->family = AF_UNIX;
    si->addrlen = sizeof(*un);
    /* si->addr is an alias of un */

    return 0;
}