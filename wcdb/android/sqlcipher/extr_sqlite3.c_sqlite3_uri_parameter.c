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

/* Variables and functions */
 scalar_t__ sqlite3Strlen30 (char const*) ; 
 int strcmp (char const*,char const*) ; 

const char *sqlite3_uri_parameter(const char *zFilename, const char *zParam){
  if( zFilename==0 || zParam==0 ) return 0;
  zFilename += sqlite3Strlen30(zFilename) + 1;
  while( zFilename[0] ){
    int x = strcmp(zFilename, zParam);
    zFilename += sqlite3Strlen30(zFilename) + 1;
    if( x==0 ) return zFilename;
    zFilename += sqlite3Strlen30(zFilename) + 1;
  }
  return 0;
}