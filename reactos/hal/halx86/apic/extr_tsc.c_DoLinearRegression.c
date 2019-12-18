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
typedef  int ULONG64 ;
typedef  int ULONG ;

/* Variables and functions */
 int SAMPLE_FREQENCY ; 

__attribute__((used)) static
ULONG64
DoLinearRegression(
    ULONG XMax,
    ULONG64 *ArrayY)
{
    ULONG X, SumXX;
    ULONG64 SumXY;

    /* Calculate the sum of the squares of X */
    SumXX = (XMax * (XMax + 1) * (2*XMax + 1)) / 6;

    /* Calculate the sum of the differences to the first value
       weighted by x */
    for (SumXY = 0, X = 1; X <= XMax; X++)
    {
         SumXY += X * (ArrayY[X] - ArrayY[0]);
    }

    /* Account for sample frequency */
    SumXY *= SAMPLE_FREQENCY;

    /* Return the quotient of the sums */
    return (SumXY + (SumXX/2)) / SumXX;
}