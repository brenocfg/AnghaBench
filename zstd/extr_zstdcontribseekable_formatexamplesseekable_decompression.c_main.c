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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  atoll (char const*) ; 
 int /*<<< orphan*/  decompressFile_orDie (char const* const,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, const char** argv)
{
    const char* const exeName = argv[0];

    if (argc!=4) {
        fprintf(stderr, "wrong arguments\n");
        fprintf(stderr, "usage:\n");
        fprintf(stderr, "%s FILE START END\n", exeName);
        return 1;
    }

    {
        const char* const inFilename = argv[1];
        off_t const startOffset = atoll(argv[2]);
        off_t const endOffset = atoll(argv[3]);
        decompressFile_orDie(inFilename, startOffset, endOffset);
    }

    return 0;
}