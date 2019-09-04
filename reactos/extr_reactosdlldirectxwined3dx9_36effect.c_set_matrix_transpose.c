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
typedef  int /*<<< orphan*/  FLOAT ;
typedef  TYPE_2__ D3DXMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXPT_FLOAT ; 
 int /*<<< orphan*/  set_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_matrix_transpose(struct d3dx_parameter *param, const D3DXMATRIX *matrix)
{
    UINT i, k;

    for (i = 0; i < param->rows; ++i)
    {
        for (k = 0; k < param->columns; ++k)
        {
            set_number((FLOAT *)param->data + i * param->columns + k, param->type,
                    &matrix->u.m[k][i], D3DXPT_FLOAT);
        }
    }
}