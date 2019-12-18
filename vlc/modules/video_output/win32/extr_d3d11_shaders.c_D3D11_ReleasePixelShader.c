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
struct TYPE_3__ {int /*<<< orphan*/ ** d3dpixelShader; } ;
typedef  TYPE_1__ d3d_quad_t ;

/* Variables and functions */
 size_t D3D11_MAX_SHADER_VIEW ; 
 int /*<<< orphan*/  ID3D11PixelShader_Release (int /*<<< orphan*/ *) ; 

void D3D11_ReleasePixelShader(d3d_quad_t *quad)
{
    for (size_t i=0; i<D3D11_MAX_SHADER_VIEW; i++)
    {
        if (quad->d3dpixelShader[i])
        {
            ID3D11PixelShader_Release(quad->d3dpixelShader[i]);
            quad->d3dpixelShader[i] = NULL;
        }
    }
}