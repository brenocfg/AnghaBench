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
struct TYPE_3__ {char* pb; char* buf; int needsp; scalar_t__ ok; } ;
typedef  int MSize ;
typedef  TYPE_1__ CTRepr ;

/* Variables and functions */

__attribute__((used)) static void ctype_prepstr(CTRepr *ctr, const char *str, MSize len)
{
  char *p = ctr->pb;
  if (ctr->buf + len+1 > p) { ctr->ok = 0; return; }
  if (ctr->needsp) *--p = ' ';
  ctr->needsp = 1;
  p -= len;
  while (len-- > 0) p[len] = str[len];
  ctr->pb = p;
}