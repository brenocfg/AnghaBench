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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fts5Dequote (char*) ; 
 scalar_t__ fts5_iswhitespace (char) ; 

void sqlite3Fts5Dequote(char *z){
  char quote;                     /* Quote character (if any ) */

  assert( 0==fts5_iswhitespace(z[0]) );
  quote = z[0];
  if( quote=='[' || quote=='\'' || quote=='"' || quote=='`' ){
    fts5Dequote(z);
  }
}