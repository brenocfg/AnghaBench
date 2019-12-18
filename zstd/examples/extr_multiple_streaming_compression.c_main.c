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
 int /*<<< orphan*/  compressFile_orDie (int /*<<< orphan*/  const,char const* const,void*) ; 
 int /*<<< orphan*/  createResources_orDie (int const) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  freeResources (int /*<<< orphan*/  const) ; 
 void* malloc_orDie (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strcat (void*,char const* const) ; 
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

    int const cLevel = 7;
    resources const ress = createResources_orDie(cLevel);
    void* ofnBuffer = NULL;
    size_t ofnbSize = 0;

    int argNb;
    for (argNb = 1; argNb < argc; argNb++) {
        const char* const ifn = argv[argNb];
        size_t const ifnSize = strlen(ifn);
        size_t const ofnSize = ifnSize + 5;
        if (ofnbSize <= ofnSize) {
            ofnbSize = ofnSize + 16;
            free(ofnBuffer);
            ofnBuffer = malloc_orDie(ofnbSize);
        }
        memset(ofnBuffer, 0, ofnSize);
        strcat(ofnBuffer, ifn);
        strcat(ofnBuffer, ".zst");
        compressFile_orDie(ress, ifn, ofnBuffer);
    }

    freeResources(ress);
    free(ofnBuffer);

    printf("compressed %i files \n", argc-1);

    return 0;
}