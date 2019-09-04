#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t fBufferSize; size_t cBufferSize; int /*<<< orphan*/ * cctx; void* cBuffer; void* fBuffer; } ;
typedef  TYPE_1__ resources ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int /*<<< orphan*/ ,char*) ; 
 size_t ZSTD_compressBound (size_t) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 size_t fsize_orDie (char const* const) ; 
 void* malloc_orDie (size_t) ; 
 size_t strlen (char const* const) ; 

__attribute__((used)) static resources createResources_orDie(int argc, const char** argv, char **ofn, size_t* ofnBufferLen)
{
    size_t maxFilenameLength=0;
    size_t maxFileSize = 0;

    int argNb;
    for (argNb = 1; argNb < argc; argNb++) {
      const char* const filename = argv[argNb];
      size_t const filenameLength = strlen(filename);
      size_t const fileSize = fsize_orDie(filename);

      if (filenameLength > maxFilenameLength) maxFilenameLength = filenameLength;
      if (fileSize > maxFileSize) maxFileSize = fileSize;
    }

    resources ress;
    ress.fBufferSize = maxFileSize;
    ress.cBufferSize = ZSTD_compressBound(maxFileSize);

    *ofnBufferLen = maxFilenameLength + 5;
    *ofn = (char*)malloc_orDie(*ofnBufferLen);
    ress.fBuffer = malloc_orDie(ress.fBufferSize);
    ress.cBuffer = malloc_orDie(ress.cBufferSize);
    ress.cctx = ZSTD_createCCtx();
    CHECK(ress.cctx != NULL, "ZSTD_createCCtx() failed!");
    return ress;
}