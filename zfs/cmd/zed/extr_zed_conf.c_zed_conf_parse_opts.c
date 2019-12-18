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
struct zed_conf {int do_verbose; int do_force; int do_foreground; int do_memlock; int do_zero; int /*<<< orphan*/  state_file; int /*<<< orphan*/  path; int /*<<< orphan*/  pid_file; int /*<<< orphan*/  zedlet_dir; int /*<<< orphan*/  conf_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  _zed_conf_display_help (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _zed_conf_display_license () ; 
 int /*<<< orphan*/  _zed_conf_display_version () ; 
 int /*<<< orphan*/  _zed_conf_parse_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char) ; 
 int getopt (int,char**,char const* const) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ opterr ; 
 char optopt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zed_log_die (char*) ; 

void
zed_conf_parse_opts(struct zed_conf *zcp, int argc, char **argv)
{
	const char * const opts = ":hLVc:d:p:P:s:vfFMZ";
	int opt;

	if (!zcp || !argv || !argv[0])
		zed_log_die("Failed to parse options: Internal error");

	opterr = 0;			/* suppress default getopt err msgs */

	while ((opt = getopt(argc, argv, opts)) != -1) {
		switch (opt) {
		case 'h':
			_zed_conf_display_help(argv[0], EXIT_SUCCESS);
			break;
		case 'L':
			_zed_conf_display_license();
			break;
		case 'V':
			_zed_conf_display_version();
			break;
		case 'c':
			_zed_conf_parse_path(&zcp->conf_file, optarg);
			break;
		case 'd':
			_zed_conf_parse_path(&zcp->zedlet_dir, optarg);
			break;
		case 'p':
			_zed_conf_parse_path(&zcp->pid_file, optarg);
			break;
		case 'P':
			_zed_conf_parse_path(&zcp->path, optarg);
			break;
		case 's':
			_zed_conf_parse_path(&zcp->state_file, optarg);
			break;
		case 'v':
			zcp->do_verbose = 1;
			break;
		case 'f':
			zcp->do_force = 1;
			break;
		case 'F':
			zcp->do_foreground = 1;
			break;
		case 'M':
			zcp->do_memlock = 1;
			break;
		case 'Z':
			zcp->do_zero = 1;
			break;
		case '?':
		default:
			if (optopt == '?')
				_zed_conf_display_help(argv[0], EXIT_SUCCESS);

			fprintf(stderr, "%s: %s '-%c'\n\n", argv[0],
			    "Invalid option", optopt);
			_zed_conf_display_help(argv[0], EXIT_FAILURE);
			break;
		}
	}
}