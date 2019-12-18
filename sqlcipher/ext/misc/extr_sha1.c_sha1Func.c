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
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  SHA1Context ;

/* Variables and functions */
 int SQLITE_BLOB ; 
 int SQLITE_NULL ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hash_finish (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_step (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sha1Func(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  SHA1Context cx;
  int eType = sqlite3_value_type(argv[0]);
  int nByte = sqlite3_value_bytes(argv[0]);
  char zOut[44];

  assert( argc==1 );
  if( eType==SQLITE_NULL ) return;
  hash_init(&cx);
  if( eType==SQLITE_BLOB ){
    hash_step(&cx, sqlite3_value_blob(argv[0]), nByte);
  }else{
    hash_step(&cx, sqlite3_value_text(argv[0]), nByte);
  }
  hash_finish(&cx, zOut);
  sqlite3_result_text(context, zOut, 40, SQLITE_TRANSIENT);
}