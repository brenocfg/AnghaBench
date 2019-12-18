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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int NORMAL_WRITE_TH_NUM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  map_writer ; 
 int /*<<< orphan*/  normal_writer ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
	pthread_t map_write_tid;
	pthread_t normal_write_tid[NORMAL_WRITE_TH_NUM];
	int i = 0;

	if (argc != 3) {
		(void) printf("usage: %s <normal write file name>"
		    "<map write file name>\n", argv[0]);
		exit(1);
	}

	for (i = 0; i < NORMAL_WRITE_TH_NUM; i++) {
		if (pthread_create(&normal_write_tid[i], NULL, normal_writer,
		    argv[1])) {
			err(1, "pthread_create normal_writer failed.");
		}
	}

	if (pthread_create(&map_write_tid, NULL, map_writer, argv[2])) {
		err(1, "pthread_create map_writer failed.");
	}

	/* NOTREACHED */
	pthread_join(map_write_tid, NULL);
	return (0);
}