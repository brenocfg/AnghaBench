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
struct TYPE_3__ {int /*<<< orphan*/  n; } ;
typedef  TYPE_1__ t1CountCtx ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int SQLITE_BIGENDIAN ; 
 scalar_t__ SQLITE_NULL ; 
 TYPE_1__* sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error16 (int /*<<< orphan*/ *,char const*,int) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void t1CountStep(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  t1CountCtx *p;
  p = sqlite3_aggregate_context(context, sizeof(*p));
  if( (argc==0 || SQLITE_NULL!=sqlite3_value_type(argv[0]) ) && p ){
    p->n++;
  }
  if( argc>0 ){
    int v = sqlite3_value_int(argv[0]);
    if( v==40 ){
      sqlite3_result_error(context, "value of 40 handed to x_count", -1);
#ifndef SQLITE_OMIT_UTF16
    }else if( v==41 ){
      const char zUtf16ErrMsg[] = { 0, 0x61, 0, 0x62, 0, 0x63, 0, 0, 0};
      sqlite3_result_error16(context, &zUtf16ErrMsg[1-SQLITE_BIGENDIAN], -1);
#endif
    }
  }
}