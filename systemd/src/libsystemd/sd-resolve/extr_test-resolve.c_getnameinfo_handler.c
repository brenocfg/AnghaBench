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
typedef  int /*<<< orphan*/  sd_resolve_query ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 char* strna (char const*) ; 

__attribute__((used)) static int getnameinfo_handler(sd_resolve_query *q, int ret, const char *host, const char *serv, void *userdata) {
        assert_se(q);

        if (ret != 0) {
                log_error("getnameinfo error: %s %i", gai_strerror(ret), ret);
                return 0;
        }

        printf("Host: %s — Serv: %s\n", strna(host), strna(serv));
        return 0;
}