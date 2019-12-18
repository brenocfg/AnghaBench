#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_2__ {scalar_t__ rto_sweep; scalar_t__ rto_benchmark; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int SPA_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  dprintf_setup (int*,char**) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb ; 
 char* gdb_tmpl ; 
 unsigned int getpid () ; 
 int /*<<< orphan*/  kernel_fini () ; 
 int /*<<< orphan*/  kernel_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mprotect (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_options (int,char**) ; 
 int rand () ; 
 int* rand_data ; 
 TYPE_1__ rto_opts ; 
 int /*<<< orphan*/  run_raidz_benchmark () ; 
 int run_sweep () ; 
 int run_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sig_handler ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 scalar_t__ umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (int*,int) ; 

int
main(int argc, char **argv)
{
	size_t i;
	struct sigaction action;
	int err = 0;

	/* init gdb string early */
	(void) sprintf(gdb, gdb_tmpl, getpid());

	action.sa_handler = sig_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	if (sigaction(SIGSEGV, &action, NULL) < 0) {
		ERR("raidz_test: cannot catch SIGSEGV: %s.\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	(void) setvbuf(stdout, NULL, _IOLBF, 0);

	dprintf_setup(&argc, argv);

	process_options(argc, argv);

	kernel_init(FREAD);

	/* setup random data because rand() is not reentrant */
	rand_data = (int *)umem_alloc(SPA_MAXBLOCKSIZE, UMEM_NOFAIL);
	srand((unsigned)time(NULL) * getpid());
	for (i = 0; i < SPA_MAXBLOCKSIZE / sizeof (int); i++)
		rand_data[i] = rand();

	mprotect(rand_data, SPA_MAXBLOCKSIZE, PROT_READ);

	if (rto_opts.rto_benchmark) {
		run_raidz_benchmark();
	} else if (rto_opts.rto_sweep) {
		err = run_sweep();
	} else {
		err = run_test(NULL);
	}

	umem_free(rand_data, SPA_MAXBLOCKSIZE);
	kernel_fini();

	return (err);
}