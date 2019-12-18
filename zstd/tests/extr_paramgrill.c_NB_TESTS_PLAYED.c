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
typedef  int /*<<< orphan*/  paramValues_t ;
typedef  int /*<<< orphan*/  cParams ;
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 unsigned long long const PARAMTABLEMASK ; 
 unsigned long long XXH64 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_alreadyTested ; 
 int /*<<< orphan*/  pvalsToCParams (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sanitizeParams (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BYTE* NB_TESTS_PLAYED(paramValues_t p)
{
    ZSTD_compressionParameters const cParams = pvalsToCParams(sanitizeParams(p));
    unsigned long long const h64 = XXH64(&cParams, sizeof(cParams), 0);
    return &g_alreadyTested[(h64 >> 3) & PARAMTABLEMASK];
}