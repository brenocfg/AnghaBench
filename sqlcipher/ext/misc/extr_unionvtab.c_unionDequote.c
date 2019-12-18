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
 scalar_t__ ALWAYS (char) ; 

__attribute__((used)) static void unionDequote(char *z){
  if( z ){
    char q = z[0];

    /* Set stack variable q to the close-quote character */
    if( q=='[' || q=='\'' || q=='"' || q=='`' ){
      int iIn = 1;
      int iOut = 0;
      if( q=='[' ) q = ']';  
      while( ALWAYS(z[iIn]) ){
        if( z[iIn]==q ){
          if( z[iIn+1]!=q ){
            /* Character iIn was the close quote. */
            iIn++;
            break;
          }else{
            /* Character iIn and iIn+1 form an escaped quote character. Skip
            ** the input cursor past both and copy a single quote character 
            ** to the output buffer. */
            iIn += 2;
            z[iOut++] = q;
          }
        }else{
          z[iOut++] = z[iIn++];
        }
      }
      z[iOut] = '\0';
    }
  }
}