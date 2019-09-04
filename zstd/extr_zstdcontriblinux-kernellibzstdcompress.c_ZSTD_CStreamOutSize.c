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

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_BLOCKSIZE_ABSOLUTEMAX ; 
 size_t ZSTD_blockHeaderSize ; 
 size_t ZSTD_compressBound (int /*<<< orphan*/ ) ; 

size_t ZSTD_CStreamOutSize(void) { return ZSTD_compressBound(ZSTD_BLOCKSIZE_ABSOLUTEMAX) + ZSTD_blockHeaderSize + 4 /* 32-bits hash */; }