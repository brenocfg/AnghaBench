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
 char** calloc (int,int) ; 
 int /*<<< orphan*/  cdio_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 

char **
_cdio_strsplit(const char str[], char delim) /* fixme -- non-reentrant */
{
  int n;
  char **strv = NULL;
  char *_str, *p;
  char _delim[2] = { 0, 0 };

  cdio_assert (str != NULL);

  _str = strdup(str);
  _delim[0] = delim;

  cdio_assert (_str != NULL);

  n = 1;
  p = _str;
  while(*p)
    if (*(p++) == delim)
      n++;

  strv = calloc (n+1, sizeof (char *));
  cdio_assert (strv != NULL);

  n = 0;
  while((p = strtok(n ? NULL : _str, _delim)) != NULL)
    strv[n++] = strdup(p);

  free(_str);

  return strv;
}