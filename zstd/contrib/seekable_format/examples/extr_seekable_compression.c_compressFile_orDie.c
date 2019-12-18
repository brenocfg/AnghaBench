#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_seekable_CStream ;
struct TYPE_6__ {void* const member_0; size_t const member_1; int /*<<< orphan*/  pos; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_7__ {void* const member_0; size_t member_1; scalar_t__ pos; scalar_t__ size; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ZSTD_CStreamInSize () ; 
 size_t ZSTD_CStreamOutSize () ; 
 char* ZSTD_getErrorName (size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 size_t ZSTD_seekable_compressStream (int /*<<< orphan*/ * const,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/ * ZSTD_seekable_createCStream () ; 
 size_t ZSTD_seekable_endStream (int /*<<< orphan*/ * const,TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_seekable_freeCStream (int /*<<< orphan*/ * const) ; 
 size_t ZSTD_seekable_initCStream (int /*<<< orphan*/ * const,int,int,unsigned int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose_orDie (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen_orDie (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread_orDie (void* const,size_t,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  free (void* const) ; 
 int /*<<< orphan*/  fwrite_orDie (void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ * const) ; 
 void* malloc_orDie (size_t const) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void compressFile_orDie(const char* fname, const char* outName, int cLevel, unsigned frameSize)
{
    FILE* const fin  = fopen_orDie(fname, "rb");
    FILE* const fout = fopen_orDie(outName, "wb");
    size_t const buffInSize = ZSTD_CStreamInSize();    /* can always read one full block */
    void*  const buffIn  = malloc_orDie(buffInSize);
    size_t const buffOutSize = ZSTD_CStreamOutSize();  /* can always flush a full block */
    void*  const buffOut = malloc_orDie(buffOutSize);

    ZSTD_seekable_CStream* const cstream = ZSTD_seekable_createCStream();
    if (cstream==NULL) { fprintf(stderr, "ZSTD_seekable_createCStream() error \n"); exit(10); }
    size_t const initResult = ZSTD_seekable_initCStream(cstream, cLevel, 1, frameSize);
    if (ZSTD_isError(initResult)) { fprintf(stderr, "ZSTD_seekable_initCStream() error : %s \n", ZSTD_getErrorName(initResult)); exit(11); }

    size_t read, toRead = buffInSize;
    while( (read = fread_orDie(buffIn, toRead, fin)) ) {
        ZSTD_inBuffer input = { buffIn, read, 0 };
        while (input.pos < input.size) {
            ZSTD_outBuffer output = { buffOut, buffOutSize, 0 };
            toRead = ZSTD_seekable_compressStream(cstream, &output , &input);   /* toRead is guaranteed to be <= ZSTD_CStreamInSize() */
            if (ZSTD_isError(toRead)) { fprintf(stderr, "ZSTD_seekable_compressStream() error : %s \n", ZSTD_getErrorName(toRead)); exit(12); }
            if (toRead > buffInSize) toRead = buffInSize;   /* Safely handle case when `buffInSize` is manually changed to a value < ZSTD_CStreamInSize()*/
            fwrite_orDie(buffOut, output.pos, fout);
        }
    }

    while (1) {
        ZSTD_outBuffer output = { buffOut, buffOutSize, 0 };
        size_t const remainingToFlush = ZSTD_seekable_endStream(cstream, &output);   /* close stream */
        if (ZSTD_isError(remainingToFlush)) { fprintf(stderr, "ZSTD_seekable_endStream() error : %s \n", ZSTD_getErrorName(remainingToFlush)); exit(13); }
        fwrite_orDie(buffOut, output.pos, fout);
        if (!remainingToFlush) break;
    }

    ZSTD_seekable_freeCStream(cstream);
    fclose_orDie(fout);
    fclose_orDie(fin);
    free(buffIn);
    free(buffOut);
}