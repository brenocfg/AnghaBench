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
 int EXEC_FAILED ; 
 int MSG_PROGS_LEN ; 
 int TASK_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int runTask (char*,char**,int*) ; 

__attribute__((used)) static int xmessage(char *argv[], int *exit_status)
{
	static const char * const MSG_PROGS[] = {"gmessage", "gxmessage",
	                                         "kmessage", "xmessage"};
	static int PREV_MSG_INDEX = -1;
	#define MSG_PROGS_LEN (sizeof(MSG_PROGS) / sizeof(MSG_PROGS[0]))

	char *prog = NULL;
	int ret;

	/* Save some fork()'ing and attempt to use last program if possible. */
	if (PREV_MSG_INDEX >= 0) {
		assert(PREV_MSG_INDEX < MSG_PROGS_LEN);

		prog = argv[0] = (char *)MSG_PROGS[PREV_MSG_INDEX];
		ret = runTask(prog, argv, exit_status);
	} else {
		/* Otherwise, try running each xmessage alternative until one works or
		 * we run out of options. */
		size_t i;
		for (i = 0; i < MSG_PROGS_LEN; ++i) {
			prog = argv[0] = (char *)MSG_PROGS[i];
			ret = runTask(prog, argv, exit_status);
			if (ret != EXEC_FAILED) break;
		}

		if (ret == TASK_SUCCESS) PREV_MSG_INDEX = i;
	}

	return ret;
}