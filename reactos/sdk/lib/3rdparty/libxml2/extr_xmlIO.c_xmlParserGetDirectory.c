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
 scalar_t__ IS_XMLPGD_SEP (char) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 scalar_t__ xmlInputCallbackInitialized ; 
 char* xmlMemStrdup (char*) ; 
 int /*<<< orphan*/  xmlRegisterDefaultInputCallbacks () ; 

char *
xmlParserGetDirectory(const char *filename) {
    char *ret = NULL;
    char dir[1024];
    char *cur;

#ifdef _WIN32_WCE  /* easy way by now ... wince does not have dirs! */
    return NULL;
#endif

    if (xmlInputCallbackInitialized == 0)
	xmlRegisterDefaultInputCallbacks();

    if (filename == NULL) return(NULL);

#if defined(_WIN32) && !defined(__CYGWIN__)
#   define IS_XMLPGD_SEP(ch) ((ch=='/')||(ch=='\\'))
#else
#   define IS_XMLPGD_SEP(ch) (ch=='/')
#endif

    strncpy(dir, filename, 1023);
    dir[1023] = 0;
    cur = &dir[strlen(dir)];
    while (cur > dir) {
         if (IS_XMLPGD_SEP(*cur)) break;
	 cur --;
    }
    if (IS_XMLPGD_SEP(*cur)) {
        if (cur == dir) dir[1] = 0;
	else *cur = 0;
	ret = xmlMemStrdup(dir);
    } else {
        if (getcwd(dir, 1024) != NULL) {
	    dir[1023] = 0;
	    ret = xmlMemStrdup(dir);
	}
    }
    return(ret);
#undef IS_XMLPGD_SEP
}