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
 int MEGABYTES ; 
 int /*<<< orphan*/  N_BUF ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int random () ; 
 int /*<<< orphan*/  setbuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srandom (int) ; 
 int /*<<< orphan*/  stdout ; 

int main ( int argc, char** argv )
{
   int ii, kk, p;
   srandom(1);
   setbuffer ( stdout, buf, N_BUF );
   for (kk = 0; kk < MEGABYTES * 515; kk+=3) {
      p = 25+random()%50;
      for (ii = 0; ii < p; ii++)
         printf ( "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" );
      for (ii = 0; ii < p-1; ii++)
         printf ( "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" );
      for (ii = 0; ii < p+1; ii++)
         printf ( "ccccccccccccccccccccccccccccccccccccc" );
   }
   fflush(stdout);
   return 0;
}