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
 int EINVAL ; 
 int EPERM ; 
 int MAP_ANONYMOUS ; 
 char* MAP_FAILED ; 
 int MAP_PRIVATE ; 
 size_t PAGE_ALIGN (size_t) ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  PR_SET_MM ; 
 int /*<<< orphan*/  PR_SET_MM_ARG_END ; 
 int /*<<< orphan*/  PR_SET_MM_ARG_START ; 
 int /*<<< orphan*/  PR_SET_NAME ; 
 size_t TASK_COMM_LEN ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  is_main_thread () ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_debug_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memzero (char*,size_t) ; 
 char* mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (char*,size_t) ; 
 scalar_t__ prctl (int /*<<< orphan*/ ,char const*,...) ; 
 char* program_invocation_name ; 
 int saved_argc ; 
 char** saved_argv ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

int rename_process(const char name[]) {
        static size_t mm_size = 0;
        static char *mm = NULL;
        bool truncated = false;
        size_t l;

        /* This is a like a poor man's setproctitle(). It changes the comm field, argv[0], and also the glibc's
         * internally used name of the process. For the first one a limit of 16 chars applies; to the second one in
         * many cases one of 10 (i.e. length of "/sbin/init") — however if we have CAP_SYS_RESOURCES it is unbounded;
         * to the third one 7 (i.e. the length of "systemd". If you pass a longer string it will likely be
         * truncated.
         *
         * Returns 0 if a name was set but truncated, > 0 if it was set but not truncated. */

        if (isempty(name))
                return -EINVAL; /* let's not confuse users unnecessarily with an empty name */

        if (!is_main_thread())
                return -EPERM; /* Let's not allow setting the process name from other threads than the main one, as we
                                * cache things without locking, and we make assumptions that PR_SET_NAME sets the
                                * process name that isn't correct on any other threads */

        l = strlen(name);

        /* First step, change the comm field. The main thread's comm is identical to the process comm. This means we
         * can use PR_SET_NAME, which sets the thread name for the calling thread. */
        if (prctl(PR_SET_NAME, name) < 0)
                log_debug_errno(errno, "PR_SET_NAME failed: %m");
        if (l >= TASK_COMM_LEN) /* Linux userspace process names can be 15 chars at max */
                truncated = true;

        /* Second step, change glibc's ID of the process name. */
        if (program_invocation_name) {
                size_t k;

                k = strlen(program_invocation_name);
                strncpy(program_invocation_name, name, k);
                if (l > k)
                        truncated = true;
        }

        /* Third step, completely replace the argv[] array the kernel maintains for us. This requires privileges, but
         * has the advantage that the argv[] array is exactly what we want it to be, and not filled up with zeros at
         * the end. This is the best option for changing /proc/self/cmdline. */

        /* Let's not bother with this if we don't have euid == 0. Strictly speaking we should check for the
         * CAP_SYS_RESOURCE capability which is independent of the euid. In our own code the capability generally is
         * present only for euid == 0, hence let's use this as quick bypass check, to avoid calling mmap() if
         * PR_SET_MM_ARG_{START,END} fails with EPERM later on anyway. After all geteuid() is dead cheap to call, but
         * mmap() is not. */
        if (geteuid() != 0)
                log_debug("Skipping PR_SET_MM, as we don't have privileges.");
        else if (mm_size < l+1) {
                size_t nn_size;
                char *nn;

                nn_size = PAGE_ALIGN(l+1);
                nn = mmap(NULL, nn_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
                if (nn == MAP_FAILED) {
                        log_debug_errno(errno, "mmap() failed: %m");
                        goto use_saved_argv;
                }

                strncpy(nn, name, nn_size);

                /* Now, let's tell the kernel about this new memory */
                if (prctl(PR_SET_MM, PR_SET_MM_ARG_START, (unsigned long) nn, 0, 0) < 0) {
                        /* HACK: prctl() API is kind of dumb on this point.  The existing end address may already be
                         * below the desired start address, in which case the kernel may have kicked this back due
                         * to a range-check failure (see linux/kernel/sys.c:validate_prctl_map() to see this in
                         * action).  The proper solution would be to have a prctl() API that could set both start+end
                         * simultaneously, or at least let us query the existing address to anticipate this condition
                         * and respond accordingly.  For now, we can only guess at the cause of this failure and try
                         * a workaround--which will briefly expand the arg space to something potentially huge before
                         * resizing it to what we want. */
                        log_debug_errno(errno, "PR_SET_MM_ARG_START failed, attempting PR_SET_MM_ARG_END hack: %m");

                        if (prctl(PR_SET_MM, PR_SET_MM_ARG_END, (unsigned long) nn + l + 1, 0, 0) < 0) {
                                log_debug_errno(errno, "PR_SET_MM_ARG_END hack failed, proceeding without: %m");
                                (void) munmap(nn, nn_size);
                                goto use_saved_argv;
                        }

                        if (prctl(PR_SET_MM, PR_SET_MM_ARG_START, (unsigned long) nn, 0, 0) < 0) {
                                log_debug_errno(errno, "PR_SET_MM_ARG_START still failed, proceeding without: %m");
                                goto use_saved_argv;
                        }
                } else {
                        /* And update the end pointer to the new end, too. If this fails, we don't really know what
                         * to do, it's pretty unlikely that we can rollback, hence we'll just accept the failure,
                         * and continue. */
                        if (prctl(PR_SET_MM, PR_SET_MM_ARG_END, (unsigned long) nn + l + 1, 0, 0) < 0)
                                log_debug_errno(errno, "PR_SET_MM_ARG_END failed, proceeding without: %m");
                }

                if (mm)
                        (void) munmap(mm, mm_size);

                mm = nn;
                mm_size = nn_size;
        } else {
                strncpy(mm, name, mm_size);

                /* Update the end pointer, continuing regardless of any failure. */
                if (prctl(PR_SET_MM, PR_SET_MM_ARG_END, (unsigned long) mm + l + 1, 0, 0) < 0)
                        log_debug_errno(errno, "PR_SET_MM_ARG_END failed, proceeding without: %m");
        }

use_saved_argv:
        /* Fourth step: in all cases we'll also update the original argv[], so that our own code gets it right too if
         * it still looks here */

        if (saved_argc > 0) {
                int i;

                if (saved_argv[0]) {
                        size_t k;

                        k = strlen(saved_argv[0]);
                        strncpy(saved_argv[0], name, k);
                        if (l > k)
                                truncated = true;
                }

                for (i = 1; i < saved_argc; i++) {
                        if (!saved_argv[i])
                                break;

                        memzero(saved_argv[i], strlen(saved_argv[i]));
                }
        }

        return !truncated;
}