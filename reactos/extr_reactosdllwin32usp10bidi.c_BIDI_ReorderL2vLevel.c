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
typedef  int BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ odd (int) ; 
 int /*<<< orphan*/  reverse (int*,int) ; 

int BIDI_ReorderL2vLevel(int level, int *pIndexs, const BYTE* plevel, int cch, BOOL fReverse)
{
    int ich = 0;
    int newlevel = -1;

    /* true as soon as first odd level encountered */
    fReverse = fReverse || odd(level);

    for (; ich < cch; ich++)
    {
        if (plevel[ich] < level)
            break;
        else if (plevel[ich] > level)
            newlevel = ich;
    }
    if (fReverse)
    {
        reverse(pIndexs, ich);
    }

    if (newlevel >= 0)
    {
        ich = 0;
        for (; ich < cch; ich++)
            if (plevel[ich] < level)
                break;
            else if (plevel[ich] > level)
                ich += BIDI_ReorderL2vLevel(level + 1, pIndexs + ich, plevel + ich,
                cch - ich, fReverse) - 1;
    }

    return ich;
}