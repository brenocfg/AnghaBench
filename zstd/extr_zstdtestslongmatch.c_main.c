#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  params ;
typedef  int /*<<< orphan*/  match ;
struct TYPE_7__ {int windowLog; int chainLog; int hashLog; int searchLog; int minMatch; int targetLength; int /*<<< orphan*/  strategy; } ;
struct TYPE_8__ {TYPE_1__ cParams; } ;
typedef  TYPE_2__ ZSTD_parameters ;
struct TYPE_9__ {char* member_0; int member_1; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_3__ ZSTD_outBuffer ;
typedef  int /*<<< orphan*/  ZSTD_CStream ;
typedef  int U64 ;

/* Variables and functions */
 int ZSTD_compressBound (int) ; 
 int /*<<< orphan*/ * ZSTD_createCStream () ; 
 int /*<<< orphan*/  ZSTD_fast ; 
 size_t ZSTD_initCStream_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 scalar_t__ compress (int /*<<< orphan*/ *,TYPE_3__,char*,size_t const) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 size_t const rand () ; 

int main(int argc, const char** argv)
{
  ZSTD_CStream* ctx;
  ZSTD_parameters params;
  size_t rc;
  unsigned windowLog;
  (void)argc;
  (void)argv;
  /* Create stream */
  ctx = ZSTD_createCStream();
  if (!ctx) { return 1; }
  /* Set parameters */
  memset(&params, 0, sizeof(params));
  params.cParams.windowLog = 18;
  params.cParams.chainLog = 13;
  params.cParams.hashLog = 14;
  params.cParams.searchLog = 1;
  params.cParams.minMatch = 7;
  params.cParams.targetLength = 16;
  params.cParams.strategy = ZSTD_fast;
  windowLog = params.cParams.windowLog;
  /* Initialize stream */
  rc = ZSTD_initCStream_advanced(ctx, NULL, 0, params, 0);
  if (ZSTD_isError(rc)) { return 2; }
  {
    U64 compressed = 0;
    const U64 toCompress = ((U64)1) << 33;
    const size_t size = 1 << windowLog;
    size_t pos = 0;
    char *srcBuffer = (char*) malloc(1 << windowLog);
    char *dstBuffer = (char*) malloc(ZSTD_compressBound(1 << windowLog));
    ZSTD_outBuffer out = { dstBuffer, ZSTD_compressBound(1 << windowLog), 0 };
    const char match[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t randomData = (1 << windowLog) - 2*sizeof(match);
    size_t i;
    printf("\n ===   Long Match Test   === \n");
    printf("Creating random data to produce long matches \n");
    for (i = 0; i < sizeof(match); ++i) {
      srcBuffer[i] = match[i];
    }
    for (i = 0; i < randomData; ++i) {
      srcBuffer[sizeof(match) + i] = (char)(rand() & 0xFF);
    }
    for (i = 0; i < sizeof(match); ++i) {
      srcBuffer[sizeof(match) + randomData + i] = match[i];
    }
    printf("Compressing, trying to generate a segfault \n");
    if (compress(ctx, out, srcBuffer, size)) {
      return 1;
    }
    compressed += size;
    while (compressed < toCompress) {
      const size_t block = rand() % (size - pos + 1);
      if (pos == size) { pos = 0; }
      if (compress(ctx, out, srcBuffer + pos, block)) {
        return 1;
      }
      pos += block;
      compressed += block;
    }
    printf("Compression completed successfully (no error triggered)\n");
    free(srcBuffer);
    free(dstBuffer);
  }
  return 0;
}