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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t DISTSIZE ; 
 size_t RAND (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RAND_bufferDist(U32* seed, BYTE* dist, void* ptr, size_t size)
{
    size_t i;
    BYTE* op = ptr;

    for (i = 0; i < size; i++) {
        op[i] = dist[RAND(seed) % DISTSIZE];
    }
}