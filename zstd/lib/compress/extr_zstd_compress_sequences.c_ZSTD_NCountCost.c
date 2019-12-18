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
typedef  int /*<<< orphan*/  wksp ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  S16 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FORWARD_IF_ERROR (int /*<<< orphan*/ ) ; 
 int FSE_NCOUNTBOUND ; 
 int /*<<< orphan*/  FSE_normalizeCount (int /*<<< orphan*/ *,int /*<<< orphan*/  const,unsigned int const*,size_t const,unsigned int const) ; 
 int /*<<< orphan*/  FSE_optimalTableLog (unsigned int const,size_t const,unsigned int const) ; 
 size_t FSE_writeNCount (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MaxSeq ; 

__attribute__((used)) static size_t ZSTD_NCountCost(unsigned const* count, unsigned const max,
                              size_t const nbSeq, unsigned const FSELog)
{
    BYTE wksp[FSE_NCOUNTBOUND];
    S16 norm[MaxSeq + 1];
    const U32 tableLog = FSE_optimalTableLog(FSELog, nbSeq, max);
    FORWARD_IF_ERROR(FSE_normalizeCount(norm, tableLog, count, nbSeq, max));
    return FSE_writeNCount(wksp, sizeof(wksp), norm, max, tableLog);
}