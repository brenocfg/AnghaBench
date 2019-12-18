#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sortby_value {int dummy; } ;
struct sortby_data {int len; int capa; TYPE_2__* buf; int /*<<< orphan*/  func; int /*<<< orphan*/  strm; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_5__ {struct sortby_data* data; } ;
typedef  TYPE_1__ strm_stream ;
struct TYPE_6__ {int /*<<< orphan*/  v; int /*<<< orphan*/  o; } ;

/* Variables and functions */
 scalar_t__ STRM_NG ; 
 int STRM_OK ; 
 TYPE_2__* realloc (TYPE_2__*,int) ; 
 scalar_t__ strm_funcall (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
iter_sortby(strm_stream* strm, strm_value data)
{
  struct sortby_data* d = strm->data;

  if (d->len >= d->capa) {
    d->capa *= 2;
    d->buf = realloc(d->buf, sizeof(struct sortby_value)*d->capa);
  }
  d->buf[d->len].o = data;
  if (strm_funcall(d->strm, d->func, 1, &data, &d->buf[d->len].v) == STRM_NG) {
    return STRM_NG;;
  }
  d->len++;
  return STRM_OK;
}