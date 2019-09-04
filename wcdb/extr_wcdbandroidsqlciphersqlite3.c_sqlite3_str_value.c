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
struct TYPE_3__ {size_t nChar; char* zText; } ;
typedef  TYPE_1__ sqlite3_str ;

/* Variables and functions */

char *sqlite3_str_value(sqlite3_str *p){
  if( p==0 || p->nChar==0 ) return 0;
  p->zText[p->nChar] = 0;
  return p->zText;
}