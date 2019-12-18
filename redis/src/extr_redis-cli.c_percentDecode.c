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
typedef  int /*<<< orphan*/  sds ;

/* Variables and functions */
 char decodeHex (char,char) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  isHexChar (char) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  stderr ; 
 char tolower (char const) ; 

__attribute__((used)) static sds percentDecode(const char *pe, size_t len) {
    const char *end = pe + len;
    sds ret = sdsempty();
    const char *curr = pe;

    while (curr < end) {
        if (*curr == '%') {
            if ((end - curr) < 2) {
                fprintf(stderr, "Incomplete URI encoding\n");
                exit(1);
            }

            char h = tolower(*(++curr));
            char l = tolower(*(++curr));
            if (!isHexChar(h) || !isHexChar(l)) {
                fprintf(stderr, "Illegal character in URI encoding\n");
                exit(1);
            }
            char c = decodeHex(h, l);
            ret = sdscatlen(ret, &c, 1);
            curr++;
        } else {
            ret = sdscatlen(ret, curr++, 1);
        }
    }

    return ret;
}