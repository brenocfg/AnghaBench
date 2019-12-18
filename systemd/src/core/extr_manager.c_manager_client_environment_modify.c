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
struct TYPE_4__ {char** client_environment; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char** sanitize_environment (char**) ; 
 char** strv_env_delete (char**,int,char**) ; 
 char** strv_env_merge (int,char**,char**) ; 
 int /*<<< orphan*/  strv_free (char**) ; 
 scalar_t__ strv_isempty (char**) ; 

int manager_client_environment_modify(
                Manager *m,
                char **minus,
                char **plus) {

        char **a = NULL, **b = NULL, **l;

        assert(m);

        if (strv_isempty(minus) && strv_isempty(plus))
                return 0;

        l = m->client_environment;

        if (!strv_isempty(minus)) {
                a = strv_env_delete(l, 1, minus);
                if (!a)
                        return -ENOMEM;

                l = a;
        }

        if (!strv_isempty(plus)) {
                b = strv_env_merge(2, l, plus);
                if (!b) {
                        strv_free(a);
                        return -ENOMEM;
                }

                l = b;
        }

        if (m->client_environment != l)
                strv_free(m->client_environment);

        if (a != l)
                strv_free(a);
        if (b != l)
                strv_free(b);

        m->client_environment = sanitize_environment(l);
        return 0;
}