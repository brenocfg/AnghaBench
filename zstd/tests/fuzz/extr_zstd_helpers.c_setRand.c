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
typedef  int /*<<< orphan*/  ZSTD_cParameter ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 unsigned int FUZZ_dataProducer_uint32Range (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const) ; 

__attribute__((used)) static void setRand(ZSTD_CCtx *cctx, ZSTD_cParameter param, unsigned min,
                    unsigned max, FUZZ_dataProducer_t *producer) {
    unsigned const value = FUZZ_dataProducer_uint32Range(producer, min, max);
    set(cctx, param, value);
}