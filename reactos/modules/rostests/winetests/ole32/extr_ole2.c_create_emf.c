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
struct TYPE_6__ {int /*<<< orphan*/  hEnhMetaFile; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pUnkForRelease; int /*<<< orphan*/  tymed; } ;
typedef  TYPE_1__ STGMEDIUM ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CloseEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateEnhMetaFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TYMED_ENHMF ; 
 TYPE_3__* U (TYPE_1__*) ; 

__attribute__((used)) static void create_emf(STGMEDIUM *med)
{
    HDC hdc = CreateEnhMetaFileW(NULL, NULL, NULL, NULL);

    Rectangle(hdc, 0, 0, 150, 300);
    med->tymed = TYMED_ENHMF;
    U(med)->hEnhMetaFile = CloseEnhMetaFile(hdc);
    med->pUnkForRelease = NULL;
}