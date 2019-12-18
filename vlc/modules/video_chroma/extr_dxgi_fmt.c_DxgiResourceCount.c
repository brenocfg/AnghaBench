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
struct TYPE_3__ {scalar_t__* resourceFormat; } ;
typedef  TYPE_1__ d3d_format_t ;
typedef  size_t UINT ;

/* Variables and functions */
 size_t D3D11_MAX_SHADER_VIEW ; 
 scalar_t__ DXGI_FORMAT_UNKNOWN ; 

UINT DxgiResourceCount(const d3d_format_t *d3d_fmt)
{
    for (UINT count=0; count<D3D11_MAX_SHADER_VIEW; count++)
    {
        if (d3d_fmt->resourceFormat[count] == DXGI_FORMAT_UNKNOWN)
            return count;
    }
    return D3D11_MAX_SHADER_VIEW;
}