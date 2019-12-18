#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* xDelete ) (scalar_t__) ;} ;
struct TYPE_5__ {scalar_t__ pTokenizer; TYPE_1__ tokenizer; } ;
typedef  TYPE_2__ PorterTokenizer ;
typedef  int /*<<< orphan*/  Fts5Tokenizer ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void fts5PorterDelete(Fts5Tokenizer *pTok){
  if( pTok ){
    PorterTokenizer *p = (PorterTokenizer*)pTok;
    if( p->pTokenizer ){
      p->tokenizer.xDelete(p->pTokenizer);
    }
    sqlite3_free(p);
  }
}