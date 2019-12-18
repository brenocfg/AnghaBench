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
struct bar_data {int col; int max; int dlen; scalar_t__* data; scalar_t__ row; scalar_t__ llen; scalar_t__ offset; } ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 scalar_t__ get_winsize (scalar_t__*,int*) ; 
 scalar_t__* malloc (int) ; 
 int /*<<< orphan*/  show_title (struct bar_data*) ; 

__attribute__((used)) static int
init_bar(struct bar_data* d)
{
  if (get_winsize(&d->row, &d->col))
    return STRM_NG;
  d->max = 1;
  d->offset = 0;
  d->dlen = d->col-6;
  d->llen = d->row-3;
  d->data = malloc((d->dlen)*sizeof(double));
  for (int i=0;i<d->dlen;i++) {
    d->data[i] = 0;
  }
  show_title(d);
  return STRM_OK;
}