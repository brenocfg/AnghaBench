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
  fprintf(stderr, "Usage: %s DATABASE\n"
                  "   or: %s DATABASE FTS3TABLE ARGS...\n", argv0, argv0);
  fprintf(stderr,
    "ARGS:\n"
    "  big-segments [--top N]                    show the largest segments\n"
    "  doclist BLOCKID OFFSET SIZE [--raw]       Decode a doclist\n"
    "  schema                                    FTS table schema\n"
    "  segdir                                    directory of segments\n"
    "  segment BLOCKID [--raw]                   content of a segment\n"
    "  segment-stats                             info on segment sizes\n"
    "  stat                                      the %%_stat table\n"
    "  vocabulary [--top N]                      document vocabulary\n"
  );
  exit(1);
}