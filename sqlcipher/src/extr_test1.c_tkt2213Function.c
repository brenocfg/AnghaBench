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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tkt2213Function(
  sqlite3_context *context, 
  int argc,  
  sqlite3_value **argv
){
  int nText;
  unsigned char const *zText1;
  unsigned char const *zText2;
  unsigned char const *zText3;

  nText = sqlite3_value_bytes(argv[0]);
  zText1 = sqlite3_value_text(argv[0]);
  zText2 = sqlite3_value_text(argv[0]);
  zText3 = sqlite3_value_text(argv[0]);

  if( zText1!=zText2 || zText2!=zText3 ){
    sqlite3_result_error(context, "tkt2213 is not fixed", -1);
  }else{
    char *zCopy = (char *)sqlite3_malloc(nText);
    memcpy(zCopy, zText1, nText);
    sqlite3_result_text(context, zCopy, nText, sqlite3_free);
  }
}