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
struct context {int client_negotiate_unix_fds; int server_negotiate_unix_fds; int client_anonymous_auth; int server_anonymous_auth; int /*<<< orphan*/  fds; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int client (struct context*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct context*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  server ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zero (struct context) ; 

__attribute__((used)) static int test_one(bool client_negotiate_unix_fds, bool server_negotiate_unix_fds,
                    bool client_anonymous_auth, bool server_anonymous_auth) {

        struct context c;
        pthread_t s;
        void *p;
        int r, q;

        zero(c);

        assert_se(socketpair(AF_UNIX, SOCK_STREAM, 0, c.fds) >= 0);

        c.client_negotiate_unix_fds = client_negotiate_unix_fds;
        c.server_negotiate_unix_fds = server_negotiate_unix_fds;
        c.client_anonymous_auth = client_anonymous_auth;
        c.server_anonymous_auth = server_anonymous_auth;

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

        return 0;
}