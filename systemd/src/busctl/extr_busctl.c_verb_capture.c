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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arg_snaplen ; 
 int /*<<< orphan*/  bus_pcap_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fflush_and_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  message_pcap ; 
 int monitor (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int verb_capture(int argc, char **argv, void *userdata) {
        int r;

        if (isatty(fileno(stdout)) > 0)
                return log_error_errno(SYNTHETIC_ERRNO(EINVAL),
                                       "Refusing to write message data to console, please redirect output to a file.");

        bus_pcap_header(arg_snaplen, stdout);

        r = monitor(argc, argv, message_pcap);
        if (r < 0)
                return r;

        r = fflush_and_check(stdout);
        if (r < 0)
                return log_error_errno(r, "Couldn't write capture file: %m");

        return r;
}