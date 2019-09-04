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
struct TYPE_3__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_CStream ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
 size_t ZSTD_initCStream_usingCDict_advanced (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__ const,int /*<<< orphan*/ ) ; 

size_t ZSTD_initCStream_usingCDict(ZSTD_CStream* zcs, const ZSTD_CDict* cdict)
{
    ZSTD_frameParameters const fParams = { 0 /* contentSizeFlag */, 0 /* checksum */, 0 /* hideDictID */ };
    DEBUGLOG(4, "ZSTD_initCStream_usingCDict");
    return ZSTD_initCStream_usingCDict_advanced(zcs, cdict, fParams, ZSTD_CONTENTSIZE_UNKNOWN);  /* note : will check that cdict != NULL */
}