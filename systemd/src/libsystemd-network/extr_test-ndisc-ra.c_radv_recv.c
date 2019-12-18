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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_radv ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  sd_event ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int* advertisement ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int /*<<< orphan*/ ,unsigned char**,int) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sd_radv_get_event (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_radv_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_fd ; 
 int test_stopped ; 

__attribute__((used)) static int radv_recv(sd_event_source *s, int fd, uint32_t revents, void *userdata) {
        sd_radv *ra = userdata;
        unsigned char buf[168];
        size_t i;

        assert_se(read(test_fd[0], &buf, sizeof(buf)) == sizeof(buf));

        /* router lifetime must be zero when test is stopped */
        if (test_stopped) {
                advertisement[6] = 0x00;
                advertisement[7] = 0x00;
        }

        printf ("Received Router Advertisement with lifetime %u\n",
                (advertisement[6] << 8) + advertisement[7]);

        /* test only up to buf size, rest is not yet implemented */
        for (i = 0; i < sizeof(buf); i++) {
                if (!(i % 8))
                        printf("%3zd: ", i);

                printf("0x%02x", buf[i]);

                assert_se(buf[i] == advertisement[i]);

                if ((i + 1) % 8)
                        printf(", ");
                else
                        printf("\n");
        }

        if (test_stopped) {
                sd_event *e;

                e = sd_radv_get_event(ra);
                sd_event_exit(e, 0);

                return 0;
        }

        assert_se(sd_radv_stop(ra) >= 0);
        test_stopped = true;

        return 0;
}