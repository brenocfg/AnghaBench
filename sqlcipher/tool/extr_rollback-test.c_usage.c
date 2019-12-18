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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(char *argv0){
  fprintf(stderr,
    "Usage: %s new [-utf8] [-utf16le] [-utf16be] [-pagesize=N] DATABASE\n"
    "       %s check DATABASE\n"
    "       %s crash [-wal] DATABASE\n",
    argv0, argv0, argv0
  );
  exit(1);
}