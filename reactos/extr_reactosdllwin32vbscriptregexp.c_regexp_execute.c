#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  parenCount; } ;
typedef  TYPE_1__ regexp_t ;
struct TYPE_12__ {int match_len; int /*<<< orphan*/  paren_count; int /*<<< orphan*/  const* cp; } ;
typedef  TYPE_2__ match_state_t ;
typedef  int /*<<< orphan*/  heap_pool_t ;
typedef  int /*<<< orphan*/  const WCHAR ;
struct TYPE_13__ {int start; int skipped; int /*<<< orphan*/  ok; int /*<<< orphan*/ * pool; int /*<<< orphan*/  const* cpend; int /*<<< orphan*/  const* cpbegin; } ;
typedef  TYPE_3__ REGlobalData ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitMatch (TYPE_1__*,void*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__* MatchRegExp (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_pool_mark (int /*<<< orphan*/ *) ; 

HRESULT regexp_execute(regexp_t *regexp, void *cx, heap_pool_t *pool,
        const WCHAR *str, DWORD str_len, match_state_t *result)
{
    match_state_t *res;
    REGlobalData gData;
    heap_pool_t *mark = heap_pool_mark(pool);
    const WCHAR *str_beg = result->cp;
    HRESULT hres;

    assert(result->cp != NULL);

    gData.cpbegin = str;
    gData.cpend = str+str_len;
    gData.start = result->cp-str;
    gData.skipped = 0;
    gData.pool = pool;

    hres = InitMatch(regexp, cx, pool, &gData);
    if(FAILED(hres)) {
        WARN("InitMatch failed\n");
        heap_pool_clear(mark);
        return hres;
    }

    res = MatchRegExp(&gData, result);
    heap_pool_clear(mark);
    if(!gData.ok) {
        WARN("MatchRegExp failed\n");
        return E_FAIL;
    }

    if(!res) {
        result->match_len = 0;
        return S_FALSE;
    }

    result->match_len = (result->cp-str_beg) - gData.skipped;
    result->paren_count = regexp->parenCount;
    return S_OK;
}