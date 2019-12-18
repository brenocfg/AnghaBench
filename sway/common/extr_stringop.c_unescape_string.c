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
 int strlen (char*) ; 

int unescape_string(char *string) {
	/* TODO: More C string escapes */
	int len = strlen(string);
	int i;
	for (i = 0; string[i]; ++i) {
		if (string[i] == '\\') {
			switch (string[++i]) {
			case '0':
				string[i - 1] = '\0';
				return i - 1;
			case 'a':
				string[i - 1] = '\a';
				string[i] = '\0';
				break;
			case 'b':
				string[i - 1] = '\b';
				string[i] = '\0';
				break;
			case 'f':
				string[i - 1] = '\f';
				string[i] = '\0';
				break;
			case 'n':
				string[i - 1] = '\n';
				string[i] = '\0';
				break;
			case 'r':
				string[i - 1] = '\r';
				string[i] = '\0';
				break;
			case 't':
				string[i - 1] = '\t';
				string[i] = '\0';
				break;
			case 'v':
				string[i - 1] = '\v';
				string[i] = '\0';
				break;
			case '\\':
				string[i] = '\0';
				break;
			case '\'':
				string[i - 1] = '\'';
				string[i] = '\0';
				break;
			case '\"':
				string[i - 1] = '\"';
				string[i] = '\0';
				break;
			case '?':
				string[i - 1] = '?';
				string[i] = '\0';
				break;
			case 'x':
				{
					unsigned char c = 0;
					if (string[i+1] >= '0' && string[i+1] <= '9') {
						c = string[i+1] - '0';
						if (string[i+2] >= '0' && string[i+2] <= '9') {
							c *= 0x10;
							c += string[i+2] - '0';
							string[i+2] = '\0';
						}
						string[i+1] = '\0';
					}
					string[i] = '\0';
					string[i - 1] = c;
				}
			}
		}
	}
	// Shift characters over nullspaces
	int shift = 0;
	for (i = 0; i < len; ++i) {
		if (string[i] == 0) {
			shift++;
			continue;
		}
		string[i-shift] = string[i];
	}
	string[len - shift] = 0;
	return len - shift;
}