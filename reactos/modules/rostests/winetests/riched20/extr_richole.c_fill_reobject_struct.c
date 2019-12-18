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
struct TYPE_4__ {void* cy; void* cx; } ;
struct TYPE_5__ {int cbStruct; void* dwUser; void* dwFlags; void* dvaspect; TYPE_1__ sizel; int /*<<< orphan*/  polesite; int /*<<< orphan*/  pstg; int /*<<< orphan*/  poleobj; void* cp; int /*<<< orphan*/  clsid; } ;
typedef  TYPE_2__ REOBJECT ;
typedef  int /*<<< orphan*/  LPSTORAGE ;
typedef  int /*<<< orphan*/  LPOLEOBJECT ;
typedef  int /*<<< orphan*/  LPOLECLIENTSITE ;
typedef  void* LONG ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_NULL ; 

__attribute__((used)) static void fill_reobject_struct(REOBJECT *reobj, LONG cp, LPOLEOBJECT poleobj,
                                 LPSTORAGE pstg, LPOLECLIENTSITE polesite, LONG sizel_cx,
                                 LONG sizel_cy, DWORD aspect, DWORD flags, DWORD user)
{
  reobj->cbStruct = sizeof(*reobj);
  reobj->clsid = CLSID_NULL;
  reobj->cp = cp;
  reobj->poleobj = poleobj;
  reobj->pstg = pstg;
  reobj->polesite = polesite;
  reobj->sizel.cx = sizel_cx;
  reobj->sizel.cy = sizel_cy;
  reobj->dvaspect = aspect;
  reobj->dwFlags = flags;
  reobj->dwUser = user;
}