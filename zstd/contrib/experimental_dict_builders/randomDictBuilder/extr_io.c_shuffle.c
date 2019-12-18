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
typedef  int U32 ;

/* Variables and functions */
 unsigned int getRand (int*) ; 

__attribute__((used)) static void shuffle(const char** fileNamesTable, unsigned nbFiles) {
    U32 seed = 0xFD2FB528;
    unsigned i;
    for (i = nbFiles - 1; i > 0; --i) {
        unsigned const j = getRand(&seed) % (i + 1);
        const char* const tmp = fileNamesTable[j];
        fileNamesTable[j] = fileNamesTable[i];
        fileNamesTable[i] = tmp;
    }
}