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
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_writeLE32 (int*,int) ; 
 int RAND (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RAND_buffer(U32* seed, void* ptr, size_t size)
{
    size_t i;
    BYTE* op = ptr;

    for (i = 0; i + 4 <= size; i += 4) {
        MEM_writeLE32(op + i, RAND(seed));
    }
    for (; i < size; i++) {
        op[i] = RAND(seed) & 0xff;
    }
}