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
 int EOF ; 
 int /*<<< orphan*/  FatalError (char*) ; 
 char SW ; 
 char* letP ; 
 char* strchr (char*,unsigned char) ; 
 char* xoptarg ; 
 scalar_t__ xopterr ; 
 int xoptind ; 

__attribute__((used)) static
int xgetopt(int argc, char *argv[], char *optionS)
{
	unsigned char ch;
	char *optP;

	if (SW == 0) {
		SW = '/';
	}

	if (argc > xoptind) {
		if (letP == NULL) {
			if ((letP = argv[xoptind]) == NULL ||
				*(letP++) != SW)  goto gopEOF;
			if (*letP == SW) {
				xoptind++;  goto gopEOF;
			}
		}
		if (0 == (ch = *(letP++))) {
			xoptind++;  goto gopEOF;
		}
		if (':' == ch  ||  (optP = strchr(optionS, ch)) == NULL)
			goto gopError;
		if (':' == *(++optP)) {
			xoptind++;
			if (0 == *letP) {
				if (argc <= xoptind)  goto  gopError;
				letP = argv[xoptind++];
			}
			xoptarg = letP;
			letP = NULL;
		} else {
			if (0 == *letP) {
				xoptind++;
				letP = NULL;
			}
			xoptarg = NULL;
		}
		return ch;
	}
gopEOF:
	xoptarg = letP = NULL;
	return EOF;

gopError:
	xoptarg = NULL;    
	if (xopterr)
		FatalError ("get command line option");
	return ('?');
}