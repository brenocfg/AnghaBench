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
typedef  int /*<<< orphan*/  optState_t ;
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int ZSTD_litLengthContribution (int /*<<< orphan*/  const,int /*<<< orphan*/  const* const,int) ; 
 int ZSTD_rawLiteralsCost (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const,int /*<<< orphan*/  const* const,int) ; 

__attribute__((used)) static int ZSTD_literalsContribution(const BYTE* const literals, U32 const litLength,
                                     const optState_t* const optPtr,
                                     int optLevel)
{
    int const contribution = ZSTD_rawLiteralsCost(literals, litLength, optPtr, optLevel)
                           + ZSTD_litLengthContribution(litLength, optPtr, optLevel);
    return contribution;
}