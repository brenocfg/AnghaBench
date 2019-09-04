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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
struct args {int fullscreen; int help; int no_control; int no_display; char* record_filename; int show_touches; int always_on_top; int version; scalar_t__ record_format; void* serial; int /*<<< orphan*/  port; int /*<<< orphan*/  max_size; void* crop; int /*<<< orphan*/  bit_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGE (char*,...) ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 scalar_t__ guess_record_format (char*) ; 
#define  no_argument 129 
 void* optarg ; 
 int optind ; 
 int /*<<< orphan*/  parse_bit_rate (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_max_size (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_port (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_record_format (void*,scalar_t__*) ; 
#define  required_argument 128 

__attribute__((used)) static bool
parse_args(struct args *args, int argc, char *argv[]) {
    static const struct option long_options[] = {
        {"always-on-top", no_argument,       NULL, 'T'},
        {"bit-rate",      required_argument, NULL, 'b'},
        {"crop",          required_argument, NULL, 'c'},
        {"fullscreen",    no_argument,       NULL, 'f'},
        {"help",          no_argument,       NULL, 'h'},
        {"max-size",      required_argument, NULL, 'm'},
        {"no-control",    no_argument,       NULL, 'n'},
        {"no-display",    no_argument,       NULL, 'N'},
        {"port",          required_argument, NULL, 'p'},
        {"record",        required_argument, NULL, 'r'},
        {"record-format", required_argument, NULL, 'f'},
        {"serial",        required_argument, NULL, 's'},
        {"show-touches",  no_argument,       NULL, 't'},
        {"version",       no_argument,       NULL, 'v'},
        {NULL,            0,                 NULL, 0  },
    };
    int c;
    while ((c = getopt_long(argc, argv, "b:c:fF:hm:nNp:r:s:tTv", long_options,
                            NULL)) != -1) {
        switch (c) {
            case 'b':
                if (!parse_bit_rate(optarg, &args->bit_rate)) {
                    return false;
                }
                break;
            case 'c':
                args->crop = optarg;
                break;
            case 'f':
                args->fullscreen = true;
                break;
            case 'F':
                if (!parse_record_format(optarg, &args->record_format)) {
                    return false;
                }
                break;
            case 'h':
                args->help = true;
                break;
            case 'm':
                if (!parse_max_size(optarg, &args->max_size)) {
                    return false;
                }
                break;
            case 'n':
                args->no_control = true;
                break;
            case 'N':
                args->no_display = true;
                break;
            case 'p':
                if (!parse_port(optarg, &args->port)) {
                    return false;
                }
                break;
            case 'r':
                args->record_filename = optarg;
                break;
            case 's':
                args->serial = optarg;
                break;
            case 't':
                args->show_touches = true;
                break;
            case 'T':
                args->always_on_top = true;
                break;
            case 'v':
                args->version = true;
                break;
            default:
                // getopt prints the error message on stderr
                return false;
        }
    }

    if (args->no_display && !args->record_filename) {
        LOGE("-N/--no-display requires screen recording (-r/--record)");
        return false;
    }

    if (args->no_display && args->fullscreen) {
        LOGE("-f/--fullscreen-window is incompatible with -N/--no-display");
        return false;
    }

    int index = optind;
    if (index < argc) {
        LOGE("Unexpected additional argument: %s", argv[index]);
        return false;
    }

    if (args->record_format && !args->record_filename) {
        LOGE("Record format specified without recording");
        return false;
    }

    if (args->record_filename && !args->record_format) {
        args->record_format = guess_record_format(args->record_filename);
        if (!args->record_format) {
            LOGE("No format specified for \"%s\" (try with -F mkv)",
                 args->record_filename);
            return false;
        }
    }

    return true;
}