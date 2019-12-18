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
struct TYPE_4__ {scalar_t__ arg; int /*<<< orphan*/  skip; } ;
typedef  TYPE_1__ exarg_T ;

/* Variables and functions */
 scalar_t__ ensure_ruby_initialized () ; 
 int /*<<< orphan*/  error_print (int) ; 
 int /*<<< orphan*/  rb_eval_string_protect (char*,int*) ; 
 scalar_t__ script_get (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  vim_free (char*) ; 

void ex_ruby(exarg_T *eap)
{
    int state;
    char *script = NULL;

    script = (char *)script_get(eap, eap->arg);
    if (!eap->skip && ensure_ruby_initialized())
    {
	if (script == NULL)
	    rb_eval_string_protect((char *)eap->arg, &state);
	else
	    rb_eval_string_protect(script, &state);
	if (state)
	    error_print(state);
    }
    vim_free(script);
}