#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; scalar_t__ opt_type; int /*<<< orphan*/ ** value; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 TYPE_2__* long_extras ; 
 TYPE_1__* long_options ; 
 size_t nargs ; 
 int /*<<< orphan*/ * optarg ; 
 int /*<<< orphan*/  print_help () ; 
 scalar_t__ required_option ; 
 int /*<<< orphan*/  short_options ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int parse_args(int argc, char** argv) {
    int option_index = 0;
    int c;

    while (1) {
        c = getopt_long(argc, argv, short_options, long_options, &option_index);
        if (c == -1)
            break;

        int found = 0;
        for (size_t i = 0; i < nargs; ++i) {
            if (c == long_extras[i].id && long_extras[i].value != NULL) {
                *long_extras[i].value = optarg;
                found = 1;
                break;
            }
        }
        if (found)
            continue;

        switch (c) {
            case 'h':
            case '?':
            default:
                print_help();
                return 1;
        }
    }

    int bad = 0;
    for (size_t i = 0; i < nargs; ++i) {
        if (long_extras[i].opt_type != required_option)
            continue;
        if (long_extras[i].value == NULL)
            continue;
        if (*long_extras[i].value != NULL)
            continue;
        fprintf(
            stderr,
            "--%s is a required argument but is not set\n",
            long_options[i].name);
        bad = 1;
    }
    if (bad) {
        fprintf(stderr, "\n");
        print_help();
        return 1;
    }

    return 0;
}