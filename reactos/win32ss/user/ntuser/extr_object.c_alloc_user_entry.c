#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  cHandleEntries; } ;
struct TYPE_9__ {int generation; struct TYPE_9__* ptr; } ;
struct TYPE_8__ {int nb_handles; int allocated_handles; TYPE_2__* handles; TYPE_2__* freelist; } ;
typedef  TYPE_1__* PUSER_HANDLE_TABLE ;
typedef  TYPE_2__* PUSER_HANDLE_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  DbgUserDumpHandleTable () ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int) ; 
 int FIRST_USER_HANDLE ; 
 int LAST_USER_HANDLE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* UserHeapReAlloc (TYPE_2__*,int) ; 
 TYPE_3__* gpsi ; 
 int max (int,int) ; 
 int min (int,int) ; 

__attribute__((used)) __inline static PUSER_HANDLE_ENTRY alloc_user_entry(PUSER_HANDLE_TABLE ht)
{
   PUSER_HANDLE_ENTRY entry;
   TRACE("handles used %lu\n", gpsi->cHandleEntries);

   if (ht->freelist)
   {
      entry = ht->freelist;
      ht->freelist = entry->ptr;

      gpsi->cHandleEntries++;
      return entry;
   }

   if (ht->nb_handles >= ht->allocated_handles)  /* Need to grow the array */
   {
       ERR("Out of user handles! Used -> %lu, NM_Handle -> %d\n", gpsi->cHandleEntries, ht->nb_handles);

#if DBG
       DbgUserDumpHandleTable();
#endif

      return NULL;
#if 0
      PUSER_HANDLE_ENTRY new_handles;
      /* Grow array by 50% (but at minimum 32 entries) */
      int growth = max( 32, ht->allocated_handles / 2 );
      int new_size = min( ht->allocated_handles + growth, (LAST_USER_HANDLE-FIRST_USER_HANDLE+1) >> 1 );
      if (new_size <= ht->allocated_handles)
         return NULL;
      if (!(new_handles = UserHeapReAlloc( ht->handles, new_size * sizeof(*ht->handles) )))
         return NULL;
      ht->handles = new_handles;
      ht->allocated_handles = new_size;
#endif
   }

   entry = &ht->handles[ht->nb_handles++];

   entry->generation = 1;

   gpsi->cHandleEntries++;

   return entry;
}