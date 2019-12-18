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
typedef  int /*<<< orphan*/  SBuf ;
typedef  int /*<<< orphan*/  MSize ;

/* Variables and functions */
 char* lj_buf_more (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* lj_buf_wmem (char*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,char*) ; 

SBuf *lj_buf_putmem(SBuf *sb, const void *q, MSize len)
{
  char *p = lj_buf_more(sb, len);
  p = lj_buf_wmem(p, q, len);
  setsbufP(sb, p);
  return sb;
}