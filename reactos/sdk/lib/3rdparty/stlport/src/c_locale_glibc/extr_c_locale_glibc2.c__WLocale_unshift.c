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
struct _Locale_codecvt {int dummy; } ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */

size_t _WLocale_unshift(struct _Locale_codecvt *lcodecvt,
                        mbstate_t *st,
                        char *buf, size_t n, char ** next)
{ *next = buf; return 0; }