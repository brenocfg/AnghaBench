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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(char **argv){
  fprintf(stderr, "\n");
  fprintf(stderr, "Usage %s ?OPTIONS? DATABASE\n", argv[0]);
  fprintf(stderr, "\n");
  fprintf(stderr, "Options are:\n");
  fprintf(stderr, "  -sql SQL   (analyze SQL statements passed as argument)\n");
  fprintf(stderr, "  -file FILE (read SQL statements from file FILE)\n");
  fprintf(stderr, "  -verbose LEVEL (integer verbosity level. default 1)\n");
  fprintf(stderr, "  -sample PERCENT (percent of db to sample. default 100)\n");
  exit(-1);
}