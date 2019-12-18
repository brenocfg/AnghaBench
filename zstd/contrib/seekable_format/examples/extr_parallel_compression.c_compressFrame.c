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
struct job {size_t dstSize; int done; int /*<<< orphan*/  compressionLevel; int /*<<< orphan*/  srcSize; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; int /*<<< orphan*/  checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  XXH64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compress (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ZSTD_getErrorName (size_t) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void compressFrame(void* opaque)
{
    struct job* job = opaque;

    job->checksum = XXH64(job->src, job->srcSize, 0);

    size_t ret = ZSTD_compress(job->dst, job->dstSize, job->src, job->srcSize, job->compressionLevel);
    if (ZSTD_isError(ret)) {
        fprintf(stderr, "ZSTD_compress() error : %s \n", ZSTD_getErrorName(ret));
        exit(20);
    }

    job->dstSize = ret;
    job->done = 1;
}