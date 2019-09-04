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
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

char *
next_arg(char *src, char needle)
{
	char *nextval;
	char *p;
	char *mvp = 0;

	/* EOS */
	if (*src == (char) 0x00)
		return 0;

	p = src;
	/*  skip escaped needles */
	while ((nextval = strchr(p, needle)))
	{
		mvp = nextval - 1;
		/* found backslashed needle */
		if (*mvp == '\\' && (mvp > src))
		{
			/* move string one to the left */
			while (*(mvp + 1) != (char) 0x00)
			{
				*mvp = *(mvp + 1);
				mvp++;
			}
			*mvp = (char) 0x00;
			p = nextval;
		}
		else
		{
			p = nextval + 1;
			break;
		}

	}

	/* more args available */
	if (nextval)
	{
		*nextval = (char) 0x00;
		return ++nextval;
	}

	/* no more args after this, jump to EOS */
	nextval = src + strlen(src);
	return nextval;
}