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
typedef  int /*<<< orphan*/  ZSTD_compressionParameters ;
typedef  int /*<<< orphan*/  ZSTD_CDict ;

/* Variables and functions */
 size_t ZSTD_ALIGN (int) ; 
 size_t ZSTD_CCtxWorkspaceBound (int /*<<< orphan*/ ) ; 

size_t ZSTD_CDictWorkspaceBound(ZSTD_compressionParameters cParams) { return ZSTD_CCtxWorkspaceBound(cParams) + ZSTD_ALIGN(sizeof(ZSTD_CDict)); }