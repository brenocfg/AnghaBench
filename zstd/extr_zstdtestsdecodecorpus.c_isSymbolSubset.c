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
typedef  size_t const BYTE ;

/* Variables and functions */

__attribute__((used)) static int isSymbolSubset(const BYTE* symbols, size_t len, const BYTE* set, BYTE maxSymbolValue)
{
    size_t i;

    for (i = 0; i < len; i++) {
        if (symbols[i] > maxSymbolValue || !set[symbols[i]]) {
            return 0;
        }
    }
    return 1;
}