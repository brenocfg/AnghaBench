#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char const* zAuthContext; TYPE_1__* pParse; } ;
struct TYPE_6__ {char const* zAuthContext; } ;
typedef  TYPE_1__ Parse ;
typedef  TYPE_2__ AuthContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

void sqlite3AuthContextPush(
  Parse *pParse,
  AuthContext *pContext, 
  const char *zContext
){
  assert( pParse );
  pContext->pParse = pParse;
  pContext->zAuthContext = pParse->zAuthContext;
  pParse->zAuthContext = zContext;
}