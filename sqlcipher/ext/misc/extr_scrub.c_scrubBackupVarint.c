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
typedef  int u8 ;
typedef  int sqlite3_int64 ;

/* Variables and functions */

__attribute__((used)) static int scrubBackupVarint(const u8 *z, sqlite3_int64 *pVal){
  sqlite3_int64 v = 0;
  int i;
  for(i=0; i<8; i++){
    v = (v<<7) + (z[i]&0x7f);
    if( (z[i]&0x80)==0 ){ *pVal = v; return i+1; }
  }
  v = (v<<8) + (z[i]&0xff);
  *pVal = v;
  return 9;
}