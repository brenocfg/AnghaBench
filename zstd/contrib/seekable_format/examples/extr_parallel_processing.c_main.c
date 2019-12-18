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
 int atoi (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  sumFile_orDie (char const* const,int const) ; 

int main(int argc, const char** argv)
{
    const char* const exeName = argv[0];

    if (argc!=3) {
        fprintf(stderr, "wrong arguments\n");
        fprintf(stderr, "usage:\n");
        fprintf(stderr, "%s FILE NB_THREADS\n", exeName);
        return 1;
    }

    {
        const char* const inFilename = argv[1];
        int const nbThreads = atoi(argv[2]);
        sumFile_orDie(inFilename, nbThreads);
    }

    return 0;
}