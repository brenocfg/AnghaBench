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
 int /*<<< orphan*/  isColorTerm () ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  sdscatlen (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

sds sdscatcolor(sds o, char *s, size_t len, char *color) {
    if (!isColorTerm()) return sdscatlen(o,s,len);

    int bold = strstr(color,"bold") != NULL;
    int ccode = 37; /* Defaults to white. */
    if (strstr(color,"red")) ccode = 31;
    else if (strstr(color,"green")) ccode = 32;
    else if (strstr(color,"yellow")) ccode = 33;
    else if (strstr(color,"blue")) ccode = 34;
    else if (strstr(color,"magenta")) ccode = 35;
    else if (strstr(color,"cyan")) ccode = 36;
    else if (strstr(color,"white")) ccode = 37;

    o = sdscatfmt(o,"\033[%i;%i;49m",bold,ccode);
    o = sdscatlen(o,s,len);
    o = sdscat(o,"\033[0m");
    return o;
}