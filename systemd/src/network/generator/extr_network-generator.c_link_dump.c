#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* ifname; int /*<<< orphan*/  mac; } ;
typedef  TYPE_1__ Link ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int ETHER_ADDR_TO_STRING_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ether_addr_is_null (int /*<<< orphan*/ *) ; 
 char* ether_addr_to_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  fputs (char*,TYPE_1__*) ; 

void link_dump(Link *link, FILE *f) {
        char mac[ETHER_ADDR_TO_STRING_MAX];

        assert(link);
        assert(f);

        fputs("[Match]\n", f);

        if (!ether_addr_is_null(&link->mac))
                fprintf(f, "MACAddress=%s\n", ether_addr_to_string(&link->mac, mac));

        fprintf(f,
                "\n[Link]\n"
                "Name=%s\n",
                link->ifname);
}