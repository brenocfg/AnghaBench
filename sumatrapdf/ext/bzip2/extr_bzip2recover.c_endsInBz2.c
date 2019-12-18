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
typedef  int Int32 ;
typedef  char Char ;
typedef  int Bool ;

/* Variables and functions */
 int False ; 
 int strlen (char*) ; 

__attribute__((used)) static Bool endsInBz2 ( Char* name )
{
   Int32 n = strlen ( name );
   if (n <= 4) return False;
   return
      (name[n-4] == '.' &&
       name[n-3] == 'b' &&
       name[n-2] == 'z' &&
       name[n-1] == '2');
}