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
struct scrcpy_options {int show_touches; int always_on_top; int no_control; int no_display; int /*<<< orphan*/  fullscreen; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  max_size; int /*<<< orphan*/  record_format; int /*<<< orphan*/ * record_filename; int /*<<< orphan*/  port; int /*<<< orphan*/ * crop; int /*<<< orphan*/ * serial; } ;
struct args {int help; int version; int show_touches; int always_on_top; int no_control; int no_display; int /*<<< orphan*/  fullscreen; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  max_size; int /*<<< orphan*/  record_format; int /*<<< orphan*/ * record_filename; int /*<<< orphan*/  port; int /*<<< orphan*/ * crop; int /*<<< orphan*/ * serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BIT_RATE ; 
 int /*<<< orphan*/  DEFAULT_LOCAL_PORT ; 
 int /*<<< orphan*/  DEFAULT_MAX_SIZE ; 
 int /*<<< orphan*/  avformat_network_deinit () ; 
 scalar_t__ avformat_network_init () ; 
 int /*<<< orphan*/  parse_args (struct args*,int,char**) ; 
 int /*<<< orphan*/  print_version () ; 
 scalar_t__ scrcpy (struct scrcpy_options*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int
main(int argc, char *argv[]) {
#ifdef __WINDOWS__
    // disable buffering, we want logs immediately
    // even line buffering (setvbuf() with mode _IOLBF) is not sufficient
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
#endif
    struct args args = {
        .serial = NULL,
        .crop = NULL,
        .record_filename = NULL,
        .record_format = 0,
        .help = false,
        .version = false,
        .show_touches = false,
        .port = DEFAULT_LOCAL_PORT,
        .max_size = DEFAULT_MAX_SIZE,
        .bit_rate = DEFAULT_BIT_RATE,
        .always_on_top = false,
        .no_control = false,
        .no_display = false,
    };
    if (!parse_args(&args, argc, argv)) {
        return 1;
    }

    if (args.help) {
        usage(argv[0]);
        return 0;
    }

    if (args.version) {
        print_version();
        return 0;
    }

#ifdef SCRCPY_LAVF_REQUIRES_REGISTER_ALL
    av_register_all();
#endif

    if (avformat_network_init()) {
        return 1;
    }

#ifdef BUILD_DEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif

    struct scrcpy_options options = {
        .serial = args.serial,
        .crop = args.crop,
        .port = args.port,
        .record_filename = args.record_filename,
        .record_format = args.record_format,
        .max_size = args.max_size,
        .bit_rate = args.bit_rate,
        .show_touches = args.show_touches,
        .fullscreen = args.fullscreen,
        .always_on_top = args.always_on_top,
        .no_control = args.no_control,
        .no_display = args.no_display,
    };
    int res = scrcpy(&options) ? 0 : 1;

    avformat_network_deinit(); // ignore failure

#if defined (__WINDOWS__) && ! defined (WINDOWS_NOCONSOLE)
    if (res != 0) {
        fprintf(stderr, "Press any key to continue...\n");
        getchar();
    }
#endif
    return res;
}