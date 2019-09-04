#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  (* func_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;
struct TYPE_8__ {char* kernelenv; scalar_t__ cons; int /*<<< orphan*/  userboot; scalar_t__ bootvolume; } ;
struct TYPE_7__ {int /*<<< orphan*/  c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCAL ; 
 int /*<<< orphan*/  RTLD_LOCAL ; 
 scalar_t__ STDIN_FILENO ; 
 scalar_t__ STDOUT_FILENO ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  USERBOOT_VERSION_3 ; 
 int /*<<< orphan*/  addenv (char*) ; 
 int /*<<< orphan*/  altcons_open (scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cb ; 
 int /*<<< orphan*/  cfmakeraw (TYPE_1__*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 TYPE_5__ config ; 
 scalar_t__ consin_fd ; 
 scalar_t__ consout_fd ; 
 scalar_t__* disk_fd ; 
 int /*<<< orphan*/  disk_open (scalar_t__) ; 
 char* dlerror () ; 
 void* dlopen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dlsym (void*,char*) ; 
 int /*<<< orphan*/  exec_done ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * host_base ; 
 int ndisks ; 
 TYPE_1__ oldterm ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcgetattr (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  tcsetattr (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ term ; 
 int /*<<< orphan*/  vcpu_rip ; 

uint64_t
fbsd_load(void)
{
	void *h;
	int i;
	func_t func;

	host_base = NULL;
	consin_fd = STDIN_FILENO;
	consout_fd = STDOUT_FILENO;

	if (config.cons) {
		altcons_open(config.cons);
	}

	if (config.bootvolume) {
		disk_open(config.bootvolume);
	} else {
		fprintf(stderr, "fbsd: no boot volume\n");
		exit(-1);
	}

	if (config.kernelenv) {
		addenv(config.kernelenv);
	}

	//host_base = optarg h

	tcgetattr(consout_fd, &term);
	oldterm = term;
	cfmakeraw(&term);
	term.c_cflag |= CLOCAL;
	
	tcsetattr(consout_fd, TCSAFLUSH, &term);

	h = dlopen(config.userboot, RTLD_LOCAL);
	if (!h) {
		fprintf(stderr, "%s\n", dlerror());
		exit(-1);
	}

	func = (func_t) dlsym(h, "loader_main");
	if (!func) {
		fprintf(stderr, "%s\n", dlerror());
		exit(-1);
	}

	addenv("smbios.bios.vendor=BHYVE");
	addenv("boot_serial=1");

	if (!setjmp(exec_done)) {
		func(&cb, NULL, USERBOOT_VERSION_3, ndisks);
	}

	for (i = 0; i < ndisks; i++) {
		close(disk_fd[i]);
	}

	if (config.cons) {
		assert(consin_fd == consout_fd);
		close(consin_fd);
	}

	return vcpu_rip;
}