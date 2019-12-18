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
struct TYPE_4__ {int /*<<< orphan*/  status_; } ;
typedef  TYPE_1__ WebPWorker ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void Init(WebPWorker* const worker) {
  memset(worker, 0, sizeof(*worker));
  worker->status_ = NOT_OK;
}