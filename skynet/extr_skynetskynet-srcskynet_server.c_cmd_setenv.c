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
struct skynet_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skynet_setenv (char*,char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static const char *
cmd_setenv(struct skynet_context * context, const char * param) {
	size_t sz = strlen(param);
	char key[sz+1];
	int i;
	for (i=0;param[i] != ' ' && param[i];i++) {
		key[i] = param[i];
	}
	if (param[i] == '\0')
		return NULL;

	key[i] = '\0';
	param += i+1;
	
	skynet_setenv(key,param);
	return NULL;
}