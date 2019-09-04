#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  off; int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ rangepoint_t ;
typedef  char WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free_rangepoint (TYPE_1__*) ; 
 int /*<<< orphan*/  init_rangepoint (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isspaceW (char) ; 
 char move_next_char (TYPE_1__*) ; 
 char move_prev_char (TYPE_1__*) ; 
 int /*<<< orphan*/  rangepoint_cmp (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static BOOL find_word_end(rangepoint_t *iter, BOOL is_collapsed)
{
    rangepoint_t prev_iter;
    WCHAR c;
    BOOL ret = FALSE;

    if(!is_collapsed) {
        init_rangepoint(&prev_iter, iter->node, iter->off);
        c = move_prev_char(&prev_iter);
        free_rangepoint(&prev_iter);
        if(isspaceW(c))
            return FALSE;
    }

    do {
        init_rangepoint(&prev_iter, iter->node, iter->off);
        c = move_next_char(iter);
        if(c == '\n') {
            free_rangepoint(iter);
            *iter = prev_iter;
            return ret;
        }
        if(!c) {
            if(!ret)
                ret = !rangepoint_cmp(iter, &prev_iter);
        }else {
            ret = TRUE;
        }
        free_rangepoint(&prev_iter);
    }while(c && !isspaceW(c));

    return ret;
}