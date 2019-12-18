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
typedef  int /*<<< orphan*/  frame_t ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int RAND (int /*<<< orphan*/ *) ; 
 size_t writeLiteralsBlockCompressed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t writeLiteralsBlockSimple (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t writeLiteralsBlock(U32* seed, frame_t* frame, size_t contentSize)
{
    /* only do compressed for larger segments to avoid compressibility issues */
    if (RAND(seed) & 7 && contentSize >= 64) {
        return writeLiteralsBlockCompressed(seed, frame, contentSize);
    } else {
        return writeLiteralsBlockSimple(seed, frame, contentSize);
    }
}