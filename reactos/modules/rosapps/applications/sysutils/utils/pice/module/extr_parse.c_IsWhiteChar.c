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
typedef  size_t USHORT ;
typedef  char* LPSTR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t PICE_strlen (char*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN IsWhiteChar(char c,LPSTR WhiteChars)
{
	USHORT lenWhiteChar = PICE_strlen(WhiteChars);
	USHORT i;
	for(i=0;i<lenWhiteChar;i++)
	{
		if(c == WhiteChars[i])
			return TRUE;
	}
	return FALSE;
}