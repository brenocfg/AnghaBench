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
typedef  int OPJ_SIZE_T ;
typedef  int /*<<< orphan*/  OPJ_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ * const,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void convert_32s_C1P1(const OPJ_INT32* pSrc, OPJ_INT32* const* pDst,
                             OPJ_SIZE_T length)
{
    memcpy(pDst[0], pSrc, length * sizeof(OPJ_INT32));
}