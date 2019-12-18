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
struct TYPE_3__ {scalar_t__ zOut; } ;
typedef  TYPE_1__ HighlightContext ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ sqlite3_mprintf (char*,scalar_t__,int,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void fts5HighlightAppend(
  int *pRc, 
  HighlightContext *p, 
  const char *z, int n
){
  if( *pRc==SQLITE_OK && z ){
    if( n<0 ) n = (int)strlen(z);
    p->zOut = sqlite3_mprintf("%z%.*s", p->zOut, n, z);
    if( p->zOut==0 ) *pRc = SQLITE_NOMEM;
  }
}