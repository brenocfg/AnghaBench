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
 char NUL ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  get_part (char*,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,float) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
size_part(char *font, char *buf, int inPixels)
{
    int	    size;
    float   temp;

    *buf = '\0';

    if (inPixels)
    {
	get_part(font, 7, buf);
	if (*buf != NUL)
	{
	    size = atoi(buf);
	    sprintf(buf, "%3d", size);
	}
    }
    else
    {
	get_part(font, 8, buf);
	if (*buf != NUL)
	{
	    size = atoi(buf);
	    temp = (float)size / 10.0;
	    size = temp;
	    if (buf[strlen(buf) - 1] == '0')
		sprintf(buf, "%3d", size);
	    else
		sprintf(buf, "%4.1f", temp);
	}
    }
}