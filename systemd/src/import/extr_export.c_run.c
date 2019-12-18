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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int export_main (int,char**) ; 
 int /*<<< orphan*/  ignore_signals (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_open () ; 
 int /*<<< orphan*/  log_parse_environment () ; 
 int parse_argv (int,char**) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        setlocale(LC_ALL, "");
        log_parse_environment();
        log_open();

        r = parse_argv(argc, argv);
        if (r <= 0)
                return r;

        (void) ignore_signals(SIGPIPE, -1);

        return export_main(argc, argv);
}