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
struct bar_data {int tlen; void* title; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int strm_int ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  fin_bar ; 
 int init_bar (struct bar_data*) ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  iter_bar ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 scalar_t__ refcnt ; 
 int /*<<< orphan*/  sigupdate ; 
 int /*<<< orphan*/  strm_atomic_inc (scalar_t__) ; 
 int /*<<< orphan*/  strm_consumer ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,char**,int*) ; 
 int /*<<< orphan*/  strm_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winch ; 

__attribute__((used)) static int
exec_bgraph(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct bar_data* d;
  char* title = NULL;
  strm_int tlen = 0;

  strm_get_args(strm, argc, args, "|s", &title, &tlen);
  d = malloc(sizeof(struct bar_data));
  if (!d) return STRM_NG;
  d->title = malloc(tlen);
  memcpy((void*)d->title, title, tlen);
  d->tlen = tlen;
  if (refcnt == 0) {
    strm_atomic_inc(refcnt);
    strm_signal(SIGWINCH, sigupdate, &winch);
    strm_signal(SIGINT, sigupdate, &interrupt);
  }
  if (init_bar(d) == STRM_NG) return STRM_NG;
  *ret = strm_stream_value(strm_stream_new(strm_consumer, iter_bar,
                                           fin_bar, (void*)d));
  return STRM_OK;
}