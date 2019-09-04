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
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  LOCK ; 
 int /*<<< orphan*/  UNLOCK ; 
 char** __environ ; 
 int /*<<< orphan*/  __set_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** last_environ ; 
 scalar_t__ malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 scalar_t__ realloc (char**,size_t) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,size_t const) ; 

int
compat_setenv (const char *name, const char *value, int replace)
{
  register char **ep = 0;
  register size_t size;
  const size_t namelen = strlen (name);
  const size_t vallen = strlen (value) + 1;

  LOCK;

  size = 0;
  if (__environ != NULL)
    {
      for (ep = __environ; *ep != NULL; ++ep)
	if (!strncmp (*ep, name, namelen) && (*ep)[namelen] == '=')
	  break;
	else
	  ++size;
    }

  if (__environ == NULL || *ep == NULL)
    {
      char **new_environ;
      if (__environ == last_environ && __environ != NULL)
	/* We allocated this space; we can extend it.  */
	new_environ = (char **) realloc (last_environ,
					 (size + 2) * sizeof (char *));
      else
	new_environ = (char **) malloc ((size + 2) * sizeof (char *));

      if (new_environ == NULL)
	{
	  UNLOCK;
	  return -1;
	}

      new_environ[size] = (char *) malloc (namelen + 1 + vallen);
      if (new_environ[size] == NULL)
	{
	  free ((char *) new_environ);
	  __set_errno (ENOMEM);
	  UNLOCK;
	  return -1;
	}

      if (__environ != last_environ)
	memcpy ((char *) new_environ, (char *) __environ,
		size * sizeof (char *));

      memcpy (new_environ[size], name, namelen);
      new_environ[size][namelen] = '=';
      memcpy (&new_environ[size][namelen + 1], value, vallen);

      new_environ[size + 1] = NULL;

      last_environ = __environ = new_environ;
    }
  else if (replace)
    {
      size_t len = strlen (*ep);
      if (len + 1 < namelen + 1 + vallen)
	{
	  /* The existing string is too short; malloc a new one.  */
	  char *new_string = (char *) malloc (namelen + 1 + vallen);
	  if (new_string == NULL)
	    {
	      UNLOCK;
	      return -1;
	    }
	  *ep = new_string;
	}
      memcpy (*ep, name, namelen);
      (*ep)[namelen] = '=';
      memcpy (&(*ep)[namelen + 1], value, vallen);
    }

  UNLOCK;

  return 0;
}