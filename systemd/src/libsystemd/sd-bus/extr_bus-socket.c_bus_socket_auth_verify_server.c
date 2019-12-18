#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int rbuffer_size; int auth_rbegin; scalar_t__ auth; int can_fds; scalar_t__ rbuffer; int /*<<< orphan*/  accept_fd; } ;
typedef  TYPE_1__ sd_bus ;

/* Variables and functions */
 scalar_t__ BUS_AUTH_ANONYMOUS ; 
 scalar_t__ BUS_AUTH_EXTERNAL ; 
 int EIO ; 
 scalar_t__ _BUS_AUTH_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ bus_socket_auth_needs_write (TYPE_1__*) ; 
 int bus_socket_auth_write (TYPE_1__*,char*) ; 
 int bus_socket_auth_write_ok (TYPE_1__*) ; 
 int bus_start_running (TYPE_1__*) ; 
 scalar_t__ line_begins (char const*,size_t,char*) ; 
 scalar_t__ line_equals (char const*,size_t,char*) ; 
 char* memmem (char const*,int,char*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,char*,int) ; 
 size_t strlen (char*) ; 
 int verify_anonymous_token (TYPE_1__*,char const*,size_t) ; 
 int verify_external_token (TYPE_1__*,char const*,size_t) ; 

__attribute__((used)) static int bus_socket_auth_verify_server(sd_bus *b) {
        char *e;
        const char *line;
        size_t l;
        bool processed = false;
        int r;

        assert(b);

        if (b->rbuffer_size < 1)
                return 0;

        /* First char must be a NUL byte */
        if (*(char*) b->rbuffer != 0)
                return -EIO;

        if (b->rbuffer_size < 3)
                return 0;

        /* Begin with the first line */
        if (b->auth_rbegin <= 0)
                b->auth_rbegin = 1;

        for (;;) {
                /* Check if line is complete */
                line = (char*) b->rbuffer + b->auth_rbegin;
                e = memmem(line, b->rbuffer_size - b->auth_rbegin, "\r\n", 2);
                if (!e)
                        return processed;

                l = e - line;

                if (line_begins(line, l, "AUTH ANONYMOUS")) {

                        r = verify_anonymous_token(b,
                                                   line + strlen("AUTH ANONYMOUS"),
                                                   l - strlen("AUTH ANONYMOUS"));
                        if (r < 0)
                                return r;
                        if (r == 0)
                                r = bus_socket_auth_write(b, "REJECTED\r\n");
                        else {
                                b->auth = BUS_AUTH_ANONYMOUS;
                                if (l <= strlen("AUTH ANONYMOUS"))
                                        r = bus_socket_auth_write(b, "DATA\r\n");
                                else
                                        r = bus_socket_auth_write_ok(b);
                        }

                } else if (line_begins(line, l, "AUTH EXTERNAL")) {

                        r = verify_external_token(b,
                                                  line + strlen("AUTH EXTERNAL"),
                                                  l - strlen("AUTH EXTERNAL"));
                        if (r < 0)
                                return r;
                        if (r == 0)
                                r = bus_socket_auth_write(b, "REJECTED\r\n");
                        else {
                                b->auth = BUS_AUTH_EXTERNAL;
                                if (l <= strlen("AUTH EXTERNAL"))
                                        r = bus_socket_auth_write(b, "DATA\r\n");
                                else
                                        r = bus_socket_auth_write_ok(b);
                        }

                } else if (line_begins(line, l, "AUTH"))
                        r = bus_socket_auth_write(b, "REJECTED EXTERNAL ANONYMOUS\r\n");
                else if (line_equals(line, l, "CANCEL") ||
                         line_begins(line, l, "ERROR")) {

                        b->auth = _BUS_AUTH_INVALID;
                        r = bus_socket_auth_write(b, "REJECTED\r\n");

                } else if (line_equals(line, l, "BEGIN")) {

                        if (b->auth == _BUS_AUTH_INVALID)
                                r = bus_socket_auth_write(b, "ERROR\r\n");
                        else {
                                /* We can't leave from the auth phase
                                 * before we haven't written
                                 * everything queued, so let's check
                                 * that */

                                if (bus_socket_auth_needs_write(b))
                                        return 1;

                                b->rbuffer_size -= (e + 2 - (char*) b->rbuffer);
                                memmove(b->rbuffer, e + 2, b->rbuffer_size);
                                return bus_start_running(b);
                        }

                } else if (line_begins(line, l, "DATA")) {

                        if (b->auth == _BUS_AUTH_INVALID)
                                r = bus_socket_auth_write(b, "ERROR\r\n");
                        else {
                                if (b->auth == BUS_AUTH_ANONYMOUS)
                                        r = verify_anonymous_token(b, line + 4, l - 4);
                                else
                                        r = verify_external_token(b, line + 4, l - 4);

                                if (r < 0)
                                        return r;
                                if (r == 0) {
                                        b->auth = _BUS_AUTH_INVALID;
                                        r = bus_socket_auth_write(b, "REJECTED\r\n");
                                } else
                                        r = bus_socket_auth_write_ok(b);
                        }
                } else if (line_equals(line, l, "NEGOTIATE_UNIX_FD")) {
                        if (b->auth == _BUS_AUTH_INVALID || !b->accept_fd)
                                r = bus_socket_auth_write(b, "ERROR\r\n");
                        else {
                                b->can_fds = true;
                                r = bus_socket_auth_write(b, "AGREE_UNIX_FD\r\n");
                        }
                } else
                        r = bus_socket_auth_write(b, "ERROR\r\n");

                if (r < 0)
                        return r;

                b->auth_rbegin = e + 2 - (char*) b->rbuffer;

                processed = true;
        }
}