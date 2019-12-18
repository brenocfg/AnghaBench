#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_9__ {int* bytes; } ;
typedef  TYPE_1__ sd_id128_t ;
struct TYPE_10__ {char* rbuffer; int rbuffer_size; int can_fds; TYPE_1__ server_id; scalar_t__ anonymous_auth; int /*<<< orphan*/  auth; scalar_t__ accept_fd; } ;
typedef  TYPE_2__ sd_bus ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_AUTH_ANONYMOUS ; 
 int /*<<< orphan*/  BUS_AUTH_EXTERNAL ; 
 int EINVAL ; 
 int EPERM ; 
 int STRLEN (char*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int bus_start_running (TYPE_2__*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 char* memmem (char*,int,char*,int) ; 
 char* memmem_safe (char*,int,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 int /*<<< orphan*/  sd_id128_equal (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  sd_id128_is_null (TYPE_1__) ; 
 int unhexchar (char) ; 

__attribute__((used)) static int bus_socket_auth_verify_client(sd_bus *b) {
        char *d, *e, *f, *start;
        sd_id128_t peer;
        int r;

        assert(b);

        /*
         * We expect three response lines:
         *   "DATA\r\n"
         *   "OK <server-id>\r\n"
         *   "AGREE_UNIX_FD\r\n"        (optional)
         */

        d = memmem_safe(b->rbuffer, b->rbuffer_size, "\r\n", 2);
        if (!d)
                return 0;

        e = memmem(d + 2, b->rbuffer_size - (d - (char*) b->rbuffer) - 2, "\r\n", 2);
        if (!e)
                return 0;

        if (b->accept_fd) {
                f = memmem(e + 2, b->rbuffer_size - (e - (char*) b->rbuffer) - 2, "\r\n", 2);
                if (!f)
                        return 0;

                start = f + 2;
        } else {
                f = NULL;
                start = e + 2;
        }

        /* Nice! We got all the lines we need. First check the DATA line. */

        if (d - (char*) b->rbuffer == 4) {
                if (memcmp(b->rbuffer, "DATA", 4))
                        return -EPERM;
        } else if (d - (char*) b->rbuffer == 3 + 32) {
                /*
                 * Old versions of the server-side implementation of `sd-bus` replied with "OK <id>" to
                 * "AUTH" requests from a client, even if the "AUTH" line did not contain inlined
                 * arguments. Therefore, we also accept "OK <id>" here, even though it is technically the
                 * wrong reply. We ignore the "<id>" parameter, though, since it has no real value.
                 */
                if (memcmp(b->rbuffer, "OK ", 3))
                        return -EPERM;
        } else
                return -EPERM;

        /* Now check the OK line. */

        if (e - d != 2 + 3 + 32)
                return -EPERM;

        if (memcmp(d + 2, "OK ", 3))
                return -EPERM;

        b->auth = b->anonymous_auth ? BUS_AUTH_ANONYMOUS : BUS_AUTH_EXTERNAL;

        for (unsigned i = 0; i < 32; i += 2) {
                int x, y;

                x = unhexchar(d[2 + 3 + i]);
                y = unhexchar(d[2 + 3 + i + 1]);

                if (x < 0 || y < 0)
                        return -EINVAL;

                peer.bytes[i/2] = ((uint8_t) x << 4 | (uint8_t) y);
        }

        if (!sd_id128_is_null(b->server_id) &&
            !sd_id128_equal(b->server_id, peer))
                return -EPERM;

        b->server_id = peer;

        /* And possibly check the third line, too */

        if (f)
                b->can_fds =
                        (f - e == STRLEN("\r\nAGREE_UNIX_FD")) &&
                        memcmp(e + 2, "AGREE_UNIX_FD",
                               STRLEN("AGREE_UNIX_FD")) == 0;

        b->rbuffer_size -= (start - (char*) b->rbuffer);
        memmove(b->rbuffer, start, b->rbuffer_size);

        r = bus_start_running(b);
        if (r < 0)
                return r;

        return 1;
}