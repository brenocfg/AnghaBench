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
struct _Locale_collate {int dummy; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int strcoll_l (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

int _Locale_strcmp(struct _Locale_collate * __loc,
                   const char *s1, size_t n1,
		   const char *s2, size_t n2) {
  int ret = 0;
  char buf1[64], buf2[64];
  while (n1 > 0 || n2 > 0) {
    size_t bufsize1 = n1 < 63 ? n1 : 63;
    size_t bufsize2 = n2 < 63 ? n2 : 63;
    strncpy(buf1, s1, bufsize1); buf1[bufsize1] = 0;
    strncpy(buf2, s2, bufsize2); buf2[bufsize2] = 0;

    ret = strcoll_l(buf1, buf2, (locale_t)__loc);
    if (ret != 0) return ret;
    s1 += bufsize1; n1 -= bufsize1;
    s2 += bufsize2; n2 -= bufsize2;
  }
  return ret;
}