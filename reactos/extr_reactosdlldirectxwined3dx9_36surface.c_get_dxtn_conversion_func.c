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
typedef  int /*<<< orphan*/ * dxtn_conversion_func ;
typedef  int D3DFORMAT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  D3DFMT_DXT1 130 
#define  D3DFMT_DXT3 129 
#define  D3DFMT_DXT5 128 
 int /*<<< orphan*/ * wined3d_dxt1_decode ; 
 int /*<<< orphan*/ * wined3d_dxt1_encode ; 
 int /*<<< orphan*/ * wined3d_dxt3_decode ; 
 int /*<<< orphan*/ * wined3d_dxt3_encode ; 
 int /*<<< orphan*/ * wined3d_dxt5_decode ; 
 int /*<<< orphan*/ * wined3d_dxt5_encode ; 

__attribute__((used)) static dxtn_conversion_func get_dxtn_conversion_func(D3DFORMAT format, BOOL encode)
{
    switch (format)
    {
        case D3DFMT_DXT1:
            return encode ? wined3d_dxt1_encode : wined3d_dxt1_decode;
        case D3DFMT_DXT3:
            return encode ? wined3d_dxt3_encode : wined3d_dxt3_decode;
        case D3DFMT_DXT5:
            return encode ? wined3d_dxt5_encode : wined3d_dxt5_decode;
        default:
            return NULL;
    }
}