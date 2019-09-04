#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct d3dx_parameter {int rows; int columns; int /*<<< orphan*/  type; scalar_t__ data; } ;
typedef  int UINT ;
struct TYPE_4__ {int /*<<< orphan*/ ** m; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  float FLOAT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_2__ D3DXMATRIX ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  set_number (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_matrix(struct d3dx_parameter *param, D3DXMATRIX *matrix, BOOL transpose)
{
    UINT i, k;

    for (i = 0; i < 4; ++i)
    {
        for (k = 0; k < 4; ++k)
        {
            FLOAT *tmp = transpose ? (FLOAT *)&matrix->u.m[k][i] : (FLOAT *)&matrix->u.m[i][k];

            if ((i < param->rows) && (k < param->columns))
                set_number(tmp, D3DXPT_FLOAT, (DWORD *)param->data + i * param->columns + k, param->type);
            else
                *tmp = 0.0f;
        }
    }
}