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
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,unsigned int) ; 
 size_t g_blockSize ; 

void BMK_SetBlockSize(size_t blockSize)
{
    g_blockSize = blockSize;
    DISPLAYLEVEL(2, "using blocks of size %u KB \n", (unsigned)(blockSize>>10));
}