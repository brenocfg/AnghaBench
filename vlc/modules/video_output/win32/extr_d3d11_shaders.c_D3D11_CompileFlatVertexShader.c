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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  d3d_vshader_t ;
typedef  int /*<<< orphan*/  d3d11_handle_t ;
typedef  int /*<<< orphan*/  d3d11_device_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D11_CompileVertexShader (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  globVertexShaderFlat ; 

HRESULT D3D11_CompileFlatVertexShader(vlc_object_t *obj, d3d11_handle_t *hd3d,
                                      d3d11_device_t *d3d_dev, d3d_vshader_t *output)
{
    return D3D11_CompileVertexShader(obj, hd3d, d3d_dev, globVertexShaderFlat, output);
}