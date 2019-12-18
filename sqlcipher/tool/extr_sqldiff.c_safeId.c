#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  sqlite3_keyword_check (char const*,int) ; 
 char* sqlite3_mprintf (char*,...) ; 

__attribute__((used)) static char *safeId(const char *zId){
  int i, x;
  char c;
  if( zId[0]==0 ) return sqlite3_mprintf("\"\"");
  for(i=x=0; (c = zId[i])!=0; i++){
    if( !isalpha(c) && c!='_' ){
      if( i>0 && isdigit(c) ){
        x++;
      }else{
        return sqlite3_mprintf("\"%w\"", zId);
      }
    }
  }
  if( x || !sqlite3_keyword_check(zId,i) ){
    return sqlite3_mprintf("%s", zId);
  }
  return sqlite3_mprintf("\"%w\"", zId);
}