#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* const member_0; size_t const member_1; scalar_t__ pos; scalar_t__ size; int /*<<< orphan*/  member_2; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {scalar_t__ pos; scalar_t__ size; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_DStream ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESSED ; 
 int /*<<< orphan*/  COMPRESSED_SIZE ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 scalar_t__ EXPECTED ; 
 size_t ZSTD_DStreamOutSize () ; 
 int /*<<< orphan*/ * ZSTD_createDStream () ; 
 size_t ZSTD_decompressStream (int /*<<< orphan*/ * const,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ZSTD_freeDStream (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t const) ; 
 size_t ZSTD_initDStream (int /*<<< orphan*/ * const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  free (char* const) ; 
 char* malloc (size_t const) ; 
 scalar_t__ memcmp (char* const,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int testStreamingAPI(void)
{
    int error_code = 0;
    size_t const outBuffSize = ZSTD_DStreamOutSize();
    char* const outBuff = malloc(outBuffSize);
    ZSTD_DStream* const stream = ZSTD_createDStream();
    ZSTD_inBuffer input = { COMPRESSED, COMPRESSED_SIZE, 0 };
    size_t outputPos = 0;
    int needsInit = 1;

    if (outBuff == NULL) {
        DISPLAY("ERROR: Could not allocate memory\n");
        return 1;
    }
    if (stream == NULL) {
        DISPLAY("ERROR: Could not create dstream\n");
        free(outBuff);
        return 1;
    }

    while (1) {
        ZSTD_outBuffer output = {outBuff, outBuffSize, 0};
        if (needsInit) {
            size_t const ret = ZSTD_initDStream(stream);
            if (ZSTD_isError(ret)) {
                DISPLAY("ERROR: ZSTD_initDStream: %s\n", ZSTD_getErrorName(ret));
                error_code = 1;
                break;
        }   }

        {   size_t const ret = ZSTD_decompressStream(stream, &output, &input);
            if (ZSTD_isError(ret)) {
                DISPLAY("ERROR: ZSTD_decompressStream: %s\n", ZSTD_getErrorName(ret));
                error_code = 1;
                break;
            }

            if (ret == 0) {
                needsInit = 1;
        }   }

        if (memcmp(outBuff, EXPECTED + outputPos, output.pos) != 0) {
            DISPLAY("ERROR: Wrong decoded output produced\n");
            error_code = 1;
            break;
        }
        outputPos += output.pos;
        if (input.pos == input.size && output.pos < output.size) {
            break;
        }
    }

    free(outBuff);
    ZSTD_freeDStream(stream);
    if (error_code == 0) DISPLAY("Streaming API OK\n");
    return error_code;
}