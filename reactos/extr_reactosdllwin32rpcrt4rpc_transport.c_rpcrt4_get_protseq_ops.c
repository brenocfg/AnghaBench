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
struct protseq_ops {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct protseq_ops const*) ; 
 struct protseq_ops const* protseq_list ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

const struct protseq_ops *rpcrt4_get_protseq_ops(const char *protseq)
{
  unsigned int i;
  for(i = 0; i < ARRAY_SIZE(protseq_list); i++)
    if (!strcmp(protseq_list[i].name, protseq))
      return &protseq_list[i];
  return NULL;
}