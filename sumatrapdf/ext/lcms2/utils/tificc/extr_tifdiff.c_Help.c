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
 int SW ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static
void Help()
{
    fprintf(stderr, "Little cms TIFF compare utility. v1.0\n\n");

    fprintf(stderr, "usage: tiffdiff [flags] input.tif output.tif\n");

    fprintf(stderr, "\nflags:\n\n");


    fprintf(stderr, "%co<tiff>   - Output TIFF file\n", SW);
    fprintf(stderr, "%cg<CGATS>  - Output results in CGATS file\n", SW);

    fprintf(stderr, "\n");

    fprintf(stderr, "%cv - Verbose (show warnings)\n", SW);
    fprintf(stderr, "%ch - This help\n", SW);


    fflush(stderr);
    exit(0);
}