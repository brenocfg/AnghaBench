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
 char* RemoteCompletionFunction (char const*,int,char) ; 

__attribute__((used)) static char *
RemoteDirCompletionFunction(const char *text, int state)
{
	char *cp;

	cp = RemoteCompletionFunction(text, state, 'd');
	return cp;
}