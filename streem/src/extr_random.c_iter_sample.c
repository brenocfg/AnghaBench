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
typedef  size_t uint32_t ;
struct sample_data {size_t i; size_t len; void** samples; int /*<<< orphan*/  seed; } ;
typedef  void* strm_value ;
struct TYPE_3__ {struct sample_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 size_t xorshift128 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_sample(strm_stream* strm, strm_value data)
{
  struct sample_data* d = strm->data;
  uint32_t r;

  if (d->i < d->len) {
    d->samples[d->i++] = data;
    return STRM_OK;
  }
  r = xorshift128(d->seed)%(d->i);
  if (r < d->len) {
    d->samples[r] = data;
  }
  d->i++;
  return STRM_OK;
}