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
struct context {int automatic_integer_property; int automatic_string_property; int something; int /*<<< orphan*/  fds; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int EXIT_SUCCESS ; 
 int PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int client (struct context*) ; 
 int /*<<< orphan*/  free (int) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct context*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  server ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strdup (char*) ; 

int main(int argc, char *argv[]) {
        struct context c = {};
        pthread_t s;
        void *p;
        int r, q;

        c.automatic_integer_property = 4711;
        assert_se(c.automatic_string_property = strdup("dudeldu"));

        assert_se(socketpair(AF_UNIX, SOCK_STREAM, 0, c.fds) >= 0);

        r = pthread_create(&s, NULL, server, &c);
        if (r != 0)
                return -r;

        r = client(&c);

        q = pthread_join(s, &p);
        if (q != 0)
                return -q;

        if (r < 0)
                return r;

        if (PTR_TO_INT(p) < 0)
                return PTR_TO_INT(p);

        free(c.something);
        free(c.automatic_string_property);

        return EXIT_SUCCESS;
}