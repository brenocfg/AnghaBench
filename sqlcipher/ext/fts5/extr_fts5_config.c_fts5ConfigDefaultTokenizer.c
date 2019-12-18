#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pTok; scalar_t__ pTokApi; } ;
typedef  int /*<<< orphan*/  Fts5Global ;
typedef  TYPE_1__ Fts5Config ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3Fts5GetTokenizer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5ConfigDefaultTokenizer(Fts5Global *pGlobal, Fts5Config *pConfig){
  assert( pConfig->pTok==0 && pConfig->pTokApi==0 );
  return sqlite3Fts5GetTokenizer(
      pGlobal, 0, 0, &pConfig->pTok, &pConfig->pTokApi, 0
  );
}