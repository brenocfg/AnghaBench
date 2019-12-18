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
struct TYPE_3__ {float x; float y; float z; float w; } ;
typedef  int /*<<< orphan*/  IDirect3DDevice9 ;
typedef  int /*<<< orphan*/  ID3DXConstantTable ;
typedef  TYPE_1__ D3DXVECTOR4 ;

/* Variables and functions */
 int /*<<< orphan*/  ID3DXConstantTable_SetVector (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 

__attribute__((used)) static void set_float4_d3d9(IDirect3DDevice9 *device, ID3DXConstantTable *constants, const char *name,
        float x, float y, float z, float w)
{
    D3DXVECTOR4 vector;
    vector.x = x;
    vector.y = y;
    vector.z = z;
    vector.w = w;
    ID3DXConstantTable_SetVector(constants, device, name, &vector);
}