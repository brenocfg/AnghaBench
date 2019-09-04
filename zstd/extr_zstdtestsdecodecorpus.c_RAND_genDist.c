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
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 size_t DISTSIZE ; 
 int RAND (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RAND_genDist(U32* seed, BYTE* dist, double weight)
{
    size_t i = 0;
    size_t statesLeft = DISTSIZE;
    BYTE symb = (BYTE) (RAND(seed) % 256);
    BYTE step = (BYTE) ((RAND(seed) % 256) | 1); /* force it to be odd so it's relatively prime to 256 */

    while (i < DISTSIZE) {
        size_t states = ((size_t)(weight * statesLeft)) + 1;
        size_t j;
        for (j = 0; j < states && i < DISTSIZE; j++, i++) {
            dist[i] = symb;
        }

        symb += step;
        statesLeft -= states;
    }
}