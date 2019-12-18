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
typedef  enum criteria_token { ____Placeholder_criteria_token } criteria_token ;

/* Variables and functions */
 int T_APP_ID ; 
 int T_CLASS ; 
 int T_CON_ID ; 
 int T_CON_MARK ; 
 int T_FLOATING ; 
 int T_ID ; 
 int T_INSTANCE ; 
 int T_INVALID ; 
 int T_SHELL ; 
 int T_TILING ; 
 int T_TITLE ; 
 int T_URGENT ; 
 int T_WINDOW_ROLE ; 
 int T_WINDOW_TYPE ; 
 int T_WORKSPACE ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static enum criteria_token token_from_name(char *name) {
	if (strcmp(name, "app_id") == 0) {
		return T_APP_ID;
	} else if (strcmp(name, "con_id") == 0) {
		return T_CON_ID;
	} else if (strcmp(name, "con_mark") == 0) {
		return T_CON_MARK;
#if HAVE_XWAYLAND
	} else if (strcmp(name, "class") == 0) {
		return T_CLASS;
	} else if (strcmp(name, "id") == 0) {
		return T_ID;
	} else if (strcmp(name, "instance") == 0) {
		return T_INSTANCE;
	} else if (strcmp(name, "window_role") == 0) {
		return T_WINDOW_ROLE;
	} else if (strcmp(name, "window_type") == 0) {
		return T_WINDOW_TYPE;
#endif
	} else if (strcmp(name, "shell") == 0) {
		return T_SHELL;
	} else if (strcmp(name, "title") == 0) {
		return T_TITLE;
	} else if (strcmp(name, "urgent") == 0) {
		return T_URGENT;
	} else if (strcmp(name, "workspace") == 0) {
		return T_WORKSPACE;
	} else if (strcmp(name, "tiling") == 0) {
		return T_TILING;
	} else if (strcmp(name, "floating") == 0) {
		return T_FLOATING;
	}
	return T_INVALID;
}