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
typedef  int /*<<< orphan*/  UChar32 ;

/* Variables and functions */
 int SQLITE_MAX_LIKE_PATTERN_LENGTH ; 
 int /*<<< orphan*/  U8_NEXT (unsigned char const*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icuLikeCompare (unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void icuLikeFunc(
  sqlite3_context *context, 
  int argc, 
  sqlite3_value **argv
){
  const unsigned char *zA = sqlite3_value_text(argv[0]);
  const unsigned char *zB = sqlite3_value_text(argv[1]);
  UChar32 uEsc = 0;

  /* Limit the length of the LIKE or GLOB pattern to avoid problems
  ** of deep recursion and N*N behavior in patternCompare().
  */
  if( sqlite3_value_bytes(argv[0])>SQLITE_MAX_LIKE_PATTERN_LENGTH ){
    sqlite3_result_error(context, "LIKE or GLOB pattern too complex", -1);
    return;
  }


  if( argc==3 ){
    /* The escape character string must consist of a single UTF-8 character.
    ** Otherwise, return an error.
    */
    int nE= sqlite3_value_bytes(argv[2]);
    const unsigned char *zE = sqlite3_value_text(argv[2]);
    int i = 0;
    if( zE==0 ) return;
    U8_NEXT(zE, i, nE, uEsc);
    if( i!=nE){
      sqlite3_result_error(context, 
          "ESCAPE expression must be a single character", -1);
      return;
    }
  }

  if( zA && zB ){
    sqlite3_result_int(context, icuLikeCompare(zA, zB, uEsc));
  }
}