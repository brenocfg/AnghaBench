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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 char* error ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ftello (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  readArgc (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  readString (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  zfree (char*) ; 

off_t process(FILE *fp) {
    long argc;
    off_t pos = 0;
    int i, multi = 0;
    char *str;

    while(1) {
        if (!multi) pos = ftello(fp);
        if (!readArgc(fp, &argc)) break;

        for (i = 0; i < argc; i++) {
            if (!readString(fp,&str)) break;
            if (i == 0) {
                if (strcasecmp(str, "multi") == 0) {
                    if (multi++) {
                        ERROR("Unexpected MULTI");
                        break;
                    }
                } else if (strcasecmp(str, "exec") == 0) {
                    if (--multi) {
                        ERROR("Unexpected EXEC");
                        break;
                    }
                }
            }
            zfree(str);
        }

        /* Stop if the loop did not finish */
        if (i < argc) {
            if (str) zfree(str);
            break;
        }
    }

    if (feof(fp) && multi && strlen(error) == 0) {
        ERROR("Reached EOF before reading EXEC for MULTI");
    }
    if (strlen(error) > 0) {
        printf("%s\n", error);
    }
    return pos;
}