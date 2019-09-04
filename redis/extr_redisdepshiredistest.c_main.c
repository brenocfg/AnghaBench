#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* path; } ;
struct TYPE_3__ {char* host; int port; } ;
struct config {int /*<<< orphan*/  type; TYPE_2__ unix_sock; TYPE_1__ tcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_FD ; 
 int /*<<< orphan*/  CONN_TCP ; 
 int /*<<< orphan*/  CONN_UNIX ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fails ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  test_append_formatted_commands (struct config) ; 
 int /*<<< orphan*/  test_blocking_connection (struct config) ; 
 int /*<<< orphan*/  test_blocking_connection_errors () ; 
 int /*<<< orphan*/  test_blocking_connection_timeouts (struct config) ; 
 int /*<<< orphan*/  test_blocking_io_errors (struct config) ; 
 int /*<<< orphan*/  test_format_commands () ; 
 int /*<<< orphan*/  test_free_null () ; 
 int /*<<< orphan*/  test_invalid_timeout_errors (struct config) ; 
 int /*<<< orphan*/  test_reply_reader () ; 
 int /*<<< orphan*/  test_throughput (struct config) ; 

int main(int argc, char **argv) {
    struct config cfg = {
        .tcp = {
            .host = "127.0.0.1",
            .port = 6379
        },
        .unix_sock = {
            .path = "/tmp/redis.sock"
        }
    };
    int throughput = 1;
    int test_inherit_fd = 1;

    /* Ignore broken pipe signal (for I/O error tests). */
    signal(SIGPIPE, SIG_IGN);

    /* Parse command line options. */
    argv++; argc--;
    while (argc) {
        if (argc >= 2 && !strcmp(argv[0],"-h")) {
            argv++; argc--;
            cfg.tcp.host = argv[0];
        } else if (argc >= 2 && !strcmp(argv[0],"-p")) {
            argv++; argc--;
            cfg.tcp.port = atoi(argv[0]);
        } else if (argc >= 2 && !strcmp(argv[0],"-s")) {
            argv++; argc--;
            cfg.unix_sock.path = argv[0];
        } else if (argc >= 1 && !strcmp(argv[0],"--skip-throughput")) {
            throughput = 0;
        } else if (argc >= 1 && !strcmp(argv[0],"--skip-inherit-fd")) {
            test_inherit_fd = 0;
        } else {
            fprintf(stderr, "Invalid argument: %s\n", argv[0]);
            exit(1);
        }
        argv++; argc--;
    }

    test_format_commands();
    test_reply_reader();
    test_blocking_connection_errors();
    test_free_null();

    printf("\nTesting against TCP connection (%s:%d):\n", cfg.tcp.host, cfg.tcp.port);
    cfg.type = CONN_TCP;
    test_blocking_connection(cfg);
    test_blocking_connection_timeouts(cfg);
    test_blocking_io_errors(cfg);
    test_invalid_timeout_errors(cfg);
    test_append_formatted_commands(cfg);
    if (throughput) test_throughput(cfg);

    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix_sock.path);
    cfg.type = CONN_UNIX;
    test_blocking_connection(cfg);
    test_blocking_connection_timeouts(cfg);
    test_blocking_io_errors(cfg);
    if (throughput) test_throughput(cfg);

    if (test_inherit_fd) {
        printf("\nTesting against inherited fd (%s):\n", cfg.unix_sock.path);
        cfg.type = CONN_FD;
        test_blocking_connection(cfg);
    }


    if (fails) {
        printf("*** %d TESTS FAILED ***\n", fails);
        return 1;
    }

    printf("ALL TESTS PASSED\n");
    return 0;
}