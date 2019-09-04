#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  hGlobal; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; } ;
typedef  TYPE_1__ STGMEDIUM ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int GMEM_DDESHARE ; 
 int GMEM_MOVEABLE ; 
 int /*<<< orphan*/  GlobalAlloc (int,int) ; 
 char* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYMED_HGLOBAL ; 
 TYPE_3__* U (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void create_text(STGMEDIUM *med)
{
    HGLOBAL handle;
    char *p;

    handle = GlobalAlloc(GMEM_DDESHARE|GMEM_MOVEABLE, 5);
    p = GlobalLock(handle);
    strcpy(p, "test");
    GlobalUnlock(handle);

    med->tymed = TYMED_HGLOBAL;
    U(med)->hGlobal = handle;
    med->pUnkForRelease = NULL;
}