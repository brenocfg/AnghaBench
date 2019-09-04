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
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  sdscatcolor (int /*<<< orphan*/ ,char*,size_t,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

sds sdsCatColorizedLdbReply(sds o, char *s, size_t len) {
    char *color = "white";

    if (strstr(s,"<debug>")) color = "bold";
    if (strstr(s,"<redis>")) color = "green";
    if (strstr(s,"<reply>")) color = "cyan";
    if (strstr(s,"<error>")) color = "red";
    if (strstr(s,"<hint>")) color = "bold";
    if (strstr(s,"<value>") || strstr(s,"<retval>")) color = "magenta";
    if (len > 4 && isdigit(s[3])) {
        if (s[1] == '>') color = "yellow"; /* Current line. */
        else if (s[2] == '#') color = "bold"; /* Break point. */
    }
    return sdscatcolor(o,s,len,color);
}