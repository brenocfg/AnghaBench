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
struct sample_data {size_t len; int /*<<< orphan*/ * samples; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct sample_data* data; } ;
typedef  TYPE_1__ strm_stream ;
typedef  size_t strm_int ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct sample_data*) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
finish_sample(strm_stream* strm, strm_value data)
{
  struct sample_data* d = strm->data;
  strm_int i, len=d->len;

  for (i=0; i<len; i++) {
    strm_emit(strm, d->samples[i], NULL);
  }
  free(d);
  return STRM_OK;
}