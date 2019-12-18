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
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  assert (size_t) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in6_addr const*,char*,int) ; 

void serialize_in6_addrs(FILE *f, const struct in6_addr *addresses, size_t size) {
        unsigned i;

        assert(f);
        assert(addresses);
        assert(size);

        for (i = 0; i < size; i++) {
                char buffer[INET6_ADDRSTRLEN];

                fputs(inet_ntop(AF_INET6, addresses+i, buffer, sizeof(buffer)), f);

                if (i < size - 1)
                        fputc(' ', f);
        }
}