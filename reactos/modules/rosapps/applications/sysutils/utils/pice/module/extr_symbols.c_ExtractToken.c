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
typedef  scalar_t__* LPSTR ;

/* Variables and functions */
 scalar_t__ PICE_isalpha (char) ; 
 scalar_t__ PICE_isdigit (char) ; 
 char* pExpression ; 
 size_t ulIndex ; 

void ExtractToken(LPSTR pStringToken)
{
	while(PICE_isalpha(pExpression[ulIndex]) || PICE_isdigit(pExpression[ulIndex]) || pExpression[ulIndex]=='_')
	{
		*pStringToken++=pExpression[ulIndex++];
		*pStringToken=0;
	}
}