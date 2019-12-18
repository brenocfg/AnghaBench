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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

void usage( char *name ) {
    fprintf( stderr,
             "Usage: %s [-n nm] [-m make] libs...\n"
             "nm   -- The command used to run nm on reactos objects\n"
             "make -- The command used to build reactos\n\n"
             "libs are import libraries (.a files) typically from\n"
             "dk/lib/nkm and dk/lib/w32\n",
             name );
}