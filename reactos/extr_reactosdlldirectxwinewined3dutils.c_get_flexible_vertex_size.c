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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int GET_TEXCOORD_SIZE_FROM_FVF (int,int) ; 
 int WINED3DFVF_DIFFUSE ; 
 int WINED3DFVF_NORMAL ; 
 int WINED3DFVF_POSITION_MASK ; 
 int WINED3DFVF_PSIZE ; 
 int WINED3DFVF_SPECULAR ; 
 int WINED3DFVF_TEXCOUNT_MASK ; 
 int WINED3DFVF_TEXCOUNT_SHIFT ; 
#define  WINED3DFVF_XYZ 135 
#define  WINED3DFVF_XYZB1 134 
#define  WINED3DFVF_XYZB2 133 
#define  WINED3DFVF_XYZB3 132 
#define  WINED3DFVF_XYZB4 131 
#define  WINED3DFVF_XYZB5 130 
#define  WINED3DFVF_XYZRHW 129 
#define  WINED3DFVF_XYZW 128 

DWORD get_flexible_vertex_size(DWORD d3dvtVertexType) {
    DWORD size = 0;
    int i;
    int numTextures = (d3dvtVertexType & WINED3DFVF_TEXCOUNT_MASK) >> WINED3DFVF_TEXCOUNT_SHIFT;

    if (d3dvtVertexType & WINED3DFVF_NORMAL) size += 3 * sizeof(float);
    if (d3dvtVertexType & WINED3DFVF_DIFFUSE) size += sizeof(DWORD);
    if (d3dvtVertexType & WINED3DFVF_SPECULAR) size += sizeof(DWORD);
    if (d3dvtVertexType & WINED3DFVF_PSIZE) size += sizeof(DWORD);
    switch (d3dvtVertexType & WINED3DFVF_POSITION_MASK) {
        case WINED3DFVF_XYZ:    size += 3 * sizeof(float); break;
        case WINED3DFVF_XYZRHW: size += 4 * sizeof(float); break;
        case WINED3DFVF_XYZB1:  size += 4 * sizeof(float); break;
        case WINED3DFVF_XYZB2:  size += 5 * sizeof(float); break;
        case WINED3DFVF_XYZB3:  size += 6 * sizeof(float); break;
        case WINED3DFVF_XYZB4:  size += 7 * sizeof(float); break;
        case WINED3DFVF_XYZB5:  size += 8 * sizeof(float); break;
        case WINED3DFVF_XYZW:   size += 4 * sizeof(float); break;
        default: ERR("Unexpected position mask\n");
    }
    for (i = 0; i < numTextures; i++) {
        size += GET_TEXCOORD_SIZE_FROM_FVF(d3dvtVertexType, i) * sizeof(float);
    }

    return size;
}