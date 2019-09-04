#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hMetaFilePict; } ;
struct TYPE_8__ {int xExt; int yExt; int /*<<< orphan*/  hMF; int /*<<< orphan*/  mm; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; } ;
typedef  TYPE_1__ STGMEDIUM ;
typedef  TYPE_2__ METAFILEPICT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CloseMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateMetaFileW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MM_ANISOTROPIC ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TYMED_MFPICT ; 
 TYPE_4__* U (TYPE_1__*) ; 

__attribute__((used)) static void create_mfpict(STGMEDIUM *med)
{
    METAFILEPICT *mf;
    HDC hdc = CreateMetaFileW(NULL);

    Rectangle(hdc, 0, 0, 100, 200);

    med->tymed = TYMED_MFPICT;
    U(med)->hMetaFilePict = GlobalAlloc(GMEM_MOVEABLE, sizeof(METAFILEPICT));
    mf = GlobalLock(U(med)->hMetaFilePict);
    mf->mm = MM_ANISOTROPIC;
    mf->xExt = 100;
    mf->yExt = 200;
    mf->hMF = CloseMetaFile(hdc);
    GlobalUnlock(U(med)->hMetaFilePict);
    med->pUnkForRelease = NULL;
}