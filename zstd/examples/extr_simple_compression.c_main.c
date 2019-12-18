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
 int /*<<< orphan*/  compress_orDie (char const* const,char* const) ; 
 char* createOutFilename_orDie (char const* const) ; 
 int /*<<< orphan*/  free (char* const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, const char** argv)
{
    const char* const exeName = argv[0];

    if (argc!=2) {
        printf("wrong arguments\n");
        printf("usage:\n");
        printf("%s FILE\n", exeName);
        return 1;
    }

    const char* const inFilename = argv[1];

    char* const outFilename = createOutFilename_orDie(inFilename);
    compress_orDie(inFilename, outFilename);
    free(outFilename);
    return 0;
}