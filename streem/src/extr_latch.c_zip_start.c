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
struct zip_data {int /*<<< orphan*/ * latch; int /*<<< orphan*/  len; int /*<<< orphan*/  a; scalar_t__ i; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct zip_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  strm_ary_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_latch_receive (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_iter ; 

__attribute__((used)) static int
zip_start(strm_stream* strm, strm_value data)
{
  struct zip_data* z = strm->data;

  if (z) {
    z->i = 0;
    z->a = strm_ary_new(NULL, z->len);
    strm_latch_receive(z->latch[0], strm, zip_iter);
  }
  return STRM_OK;
}