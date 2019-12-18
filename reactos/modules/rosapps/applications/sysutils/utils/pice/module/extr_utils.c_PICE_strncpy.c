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
typedef  int ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  PICE_memcpy (char*,char*,int) ; 
 int PICE_strlen (char*) ; 

char* PICE_strncpy(char* s1,char* s2,int len)
{
	ULONG len2 =  PICE_strlen(s2);

	if(len<len2)
		PICE_memcpy(s1,s2,len2+1);
	else
		PICE_memcpy(s1,s2,len);

	return s1;
}