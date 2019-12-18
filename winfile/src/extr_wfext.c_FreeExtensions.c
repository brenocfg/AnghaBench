#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {scalar_t__ hModule; int /*<<< orphan*/  (* ExtProc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ;} ;
typedef  size_t INT ;
typedef  int /*<<< orphan*/  HMENU ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FMEVENT_UNLOAD ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeToolbarExtensions () ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDM_EXTENSIONS ; 
 int /*<<< orphan*/  MF_BYPOSITION ; 
 int /*<<< orphan*/  MapIDMToMenuPos (int /*<<< orphan*/ ) ; 
 TYPE_1__* extensions ; 
 int /*<<< orphan*/  hwndFrame ; 
 size_t iNumExtensions ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long) ; 

VOID
FreeExtensions()
{
   INT i;
   HMENU hMenuFrame;

   FreeToolbarExtensions();


   hMenuFrame = GetMenu(hwndFrame);

   // we are going to delete all extensions and thus each one to delete is at the same place
   UINT posToDelete = MapIDMToMenuPos(IDM_EXTENSIONS);

   for (i = 0; i < iNumExtensions; i++) {
      (extensions[i].ExtProc)(NULL, FMEVENT_UNLOAD, 0L);
      DeleteMenu(hMenuFrame, posToDelete, MF_BYPOSITION);
      FreeLibrary((HANDLE)extensions[i].hModule);
   }
   iNumExtensions = 0;
}