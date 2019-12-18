#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  cHandleEntries; } ;
struct TYPE_11__ {int /*<<< orphan*/ * DbgHandleCount; } ;
struct TYPE_10__ {TYPE_4__* ppi; } ;
struct TYPE_9__ {int type; TYPE_4__* pi; scalar_t__ flags; struct TYPE_9__* ptr; } ;
struct TYPE_8__ {TYPE_2__* freelist; } ;
typedef  TYPE_1__* PUSER_HANDLE_TABLE ;
typedef  TYPE_2__* PUSER_HANDLE_ENTRY ;
typedef  TYPE_3__* PTHREADINFO ;
typedef  TYPE_4__* PPROCESSINFO ;

/* Variables and functions */
#define  TYPE_ACCELTABLE 134 
#define  TYPE_CALLPROC 133 
#define  TYPE_CURSOR 132 
#define  TYPE_HOOK 131 
#define  TYPE_MENU 130 
#define  TYPE_WINDOW 129 
#define  TYPE_WINEVENTHOOK 128 
 TYPE_5__* gpsi ; 

__attribute__((used)) __inline static void *free_user_entry(PUSER_HANDLE_TABLE ht, PUSER_HANDLE_ENTRY entry)
{
   void *ret;

#if DBG
   {
       PPROCESSINFO ppi;
       switch (entry->type)
       {
           case TYPE_WINDOW:
           case TYPE_HOOK:
           case TYPE_WINEVENTHOOK:
               ppi = ((PTHREADINFO)entry->pi)->ppi;
               break;
           case TYPE_MENU:
           case TYPE_CURSOR:
           case TYPE_CALLPROC:
           case TYPE_ACCELTABLE:
               ppi = entry->pi;
               break;
           default:
               ppi = NULL;
       }
       if (ppi)
           ppi->DbgHandleCount[entry->type]--;
   }
#endif

   ret = entry->ptr;
   entry->ptr  = ht->freelist;
   entry->type = 0;
   entry->flags = 0;
   entry->pi = NULL;
   ht->freelist  = entry;

   gpsi->cHandleEntries--;

   return ret;
}