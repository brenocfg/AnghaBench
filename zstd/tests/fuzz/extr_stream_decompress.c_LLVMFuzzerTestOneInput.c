#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ZSTD_outBuffer ;
struct TYPE_4__ {scalar_t__ pos; scalar_t__ size; } ;
typedef  TYPE_1__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FUZZ_ZASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * FUZZ_dataProducer_create (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  FUZZ_dataProducer_free (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_reserveDataPrefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_DCtx_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTD_createDStream () ; 
 size_t ZSTD_decompressStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ZSTD_freeDStream (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/  ZSTD_reset_session_only ; 
 int /*<<< orphan*/ * buf ; 
 int /*<<< orphan*/ * dstream ; 
 int /*<<< orphan*/  kBufSize ; 
 TYPE_1__ makeInBuffer (int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  makeOutBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{
    /* Give a random portion of src data to the producer, to use for
    parameter generation. The rest will be used for (de)compression */
    FUZZ_dataProducer_t *producer = FUZZ_dataProducer_create(src, size);
    size = FUZZ_dataProducer_reserveDataPrefix(producer);

    /* Allocate all buffers and contexts if not already allocated */
    if (!buf) {
      buf = malloc(kBufSize);
        FUZZ_ASSERT(buf);
      }

    if (!dstream) {
        dstream = ZSTD_createDStream();
        FUZZ_ASSERT(dstream);
    } else {
        FUZZ_ZASSERT(ZSTD_DCtx_reset(dstream, ZSTD_reset_session_only));
    }

    while (size > 0) {
        ZSTD_inBuffer in = makeInBuffer(&src, &size, producer);
        while (in.pos != in.size) {
            ZSTD_outBuffer out = makeOutBuffer(producer);
            size_t const rc = ZSTD_decompressStream(dstream, &out, &in);
            if (ZSTD_isError(rc)) goto error;
        }
    }

error:
#ifndef STATEFUL_FUZZING
    ZSTD_freeDStream(dstream); dstream = NULL;
#endif
    FUZZ_dataProducer_free(producer);
    return 0;
}