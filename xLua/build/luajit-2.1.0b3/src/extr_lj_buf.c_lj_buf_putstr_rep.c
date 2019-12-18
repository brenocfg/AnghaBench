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
typedef  scalar_t__ uint64_t ;
typedef  char uint32_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_4__ {scalar_t__ len; } ;
typedef  int /*<<< orphan*/  SBuf ;
typedef  scalar_t__ MSize ;
typedef  TYPE_1__ GCstr ;

/* Variables and functions */
 scalar_t__ LJ_MAX_STR ; 
 scalar_t__ LJ_UNLIKELY (int) ; 
 char* lj_buf_more (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  lj_err_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbufL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsbufP (int /*<<< orphan*/ *,char*) ; 
 char* strdata (TYPE_1__*) ; 

SBuf *lj_buf_putstr_rep(SBuf *sb, GCstr *s, int32_t rep)
{
  MSize len = s->len;
  if (rep > 0 && len) {
    uint64_t tlen = (uint64_t)rep * len;
    char *p;
    if (LJ_UNLIKELY(tlen > LJ_MAX_STR))
      lj_err_mem(sbufL(sb));
    p = lj_buf_more(sb, (MSize)tlen);
    if (len == 1) {  /* Optimize a common case. */
      uint32_t c = strdata(s)[0];
      do { *p++ = c; } while (--rep > 0);
    } else {
      const char *e = strdata(s) + len;
      do {
	const char *q = strdata(s);
	do { *p++ = *q++; } while (q < e);
      } while (--rep > 0);
    }
    setsbufP(sb, p);
  }
  return sb;
}