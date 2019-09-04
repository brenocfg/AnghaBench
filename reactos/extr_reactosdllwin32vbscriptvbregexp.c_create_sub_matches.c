#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int match_len; size_t paren_count; TYPE_2__* parens; int /*<<< orphan*/ * cp; } ;
typedef  TYPE_3__ match_state_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_12__ {int ref; scalar_t__* match; TYPE_3__* result; TYPE_1__ ISubMatches_iface; } ;
struct TYPE_10__ {int index; } ;
typedef  TYPE_4__ SubMatches ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubMatchesVtbl ; 
 int /*<<< orphan*/  SubMatches_tid ; 
 scalar_t__* heap_alloc (int) ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_4__*) ; 
 int /*<<< orphan*/  init_regexp_typeinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT create_sub_matches(DWORD pos, match_state_t *result, SubMatches **sub_matches)
{
    SubMatches *ret;
    DWORD i;
    HRESULT hres;

    hres = init_regexp_typeinfo(SubMatches_tid);
    if(FAILED(hres))
        return hres;

    ret = heap_alloc_zero(sizeof(*ret));
    if(!ret)
        return E_OUTOFMEMORY;

    ret->ISubMatches_iface.lpVtbl = &SubMatchesVtbl;

    ret->result = result;
    if(result) {
        ret->match = heap_alloc((result->match_len+1) * sizeof(WCHAR));
        if(!ret->match) {
            heap_free(ret);
            return E_OUTOFMEMORY;
        }
        memcpy(ret->match, result->cp-result->match_len, result->match_len*sizeof(WCHAR));
        ret->match[result->match_len] = 0;

        result->cp = NULL;
        for(i=0; i<result->paren_count; i++)
            if(result->parens[i].index != -1)
                result->parens[i].index -= pos;
    }else {
        ret->match = NULL;
    }

    ret->ref = 1;
    *sub_matches = ret;
    return hres;
}