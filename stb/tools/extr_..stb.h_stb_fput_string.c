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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stb_fput_varlenu (int /*<<< orphan*/ *,unsigned int) ; 
 size_t strlen (char*) ; 

void stb_fput_string(FILE *f, char *s)
{
   size_t len = strlen(s);
   stb_fput_varlenu(f, (unsigned int) len);
   fwrite(s, 1, len, f);
}