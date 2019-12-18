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
 char* dup_basename (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void write_import(FILE *header, const char *fname)
{
  char *hname, *p;

  hname = dup_basename(fname, ".idl");
  p = hname + strlen(hname) - 2;
  if (p <= hname || strcmp( p, ".h" )) strcat(hname, ".h");

  fprintf(header, "#include <%s>\n", hname);
  free(hname);
}