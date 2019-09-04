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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* lpNSCache ;
struct TYPE_6__ {TYPE_2__* present; } ;
struct TYPE_4__ {TYPE_2__* lpQNext; } ;
struct TYPE_5__ {TYPE_1__ next; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * LPDPSESSIONDESC2 ;

/* Variables and functions */

LPDPSESSIONDESC2 NS_WalkSessions( LPVOID lpNSInfo )
{
  LPDPSESSIONDESC2 lpSessionDesc;
  lpNSCache lpCache = (lpNSCache)lpNSInfo;

  /* FIXME: The pointers could disappear when walking if a prune happens */

  /* Test for end of the list */
  if( lpCache->present == NULL )
  {
    return NULL;
  }

  lpSessionDesc = lpCache->present->data;

  /* Advance tracking pointer */
  lpCache->present = lpCache->present->next.lpQNext;

  return lpSessionDesc;
}