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
 scalar_t__* TGZsuffix ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* prog ; 
 int /*<<< orphan*/  stderr ; 

void TGZnotfound (const char *arcname)
{
  int i;

  fprintf(stderr,"%s: Couldn't find ",prog);
  for (i=0;TGZsuffix[i];i++)
    fprintf(stderr,(TGZsuffix[i+1]) ? "%s%s, " : "or %s%s\n",
            arcname,
            TGZsuffix[i]);
  exit(1);
}