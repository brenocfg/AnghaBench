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
struct LZXstate {int actual_size; int window_size; int R0; int R1; int R2; scalar_t__* LENGTH_len; scalar_t__* MAINTREE_len; scalar_t__ window_posn; scalar_t__ intel_started; scalar_t__ intel_curpos; int /*<<< orphan*/  block_type; scalar_t__ block_remaining; scalar_t__ frames_read; scalar_t__ header_read; scalar_t__ main_elements; int /*<<< orphan*/ * window; } ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  LZX_BLOCKTYPE_INVALID ; 
 int LZX_LENGTH_MAXSYMBOLS ; 
 int LZX_MAINTREE_MAXSYMBOLS ; 
 scalar_t__ LZX_NUM_CHARS ; 
 int /*<<< orphan*/  free (struct LZXstate*) ; 
 scalar_t__ malloc (int) ; 

struct LZXstate *LZXinit(int window)
{
    struct LZXstate *pState=NULL;
    ULONG wndsize = 1 << window;
    int i, posn_slots;

    /* LZX supports window sizes of 2^15 (32Kb) through 2^21 (2Mb) */
    /* if a previously allocated window is big enough, keep it     */
    if (window < 15 || window > 21) return NULL;

    /* allocate state and associated window */
    pState = (struct LZXstate *)malloc(sizeof(struct LZXstate));
    if (!pState || !(pState->window = (UBYTE *)malloc(wndsize)))
    {
        free(pState);
        return NULL;
    }
    pState->actual_size = wndsize;
    pState->window_size = wndsize;

    /* calculate required position slots */
    if (window == 20) posn_slots = 42;
    else if (window == 21) posn_slots = 50;
    else posn_slots = window << 1;

    /** alternatively **/
    /* posn_slots=i=0; while (i < wndsize) i += 1 << extra_bits[posn_slots++]; */

    /* initialize other state */
    pState->R0  =  pState->R1  = pState->R2 = 1;
    pState->main_elements   = LZX_NUM_CHARS + (posn_slots << 3);
    pState->header_read     = 0;
    pState->frames_read     = 0;
    pState->block_remaining = 0;
    pState->block_type      = LZX_BLOCKTYPE_INVALID;
    pState->intel_curpos    = 0;
    pState->intel_started   = 0;
    pState->window_posn     = 0;

    /* initialise tables to 0 (because deltas will be applied to them) */
    for (i = 0; i < LZX_MAINTREE_MAXSYMBOLS; i++) pState->MAINTREE_len[i] = 0;
    for (i = 0; i < LZX_LENGTH_MAXSYMBOLS; i++)   pState->LENGTH_len[i]   = 0;

    return pState;
}