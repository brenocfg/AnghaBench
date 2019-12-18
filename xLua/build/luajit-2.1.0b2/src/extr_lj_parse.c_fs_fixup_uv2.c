#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_9__ {int info; size_t slot; } ;
typedef  TYPE_2__ VarInfo ;
typedef  size_t VarIndex ;
struct TYPE_11__ {TYPE_1__* ls; } ;
struct TYPE_10__ {size_t sizeuv; } ;
struct TYPE_8__ {TYPE_2__* vstack; } ;
typedef  size_t MSize ;
typedef  TYPE_3__ GCproto ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 size_t LJ_MAX_VSTACK ; 
 size_t PROTO_UV_IMMUTABLE ; 
 size_t PROTO_UV_LOCAL ; 
 int VSTACK_VAR_RW ; 
 size_t* proto_uv (TYPE_3__*) ; 

__attribute__((used)) static void fs_fixup_uv2(FuncState *fs, GCproto *pt)
{
  VarInfo *vstack = fs->ls->vstack;
  uint16_t *uv = proto_uv(pt);
  MSize i, n = pt->sizeuv;
  for (i = 0; i < n; i++) {
    VarIndex vidx = uv[i];
    if (vidx >= LJ_MAX_VSTACK)
      uv[i] = vidx - LJ_MAX_VSTACK;
    else if ((vstack[vidx].info & VSTACK_VAR_RW))
      uv[i] = vstack[vidx].slot | PROTO_UV_LOCAL;
    else
      uv[i] = vstack[vidx].slot | PROTO_UV_LOCAL | PROTO_UV_IMMUTABLE;
  }
}