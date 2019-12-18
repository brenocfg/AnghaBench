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

void sqlite3Fts3Dequote(char *z){
  char quote;                     /* Quote character (if any ) */

  quote = z[0];
  if( quote=='[' || quote=='\'' || quote=='"' || quote=='`' ){
    int iIn = 1;                  /* Index of next byte to read from input */
    int iOut = 0;                 /* Index of next byte to write to output */

    /* If the first byte was a '[', then the close-quote character is a ']' */
    if( quote=='[' ) quote = ']';  

    while( z[iIn] ){
      if( z[iIn]==quote ){
        if( z[iIn+1]!=quote ) break;
        z[iOut++] = quote;
        iIn += 2;
      }else{
        z[iOut++] = z[iIn++];
      }
    }
    z[iOut] = '\0';
  }
}