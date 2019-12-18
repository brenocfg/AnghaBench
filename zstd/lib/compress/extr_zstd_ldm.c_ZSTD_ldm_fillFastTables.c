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
struct TYPE_6__ {int strategy; } ;
struct TYPE_7__ {TYPE_1__ cParams; } ;
typedef  TYPE_2__ ZSTD_matchState_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
#define  ZSTD_btlazy2 136 
#define  ZSTD_btopt 135 
#define  ZSTD_btultra 134 
#define  ZSTD_btultra2 133 
#define  ZSTD_dfast 132 
 int /*<<< orphan*/  ZSTD_dtlm_fast ; 
#define  ZSTD_fast 131 
 int /*<<< orphan*/  ZSTD_fillDoubleHashTable (TYPE_2__*,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_fillHashTable (TYPE_2__*,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 
#define  ZSTD_greedy 130 
#define  ZSTD_lazy 129 
#define  ZSTD_lazy2 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_ldm_fillFastTables(ZSTD_matchState_t* ms,
                                      void const* end)
{
    const BYTE* const iend = (const BYTE*)end;

    switch(ms->cParams.strategy)
    {
    case ZSTD_fast:
        ZSTD_fillHashTable(ms, iend, ZSTD_dtlm_fast);
        break;

    case ZSTD_dfast:
        ZSTD_fillDoubleHashTable(ms, iend, ZSTD_dtlm_fast);
        break;

    case ZSTD_greedy:
    case ZSTD_lazy:
    case ZSTD_lazy2:
    case ZSTD_btlazy2:
    case ZSTD_btopt:
    case ZSTD_btultra:
    case ZSTD_btultra2:
        break;
    default:
        assert(0);  /* not possible : not a valid strategy id */
    }

    return 0;
}