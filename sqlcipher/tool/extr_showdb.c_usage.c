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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void usage(const char *argv0){
  fprintf(stderr, "Usage %s ?--uri? FILENAME ?args...?\n\n", argv0);
  fprintf(stderr,
    "switches:\n"
    "    --raw           Read db file directly, bypassing SQLite VFS\n"
    "args:\n"
    "    dbheader        Show database header\n"
    "    pgidx           Index of how each page is used\n"
    "    ptrmap          Show all PTRMAP page content\n"
    "    NNN..MMM        Show hex of pages NNN through MMM\n"
    "    NNN..end        Show hex of pages NNN through end of file\n"
    "    NNNb            Decode btree page NNN\n"
    "    NNNbc           Decode btree page NNN and show content\n"
    "    NNNbm           Decode btree page NNN and show a layout map\n"
    "    NNNbdCCC        Decode cell CCC on btree page NNN\n"
    "    NNNt            Decode freelist trunk page NNN\n"
    "    NNNtd           Show leaf freelist pages on the decode\n"
    "    NNNtr           Recursively decode freelist starting at NNN\n"
  );
}