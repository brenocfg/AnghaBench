#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nUsed; char* zBuf; } ;
typedef  TYPE_1__ JsonString ;

/* Variables and functions */
 int /*<<< orphan*/  jsonAppendChar (TYPE_1__*,char) ; 

__attribute__((used)) static void jsonAppendSeparator(JsonString *p){
  char c;
  if( p->nUsed==0 ) return;
  c = p->zBuf[p->nUsed-1];
  if( c!='[' && c!='{' ) jsonAppendChar(p, ',');
}