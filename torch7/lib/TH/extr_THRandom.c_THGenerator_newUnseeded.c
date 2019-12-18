#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int left; scalar_t__ normal_is_valid; scalar_t__ seeded; } ;
typedef  TYPE_1__ THGenerator ;

/* Variables and functions */
 TYPE_1__* THAlloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static THGenerator* THGenerator_newUnseeded()
{
  THGenerator *self = THAlloc(sizeof(THGenerator));
  memset(self, 0, sizeof(THGenerator));
  self->left = 1;
  self->seeded = 0;
  self->normal_is_valid = 0;
  return self;
}