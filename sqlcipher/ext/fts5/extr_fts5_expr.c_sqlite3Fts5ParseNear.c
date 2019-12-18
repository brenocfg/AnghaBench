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
struct TYPE_3__ {int n; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ Fts5Token ;
typedef  int /*<<< orphan*/  Fts5Parse ;

/* Variables and functions */
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts5ParseError (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

void sqlite3Fts5ParseNear(Fts5Parse *pParse, Fts5Token *pTok){
  if( pTok->n!=4 || memcmp("NEAR", pTok->p, 4) ){
    sqlite3Fts5ParseError(
        pParse, "fts5: syntax error near \"%.*s\"", pTok->n, pTok->p
    );
  }
}