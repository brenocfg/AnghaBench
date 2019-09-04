#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_11__ {int CtlID; void* hwndItem; void* CtlType; } ;
struct TYPE_10__ {int CtlID; void* hwndItem; void* CtlType; } ;
struct TYPE_9__ {int CtlID; void* hwndItem; void* CtlType; } ;
struct TYPE_8__ {int /*<<< orphan*/  owner; void* self; } ;
struct TYPE_7__ {int CtlID; void* CtlType; } ;
typedef  TYPE_1__ MEASUREITEMSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__* LPHEADCOMBO ;
typedef  scalar_t__ LPARAM ;
typedef  void* HWND ;
typedef  TYPE_3__ DRAWITEMSTRUCT ;
typedef  TYPE_4__ DELETEITEMSTRUCT ;
typedef  TYPE_5__ COMPAREITEMSTRUCT ;

/* Variables and functions */
 int /*<<< orphan*/  GWLP_ID ; 
 int /*<<< orphan*/  GetWindowLongPtrW (void*,int /*<<< orphan*/ ) ; 
 void* ODT_COMBOBOX ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,void*,int) ; 
#define  WM_COMPAREITEM 131 
#define  WM_DELETEITEM 130 
#define  WM_DRAWITEM 129 
#define  WM_MEASUREITEM 128 

__attribute__((used)) static LRESULT COMBO_ItemOp( LPHEADCOMBO lphc, UINT msg, LPARAM lParam )
{
   HWND hWnd = lphc->self;
   UINT id = (UINT)GetWindowLongPtrW( hWnd, GWLP_ID );

   TRACE("[%p]: ownerdraw op %04x\n", lphc->self, msg );

   switch( msg )
   {
   case WM_DELETEITEM:
       {
           DELETEITEMSTRUCT *lpIS = (DELETEITEMSTRUCT *)lParam;
           lpIS->CtlType  = ODT_COMBOBOX;
           lpIS->CtlID    = id;
           lpIS->hwndItem = hWnd;
           break;
       }
   case WM_DRAWITEM:
       {
           DRAWITEMSTRUCT *lpIS = (DRAWITEMSTRUCT *)lParam;
           lpIS->CtlType  = ODT_COMBOBOX;
           lpIS->CtlID    = id;
           lpIS->hwndItem = hWnd;
           break;
       }
   case WM_COMPAREITEM:
       {
           COMPAREITEMSTRUCT *lpIS = (COMPAREITEMSTRUCT *)lParam;
           lpIS->CtlType  = ODT_COMBOBOX;
           lpIS->CtlID    = id;
           lpIS->hwndItem = hWnd;
           break;
       }
   case WM_MEASUREITEM:
       {
           MEASUREITEMSTRUCT *lpIS = (MEASUREITEMSTRUCT *)lParam;
           lpIS->CtlType  = ODT_COMBOBOX;
           lpIS->CtlID    = id;
           break;
       }
   }
   return SendMessageW(lphc->owner, msg, id, lParam);
}