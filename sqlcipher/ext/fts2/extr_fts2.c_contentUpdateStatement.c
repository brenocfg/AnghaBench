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
struct TYPE_3__ {int nColumn; char** azContentColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  int /*<<< orphan*/  StringBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  initStringBuffer (int /*<<< orphan*/ *) ; 
 char const* stringBufferData (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *contentUpdateStatement(fulltext_vtab *v){
  StringBuffer sb;
  int i;

  initStringBuffer(&sb);
  append(&sb, "update %_content set ");
  for(i=0; i<v->nColumn; ++i) {
    if( i>0 ){
      append(&sb, ", ");
    }
    append(&sb, v->azContentColumn[i]);
    append(&sb, " = ?");
  }
  append(&sb, " where rowid = ?");
  return stringBufferData(&sb);
}