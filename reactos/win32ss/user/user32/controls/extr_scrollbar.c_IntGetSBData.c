#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WND ;
struct TYPE_8__ {int /*<<< orphan*/  Vert; int /*<<< orphan*/  Horz; } ;
struct TYPE_7__ {int /*<<< orphan*/  SBCalc; } ;
struct TYPE_6__ {int cbwndExtra; int /*<<< orphan*/  pSBInfo; } ;
typedef  int /*<<< orphan*/  SBWND ;
typedef  TYPE_1__* PWND ;
typedef  TYPE_2__* PSBWND ;
typedef  TYPE_3__* PSBINFO ;
typedef  int /*<<< orphan*/ * PSBDATA ;
typedef  int INT ;

/* Variables and functions */
 TYPE_3__* DesktopPtrToUser (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*) ; 
#define  SB_CTL 130 
#define  SB_HORZ 129 
#define  SB_VERT 128 

__attribute__((used)) static PSBDATA
IntGetSBData(PWND pwnd, INT Bar)
{
   PSBWND pSBWnd;
   PSBINFO pSBInfo;

   pSBInfo = DesktopPtrToUser(pwnd->pSBInfo);
   switch (Bar)
   {
       case SB_HORZ:
         return &pSBInfo->Horz;
       case SB_VERT:
         return &pSBInfo->Vert;
       case SB_CTL:
         if ( pwnd->cbwndExtra < (sizeof(SBWND)-sizeof(WND)) )
         {
            ERR("IntGetSBData Wrong Extra bytes for CTL Scrollbar!\n");
            return 0;
         }
         pSBWnd = (PSBWND)pwnd;
         return (PSBDATA)&pSBWnd->SBCalc;
       default:
            ERR("IntGetSBData Bad Bar!\n");
   }
   return NULL;
}