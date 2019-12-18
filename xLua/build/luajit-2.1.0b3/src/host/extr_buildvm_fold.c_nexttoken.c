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
typedef  size_t uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 char** ir_names ; 
 char** ircall_names ; 
 char** irfield_names ; 
 char** irfpm_names ; 
 char** irt_names ; 
 int lineno ; 
 int /*<<< orphan*/  stderr ; 
 void* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static uint32_t nexttoken(char **pp, int allowlit, int allowany)
{
  char *p = *pp;
  if (p) {
    uint32_t i;
    char *q = strchr(p, ' ');
    if (q) *q++ = '\0';
    *pp = q;
    if (allowlit && !strncmp(p, "IRFPM_", 6)) {
      for (i = 0; irfpm_names[i]; i++)
	if (!strcmp(irfpm_names[i], p+6))
	  return i;
    } else if (allowlit && !strncmp(p, "IRFL_", 5)) {
      for (i = 0; irfield_names[i]; i++)
	if (!strcmp(irfield_names[i], p+5))
	  return i;
    } else if (allowlit && !strncmp(p, "IRCALL_", 7)) {
      for (i = 0; ircall_names[i]; i++)
	if (!strcmp(ircall_names[i], p+7))
	  return i;
    } else if (allowlit && !strncmp(p, "IRCONV_", 7)) {
      for (i = 0; irt_names[i]; i++) {
	const char *r = strchr(p+7, '_');
	if (r && !strncmp(irt_names[i], p+7, r-(p+7))) {
	  uint32_t j;
	  for (j = 0; irt_names[j]; j++)
	    if (!strcmp(irt_names[j], r+1))
	      return (i << 5) + j;
	}
      }
    } else if (allowlit && *p >= '0' && *p <= '9') {
      for (i = 0; *p >= '0' && *p <= '9'; p++)
	i = i*10 + (*p - '0');
      if (*p == '\0')
	return i;
    } else if (allowany && !strcmp("any", p)) {
      return allowany;
    } else {
      for (i = 0; ir_names[i]; i++)
	if (!strcmp(ir_names[i], p))
	  return i;
    }
    fprintf(stderr, "Error: bad fold definition token \"%s\" at line %d\n", p, lineno);
    exit(1);
  }
  return 0;
}