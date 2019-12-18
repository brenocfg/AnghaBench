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
struct TYPE_3__ {int* y_left_; int* u_left_; int* v_left_; scalar_t__ y_; int left_derr_; int /*<<< orphan*/ * top_derr_; scalar_t__* left_nz_; } ;
typedef  TYPE_1__ VP8EncIterator ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static void InitLeft(VP8EncIterator* const it) {
  it->y_left_[-1] = it->u_left_[-1] = it->v_left_[-1] =
      (it->y_ > 0) ? 129 : 127;
  memset(it->y_left_, 129, 16);
  memset(it->u_left_, 129, 8);
  memset(it->v_left_, 129, 8);
  it->left_nz_[8] = 0;
  if (it->top_derr_ != NULL) {
    memset(&it->left_derr_, 0, sizeof(it->left_derr_));
  }
}