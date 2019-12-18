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
struct sort_data {int len; int capa; int /*<<< orphan*/ * buf; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct sort_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strm_funcall (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strm_nil_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_median(strm_stream* strm, strm_value data)
{
  struct sort_data* d = strm->data;

  if (d->len >= d->capa) {
    d->capa *= 2;
    d->buf = realloc(d->buf, sizeof(strm_value)*d->capa);
  }
  if (strm_nil_p(d->func)) {
    d->buf[d->len++] = data;
  }
  else if (strm_funcall(strm, d->func, 1, &data, &d->buf[d->len++]) == STRM_NG) {
    return STRM_NG;
  }
  return STRM_OK;
}