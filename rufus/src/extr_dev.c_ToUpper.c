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
 size_t safe_strlen (char*) ; 
 scalar_t__ toupper (char) ; 

__attribute__((used)) static __inline void ToUpper(char* str)
{
	size_t i;
	for (i = 0; i < safe_strlen(str); i++)
		str[i] = (char)toupper(str[i]);
}