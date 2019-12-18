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
typedef  int sqlite3_uint64 ;

/* Variables and functions */

int sqlite3Fts3VarintLen(sqlite3_uint64 v){
  int i = 0;
  do{
    i++;
    v >>= 7;
  }while( v!=0 );
  return i;
}