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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sbuf ;
typedef  struct in_addr const FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  assert (struct in_addr const*) ; 
 int /*<<< orphan*/  fputc (char,struct in_addr const*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,struct in_addr const*) ; 
 int /*<<< orphan*/  inet_ntop (int /*<<< orphan*/ ,struct in_addr const*,char*,int) ; 

size_t serialize_in_addrs(FILE *f,
                          const struct in_addr *addresses,
                          size_t size,
                          bool with_leading_space,
                          bool (*predicate)(const struct in_addr *addr)) {
        size_t count;
        size_t i;

        assert(f);
        assert(addresses);

        count = 0;

        for (i = 0; i < size; i++) {
                char sbuf[INET_ADDRSTRLEN];

                if (predicate && !predicate(&addresses[i]))
                        continue;
                if (with_leading_space)
                        fputc(' ', f);
                else
                        with_leading_space = true;
                fputs(inet_ntop(AF_INET, &addresses[i], sbuf, sizeof(sbuf)), f);
                count++;
        }

        return count;
}