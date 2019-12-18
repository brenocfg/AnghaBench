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
typedef  int /*<<< orphan*/  uint16_t ;
struct instance {int log_level; int stats_interval; size_t mbuf_chunk_size; void* pid_filename; void* stats_addr; int /*<<< orphan*/  stats_port; void* conf_filename; void* log_filename; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_ERROR ; 
 int NC_MBUF_MAX_SIZE ; 
 int NC_MBUF_MIN_SIZE ; 
 int /*<<< orphan*/  NC_OK ; 
 int daemonize ; 
 int describe_stats ; 
 int getopt_long (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_stderr (char*,...) ; 
 int /*<<< orphan*/  long_options ; 
 int nc_atoi (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nc_valid_port (int) ; 
 void* optarg ; 
 scalar_t__ opterr ; 
 int optopt ; 
 int /*<<< orphan*/  short_options ; 
 int show_help ; 
 int show_version ; 
 int /*<<< orphan*/  strlen (void*) ; 
 int test_conf ; 

__attribute__((used)) static rstatus_t
nc_get_options(int argc, char **argv, struct instance *nci)
{
    int c, value;

    opterr = 0;

    for (;;) {
        c = getopt_long(argc, argv, short_options, long_options, NULL);
        if (c == -1) {
            /* no more options */
            break;
        }

        switch (c) {
        case 'h':
            show_version = 1;
            show_help = 1;
            break;

        case 'V':
            show_version = 1;
            break;

        case 't':
            test_conf = 1;
            break;

        case 'd':
            daemonize = 1;
            break;

        case 'D':
            describe_stats = 1;
            show_version = 1;
            break;

        case 'v':
            value = nc_atoi(optarg, strlen(optarg));
            if (value < 0) {
                log_stderr("nutcracker: option -v requires a number");
                return NC_ERROR;
            }
            nci->log_level = value;
            break;

        case 'o':
            nci->log_filename = optarg;
            break;

        case 'c':
            nci->conf_filename = optarg;
            break;

        case 's':
            value = nc_atoi(optarg, strlen(optarg));
            if (value < 0) {
                log_stderr("nutcracker: option -s requires a number");
                return NC_ERROR;
            }
            if (!nc_valid_port(value)) {
                log_stderr("nutcracker: option -s value %d is not a valid "
                           "port", value);
                return NC_ERROR;
            }

            nci->stats_port = (uint16_t)value;
            break;

        case 'i':
            value = nc_atoi(optarg, strlen(optarg));
            if (value < 0) {
                log_stderr("nutcracker: option -i requires a number");
                return NC_ERROR;
            }

            nci->stats_interval = value;
            break;

        case 'a':
            nci->stats_addr = optarg;
            break;

        case 'p':
            nci->pid_filename = optarg;
            break;

        case 'm':
            value = nc_atoi(optarg, strlen(optarg));
            if (value <= 0) {
                log_stderr("nutcracker: option -m requires a non-zero number");
                return NC_ERROR;
            }

            if (value < NC_MBUF_MIN_SIZE || value > NC_MBUF_MAX_SIZE) {
                log_stderr("nutcracker: mbuf chunk size must be between %zu and"
                           " %zu bytes", NC_MBUF_MIN_SIZE, NC_MBUF_MAX_SIZE);
                return NC_ERROR;
            }

            nci->mbuf_chunk_size = (size_t)value;
            break;

        case '?':
            switch (optopt) {
            case 'o':
            case 'c':
            case 'p':
                log_stderr("nutcracker: option -%c requires a file name",
                           optopt);
                break;

            case 'm':
            case 'v':
            case 's':
            case 'i':
                log_stderr("nutcracker: option -%c requires a number", optopt);
                break;

            case 'a':
                log_stderr("nutcracker: option -%c requires a string", optopt);
                break;

            default:
                log_stderr("nutcracker: invalid option -- '%c'", optopt);
                break;
            }
            return NC_ERROR;

        default:
            log_stderr("nutcracker: invalid option -- '%c'", optopt);
            return NC_ERROR;

        }
    }

    return NC_OK;
}