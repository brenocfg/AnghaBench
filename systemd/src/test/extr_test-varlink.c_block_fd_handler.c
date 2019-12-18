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
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ fd_nonblock (int,int) ; 
 int read (int,char*,int) ; 
 scalar_t__ sd_event_source_set_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int block_fd_handler(sd_event_source *s, int fd, uint32_t revents, void *userdata) {
        char c;

        assert_se(fd_nonblock(fd, false) >= 0);

        assert_se(read(fd, &c, sizeof(c)) == sizeof(c));
        /* When a character is written to this pipe we'll block until the pipe is closed. */

        assert_se(read(fd, &c, sizeof(c)) == 0);

        assert_se(fd_nonblock(fd, true) >= 0);

        assert_se(sd_event_source_set_enabled(s, SD_EVENT_OFF) >= 0);

        return 0;
}