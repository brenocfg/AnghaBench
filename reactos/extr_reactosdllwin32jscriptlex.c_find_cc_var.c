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
struct TYPE_5__ {unsigned int name_len; int /*<<< orphan*/  name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ cc_var_t ;
struct TYPE_6__ {TYPE_1__* vars; } ;
typedef  TYPE_2__ cc_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static cc_var_t *find_cc_var(cc_ctx_t *cc, const WCHAR *name, unsigned name_len)
{
    cc_var_t *iter;

    for(iter = cc->vars; iter; iter = iter->next) {
        if(iter->name_len == name_len && !memcmp(iter->name, name, name_len*sizeof(WCHAR)))
            return iter;
    }

    return NULL;
}