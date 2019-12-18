#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cFileName; } ;
typedef  TYPE_1__ WIN32_FIND_DATA ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  FindClose (scalar_t__) ; 
 scalar_t__ FindFirstFile (char*,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ toupper (char) ; 

void ConvertPathCase(char *src, char *dst)
{
	HANDLE hFind;
	WIN32_FIND_DATA find;
	char *p;

	p = dst;

	if (*src == '\"') {
		src++;
	}

	if (*(src + strlen(src) - 1) == '\"') {
		*(src + strlen(src) - 1) = '\0';
	}

	//
	//	handle drive / remote server name
	//
	if (isalpha(*src) && *(src + 1) == ':') {

		//	drive name

		*(p++) = (char)toupper(*src);
		strcpy(p++, ":\\");

		src += 2;
	}
	else if (*src == '\\' || *src == '/') {

		//	absolute path or remote name

		if ((*(src + 1) == '\\' || *(src + 1) == '/') &&
			*(src + 2) && *(src + 2) != '\\' && *(src + 2) != '/') {

			//	remote path

			*(p++) = '\\';
			*(p++) = '\\';
			src += 2;

			while (*src && *src != '\\' && *src != '/') {
				*(p++) = *(src++);
			}
		}

		strcpy(p, "\\");
	}
	else {
		*p = '\0';
	}

	//	skip redundant '\'

	while (*src == '\\' || *src == '/') {
		src++;
	}

	//	process the path

	while (*src) {

		char *q = src;

		//	separate the next part

		while (*q && *q != '\\' && *q != '/') {
			q++;
		}

		if ((q - src) == 2 && !strncmp(src, "..", 2)) {
			//	parent dir - copy as it is
			if (p != dst) {
				*p++ = '\\';
			}

			strcpy(p, "..");
			p += 2;
		}
		else if ((q - src) > 1 || *src != '.') {
			//	path name other than "."
			if (p != dst) {
				*(p++) = '\\';
			}

			strncpy(p, src, (q - src));
			*(p + (q - src)) = '\0';

			hFind = FindFirstFile(dst, &find);

			if (hFind == INVALID_HANDLE_VALUE) {
				strcpy(p, src);
				break;
			}

			FindClose(hFind);

			strcpy(p, find.cFileName);
			p += strlen(p);
		}

		//	skip trailing '\'s

		while (*q == '\\' || *q == '/') {
			q++;
		}

		src = q;
	}
}