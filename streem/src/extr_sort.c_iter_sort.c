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
struct sort_data {int len; int capa; int /*<<< orphan*/ * buf; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_3__ {struct sort_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
iter_sort(strm_stream* strm, strm_value data)
{
  struct sort_data* d = strm->data;

  if (d->len >= d->capa) {
    d->capa *= 2;
    d->buf = realloc(d->buf, sizeof(strm_value)*d->capa);
  }
  d->buf[d->len++] = data;
  return STRM_OK;
}