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

__attribute__((used)) static void usage(const char *argv0){
  fprintf(stderr, "Usage: %s FILENAME COMMAND ...\n", argv0);
  fprintf(stderr,
    "COMMANDs:\n"
    "   apply DB           Apply the changeset to database file DB\n"
    "   concat FILE2 OUT   Concatenate FILENAME and FILE2 into OUT\n"
    "   dump               Show the complete content of the changeset\n"
    "   invert OUT         Write an inverted changeset into file OUT\n"
    "   sql                Give a pseudo-SQL rendering of the changeset\n"
  );
  exit(1);
}