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
struct TYPE_3__ {int xExt; int yExt; int /*<<< orphan*/  hMF; int /*<<< orphan*/  mm; } ;
typedef  TYPE_1__ METAFILEPICT ;
typedef  int /*<<< orphan*/  HMETAFILEPICT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_ANISOTROPIC ; 
 int /*<<< orphan*/  create_mf () ; 

__attribute__((used)) static HMETAFILEPICT create_metafilepict(void)
{
    HGLOBAL ret = GlobalAlloc(GMEM_MOVEABLE, sizeof(METAFILEPICT));
    METAFILEPICT *mf = GlobalLock(ret);
    mf->mm = MM_ANISOTROPIC;
    mf->xExt = 100;
    mf->yExt = 200;
    mf->hMF = create_mf();
    GlobalUnlock(ret);
    return ret;
}