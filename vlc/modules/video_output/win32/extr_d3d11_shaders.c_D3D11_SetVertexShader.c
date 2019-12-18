#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  shader; int /*<<< orphan*/  layout; } ;
typedef  TYPE_1__ d3d_vshader_t ;

/* Variables and functions */
 int /*<<< orphan*/  ID3D11InputLayout_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3D11VertexShader_AddRef (int /*<<< orphan*/ ) ; 

void D3D11_SetVertexShader(d3d_vshader_t *dst, d3d_vshader_t *src)
{
    dst->layout = src->layout;
    ID3D11InputLayout_AddRef(dst->layout);
    dst->shader = src->shader;
    ID3D11VertexShader_AddRef(dst->shader);
}