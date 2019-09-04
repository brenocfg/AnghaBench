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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* malloc (int) ; 
 int sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int write_if_change (char*,char*) ; 

int
main(int argc, char* argv[])
{
  int include_tests;
  unsigned int i;
  char* outbuf;
  char* s;
  char config[512];

  if (argc == 1)
    {
      fprintf(stderr, "Not enough arguments\n");
      return(1);
    }

  outbuf = malloc(256 * 1024);
  if (outbuf == NULL)
    {
      fprintf(stderr, "Out of memory 1\n");
      return(1);
    }

  s = outbuf;
  s = s + sprintf(s, "/* Automatically generated, ");
  s = s + sprintf(s, "Edit the Makefile to change configuration */\n");
  s = s + sprintf(s, "#ifndef __INCLUDE_CONFIG_H\n");
  s = s + sprintf(s, "#define __INCLUDE_CONFIG_H\n");
  strcpy(config, "");
  include_tests = 0;
  for (i = 2; i < argc; i++)
    {
      if (strcmp(argv[i], "REGTESTS") == 0)
        {
          include_tests = 1;
        }
      else
        {
          s = s + sprintf(s, "#ifndef %s\n", argv[i]);
          s = s + sprintf(s, "#define %s\n", argv[i]);
          s = s + sprintf(s, "#endif /* %s */\n", argv[i]);
        }
      strcat(config, argv[i]);
      if (i != (argc - 1))
	{
	  strcat(config, " ");
	}
    }
  if (include_tests)
    {
      s = s + sprintf(s, "#ifndef __ASM__\n");
      s = s + sprintf(s, "extern void PrepareTests();\n");
      s = s + sprintf(s, "#define PREPARE_TESTS PrepareTests();\n");
	  s = s + sprintf(s, "#endif /* __ASM__ */\n");
    }
  else
    {
      s = s + sprintf(s, "#define PREPARE_TESTS\n");
    }
  s = s + sprintf(s, "#define CONFIG \"%s\"\n", config);
  s = s + sprintf(s, "#endif /* __INCLUDE_CONFIG_H */\n");

  return(write_if_change(outbuf, argv[1]));
}