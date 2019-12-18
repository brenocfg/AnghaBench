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
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  PICE_memcpy (char*,char*,scalar_t__) ; 
 scalar_t__ PICE_strlen (char*) ; 

char* PICE_strcpy(char* s1,char* s2)
{
	ULONG len2 =  PICE_strlen(s2);

	PICE_memcpy(s1,s2,len2+1);

	return s1;
}