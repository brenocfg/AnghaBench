#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {double** m; } ;
typedef  TYPE_1__ ColorMatrix ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int gdip_round (double) ; 

__attribute__((used)) static BOOL round_color_matrix(const ColorMatrix *matrix, int values[5][5])
{
    /* Convert floating point color matrix to int[5][5], return TRUE if it's an identity */
    BOOL identity = TRUE;
    int i, j;

    for (i=0; i<4; i++)
        for (j=0; j<5; j++)
        {
            if (matrix->m[j][i] != (i == j ? 1.0 : 0.0))
                identity = FALSE;
            values[j][i] = gdip_round(matrix->m[j][i] * 256.0);
        }

    return identity;
}