#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  length_flags; } ;
struct TYPE_8__ {TYPE_3__ str; TYPE_3__* right; TYPE_3__* left; } ;
typedef  TYPE_1__ jsstr_rope_t ;
typedef  scalar_t__ WCHAR ;
struct TYPE_10__ {scalar_t__ const* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  JSSTR_FLAG_FLAT ; 
 scalar_t__* heap_alloc (int) ; 
 TYPE_6__* jsstr_as_heap (TYPE_3__*) ; 
 int /*<<< orphan*/  jsstr_flush (TYPE_3__*,scalar_t__*) ; 
 size_t jsstr_length (TYPE_3__*) ; 
 int /*<<< orphan*/  jsstr_release (TYPE_3__*) ; 

const WCHAR *jsstr_rope_flatten(jsstr_rope_t *str)
{
    WCHAR *buf;

    buf = heap_alloc((jsstr_length(&str->str)+1) * sizeof(WCHAR));
    if(!buf)
        return NULL;

    jsstr_flush(str->left, buf);
    jsstr_flush(str->right, buf+jsstr_length(str->left));
    buf[jsstr_length(&str->str)] = 0;

    /* Trasform to heap string */
    jsstr_release(str->left);
    jsstr_release(str->right);
    str->str.length_flags |= JSSTR_FLAG_FLAT;
    return jsstr_as_heap(&str->str)->buf = buf;
}