#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* script; } ;
typedef  TYPE_2__ parser_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/ * vars; } ;
typedef  TYPE_3__ cc_ctx_t ;
typedef  char WCHAR ;
struct TYPE_9__ {TYPE_3__* cc; } ;
typedef  double DOUBLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ JSCRIPT_BUILD_VERSION ; 
 scalar_t__ JSCRIPT_MAJOR_VERSION ; 
 scalar_t__ JSCRIPT_MINOR_VERSION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ccval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccval_num (scalar_t__) ; 
 TYPE_3__* heap_alloc (int) ; 
 int /*<<< orphan*/  lex_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_cc_var (TYPE_3__*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_cc (TYPE_3__*) ; 

__attribute__((used)) static BOOL init_cc(parser_ctx_t *ctx)
{
    cc_ctx_t *cc;

    static const WCHAR _win32W[] = {'_','w','i','n','3','2',0};
    static const WCHAR _win64W[] = {'_','w','i','n','6','4',0};
    static const WCHAR _x86W[] = {'_','x','8','6',0};
    static const WCHAR _amd64W[] = {'_','a','m','d','6','4',0};
    static const WCHAR _jscriptW[] = {'_','j','s','c','r','i','p','t',0};
    static const WCHAR _jscript_buildW[] = {'_','j','s','c','r','i','p','t','_','b','u','i','l','d',0};
    static const WCHAR _jscript_versionW[] = {'_','j','s','c','r','i','p','t','_','v','e','r','s','i','o','n',0};

    if(ctx->script->cc)
        return TRUE;

    cc = heap_alloc(sizeof(cc_ctx_t));
    if(!cc) {
        lex_error(ctx, E_OUTOFMEMORY);
        return FALSE;
    }

    cc->vars = NULL;

    if(!new_cc_var(cc, _jscriptW, -1, ccval_bool(TRUE))
       || !new_cc_var(cc, sizeof(void*) == 8 ? _win64W : _win32W, -1, ccval_bool(TRUE))
       || !new_cc_var(cc, sizeof(void*) == 8 ? _amd64W : _x86W, -1, ccval_bool(TRUE))
       || !new_cc_var(cc, _jscript_versionW, -1, ccval_num(JSCRIPT_MAJOR_VERSION + (DOUBLE)JSCRIPT_MINOR_VERSION/10.0))
       || !new_cc_var(cc, _jscript_buildW, -1, ccval_num(JSCRIPT_BUILD_VERSION))) {
        release_cc(cc);
        lex_error(ctx, E_OUTOFMEMORY);
        return FALSE;
    }

    ctx->script->cc = cc;
    return TRUE;
}