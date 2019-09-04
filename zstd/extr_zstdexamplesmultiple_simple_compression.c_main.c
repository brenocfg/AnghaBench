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
typedef  int /*<<< orphan*/  resources ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*) ; 
 int /*<<< orphan*/  compressFile_orDie (int /*<<< orphan*/  const,char const* const,char*) ; 
 int /*<<< orphan*/  createResources_orDie (int,char const**,char**,size_t*) ; 
 int /*<<< orphan*/  freeResources (int /*<<< orphan*/  const,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const* const,size_t const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t strlen (char const* const) ; 

int main(int argc, const char** argv)
{
    const char* const exeName = argv[0];

    if (argc<2) {
        printf("wrong arguments\n");
        printf("usage:\n");
        printf("%s FILE(s)\n", exeName);
        return 1;
    }

    /* memory allocation for outFilename and resources */
    char* outFilename;
    size_t outFilenameBufferLen;
    resources const ress = createResources_orDie(argc, argv, &outFilename, &outFilenameBufferLen);

    /* compress files with shared context, input and output buffers */
    int argNb;
    for (argNb = 1; argNb < argc; argNb++) {
        const char* const inFilename = argv[argNb];
        size_t const inFilenameLen = strlen(inFilename);
        CHECK(inFilenameLen + 5 <= outFilenameBufferLen, "File name too long!");
        memcpy(outFilename, inFilename, inFilenameLen);
        memcpy(outFilename+inFilenameLen, ".zst", 5);
        compressFile_orDie(ress, inFilename, outFilename);
    }

    /* free memory */
    freeResources(ress,outFilename);

    printf("compressed %i files \n", argc-1);

    return 0;
}