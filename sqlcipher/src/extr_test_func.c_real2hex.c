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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void real2hex(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  union {
    sqlite3_uint64 i;
    double r;
    unsigned char x[8];
  } v;
  char zOut[20];
  int i;
  int bigEndian;
  v.i = 1;
  bigEndian = v.x[0]==0;
  v.r = sqlite3_value_double(argv[0]);
  for(i=0; i<8; i++){
    if( bigEndian ){
      zOut[i*2]   = "0123456789abcdef"[v.x[i]>>4];
      zOut[i*2+1] = "0123456789abcdef"[v.x[i]&0xf];
    }else{
      zOut[14-i*2]   = "0123456789abcdef"[v.x[i]>>4];
      zOut[14-i*2+1] = "0123456789abcdef"[v.x[i]&0xf];
    }
  }
  zOut[16] = 0;
  sqlite3_result_text(context, zOut, -1, SQLITE_TRANSIENT);
}