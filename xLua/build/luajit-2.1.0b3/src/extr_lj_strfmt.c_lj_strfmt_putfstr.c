#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; } ;
typedef  int SFormat ;
typedef  int /*<<< orphan*/  SBuf ;
typedef  scalar_t__ MSize ;
typedef  TYPE_1__ GCstr ;

/* Variables and functions */
 int STRFMT_F_LEFT ; 
 scalar_t__ STRFMT_PREC (int) ; 
 scalar_t__ STRFMT_WIDTH (int) ; 
 char* lj_buf_more (int /*<<< orphan*/ *,scalar_t__) ; 
 char* lj_buf_wmem (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strdata (TYPE_1__*) ; 

SBuf *lj_strfmt_putfstr(SBuf *sb, SFormat sf, GCstr *str)
{
  MSize len = str->len <= STRFMT_PREC(sf) ? str->len : STRFMT_PREC(sf);
  MSize width = STRFMT_WIDTH(sf);
  char *p = lj_buf_more(sb, width > len ? width : len);
  if ((sf & STRFMT_F_LEFT)) p = lj_buf_wmem(p, strdata(str), len);
  while (width-- > len) *p++ = ' ';
  if (!(sf & STRFMT_F_LEFT)) p = lj_buf_wmem(p, strdata(str), len);
  setsbufP(sb, p);
  return sb;
}