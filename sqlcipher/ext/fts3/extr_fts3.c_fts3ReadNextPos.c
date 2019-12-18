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
typedef  int sqlite3_int64 ;

/* Variables and functions */
 int POSITION_LIST_END ; 
 int /*<<< orphan*/  fts3GetDeltaVarint (char**,int*) ; 

__attribute__((used)) static void fts3ReadNextPos(
  char **pp,                    /* IN/OUT: Pointer into position-list buffer */
  sqlite3_int64 *pi             /* IN/OUT: Value read from position-list */
){
  if( (**pp)&0xFE ){
    fts3GetDeltaVarint(pp, pi);
    *pi -= 2;
  }else{
    *pi = POSITION_LIST_END;
  }
}