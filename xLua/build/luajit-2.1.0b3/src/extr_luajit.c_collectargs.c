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
 int FLAGS_EXEC ; 
 int FLAGS_INTERACTIVE ; 
 int FLAGS_NOENV ; 
 int FLAGS_OPTION ; 
 int FLAGS_VERSION ; 
 int /*<<< orphan*/  notail (char*) ; 

__attribute__((used)) static int collectargs(char **argv, int *flags)
{
  int i;
  for (i = 1; argv[i] != NULL; i++) {
    if (argv[i][0] != '-')  /* Not an option? */
      return i;
    switch (argv[i][1]) {  /* Check option. */
    case '-':
      notail(argv[i]);
      return i+1;
    case '\0':
      return i;
    case 'i':
      notail(argv[i]);
      *flags |= FLAGS_INTERACTIVE;
      /* fallthrough */
    case 'v':
      notail(argv[i]);
      *flags |= FLAGS_VERSION;
      break;
    case 'e':
      *flags |= FLAGS_EXEC;
    case 'j':  /* LuaJIT extension */
    case 'l':
      *flags |= FLAGS_OPTION;
      if (argv[i][2] == '\0') {
	i++;
	if (argv[i] == NULL) return -1;
      }
      break;
    case 'O': break;  /* LuaJIT extension */
    case 'b':  /* LuaJIT extension */
      if (*flags) return -1;
      *flags |= FLAGS_EXEC;
      return i+1;
    case 'E':
      *flags |= FLAGS_NOENV;
      break;
    default: return -1;  /* invalid option */
    }
  }
  return i;
}