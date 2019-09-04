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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {void* fWordStop; void* fSoftBreak; void* fCharStop; void* fWhiteSpace; } ;
typedef  TYPE_1__ SCRIPT_LOGATTR ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
#define  b_AI 164 
#define  b_AL 163 
#define  b_B2 162 
#define  b_BA 161 
#define  b_BB 160 
#define  b_BK 159 
#define  b_CB 158 
#define  b_CJ 157 
#define  b_CL 156 
#define  b_CM 155 
#define  b_CP 154 
#define  b_CR 153 
#define  b_EX 152 
#define  b_GL 151 
#define  b_H2 150 
#define  b_H3 149 
#define  b_HL 148 
#define  b_HY 147 
#define  b_ID 146 
#define  b_IN 145 
#define  b_IS 144 
#define  b_JL 143 
#define  b_JT 142 
#define  b_JV 141 
#define  b_LF 140 
#define  b_NL 139 
#define  b_NS 138 
#define  b_NU 137 
#define  b_OP 136 
 short b_PO ; 
 short b_PR ; 
#define  b_QU 135 
 short b_RI ; 
#define  b_SA 134 
#define  b_SG 133 
#define  b_SP 132 
#define  b_SY 131 
#define  b_WJ 130 
#define  b_XX 129 
#define  b_ZW 128 
 short b_r ; 
 short b_s ; 
 short b_x ; 
 int /*<<< orphan*/  debug_output_breaks (short*,int) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  else_break (short*,short) ; 
 short get_table_entry (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 short* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (short*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wine_linebreak_table ; 

void BREAK_line(const WCHAR *chars, int count, const SCRIPT_ANALYSIS *sa, SCRIPT_LOGATTR *la)
{
    int i,j;
    short *break_class;
    short *break_before;

    TRACE("In      %s\n",debugstr_wn(chars,count));

    break_class = heap_alloc(count * sizeof(*break_class));
    break_before = heap_alloc(count * sizeof(*break_before));

    for (i = 0; i < count; i++)
    {
        break_class[i] = get_table_entry( wine_linebreak_table, chars[i] );
        break_before[i] = 0;

        memset(&la[i],0,sizeof(SCRIPT_LOGATTR));

        la[i].fCharStop = TRUE;
        switch (break_class[i])
        {
            case b_BK:
            case b_ZW:
            case b_SP:
                la[i].fWhiteSpace = TRUE;
                break;
            case b_CM:
                la[i].fCharStop = FALSE;
                break;
        }
    }

    /* LB1 */
    /* TODO: Have outside algorithms for these scripts */
    for (i = 0; i < count; i++)
    {
        switch(break_class[i])
        {
            case b_AI:
            case b_SA:
            case b_SG:
            case b_XX:
                break_class[i] = b_AL;
                break;
            case b_CJ:
                break_class[i] = b_NS;
                break;
        }
    }

    /* LB2 - LB3 */
    break_before[0] = b_x;
    for (i = 0; i < count; i++)
    {
        switch(break_class[i])
        {
            /* LB4 - LB6 */
            case b_CR:
                if (i < count-1 && break_class[i+1] == b_LF)
                {
                    else_break(&break_before[i],b_x);
                    else_break(&break_before[i+1],b_x);
                    break;
                }
            case b_LF:
            case b_NL:
            case b_BK:
                if (i < count-1) else_break(&break_before[i+1],b_r);
                else_break(&break_before[i],b_x);
                break;
            /* LB7 */
            case b_SP:
                else_break(&break_before[i],b_x);
                break;
            case b_ZW:
                else_break(&break_before[i],b_x);
            /* LB8 */
                while (i < count-1 && break_class[i+1] == b_SP)
                    i++;
                else_break(&break_before[i],b_s);
                break;
        }
    }

    debug_output_breaks(break_before,count);

    /* LB9 - LB10 */
    for (i = 0; i < count; i++)
    {
        if (break_class[i] == b_CM)
        {
            if (i > 0)
            {
                switch (break_class[i-1])
                {
                    case b_SP:
                    case b_BK:
                    case b_CR:
                    case b_LF:
                    case b_NL:
                    case b_ZW:
                        break_class[i] = b_AL;
                        break;
                    default:
                        break_class[i] = break_class[i-1];
                }
            }
            else break_class[i] = b_AL;
        }
    }

    for (i = 0; i < count; i++)
    {
        switch(break_class[i])
        {
            /* LB11 */
            case b_WJ:
                else_break(&break_before[i],b_x);
                if (i < count-1)
                    else_break(&break_before[i+1],b_x);
                break;
            /* LB12 */
            case b_GL:
                if (i < count-1)
                    else_break(&break_before[i+1],b_x);
            /* LB12a */
                if (i > 0)
                {
                    if (break_class[i-1] != b_SP &&
                        break_class[i-1] != b_BA &&
                        break_class[i-1] != b_HY)
                        else_break(&break_before[i],b_x);
                }
                break;
            /* LB13 */
            case b_CL:
            case b_CP:
            case b_EX:
            case b_IS:
            case b_SY:
                else_break(&break_before[i],b_x);
                break;
            /* LB14 */
            case b_OP:
                while (i < count-1 && break_class[i+1] == b_SP)
                {
                    else_break(&break_before[i+1],b_x);
                    i++;
                }
                else_break(&break_before[i+1],b_x);
                break;
            /* LB15 */
            case b_QU:
                j = i+1;
                while (j < count-1 && break_class[j] == b_SP)
                    j++;
                if (break_class[j] == b_OP)
                {
                    for (; j > i; j--)
                        else_break(&break_before[j],b_x);
                }
                break;
            /* LB16 */
            case b_NS:
                j = i-1;
                while(j > 0 && break_class[j] == b_SP)
                    j--;
                if (break_class[j] == b_CL || break_class[j] == b_CP)
                {
                    for (j++; j <= i; j++)
                        else_break(&break_before[j],b_x);
                }
                break;
            /* LB17 */
            case b_B2:
                j = i+1;
                while (j < count && break_class[j] == b_SP)
                    j++;
                if (break_class[j] == b_B2)
                {
                    for (; j > i; j--)
                        else_break(&break_before[j],b_x);
                }
                break;
        }
    }

    debug_output_breaks(break_before,count);

    for (i = 0; i < count; i++)
    {
        switch(break_class[i])
        {
            /* LB18 */
            case b_SP:
                if (i < count-1)
                    else_break(&break_before[i+1],b_s);
                break;
            /* LB19 */
            case b_QU:
                else_break(&break_before[i],b_x);
                if (i < count-1)
                    else_break(&break_before[i+1],b_x);
                break;
            /* LB20 */
            case b_CB:
                else_break(&break_before[i],b_s);
                if (i < count-1)
                    else_break(&break_before[i+1],b_s);
                break;
            /* LB21 */
            case b_BA:
            case b_HY:
            case b_NS:
                else_break(&break_before[i],b_x);
                break;
            case b_BB:
                if (i < count-1)
                    else_break(&break_before[i+1],b_x);
                break;
            /* LB21a */
            case b_HL:
                if (i < count-2)
                    switch (break_class[i+1])
                    {
                    case b_HY:
                    case b_BA:
                        else_break(&break_before[i+2], b_x);
                    }
                break;
            /* LB22 */
            case b_IN:
                if (i > 0)
                {
                    switch (break_class[i-1])
                    {
                        case b_AL:
                        case b_HL:
                        case b_ID:
                        case b_IN:
                        case b_NU:
                            else_break(&break_before[i], b_x);
                    }
                }
                break;
        }

        if (i < count-1)
        {
            /* LB23 */
            if ((break_class[i] == b_ID && break_class[i+1] == b_PO) ||
                (break_class[i] == b_AL && break_class[i+1] == b_NU) ||
                (break_class[i] == b_HL && break_class[i+1] == b_NU) ||
                (break_class[i] == b_NU && break_class[i+1] == b_AL) ||
                (break_class[i] == b_NU && break_class[i+1] == b_HL))
                    else_break(&break_before[i+1],b_x);
            /* LB24 */
            if ((break_class[i] == b_PR && break_class[i+1] == b_ID) ||
                (break_class[i] == b_PR && break_class[i+1] == b_AL) ||
                (break_class[i] == b_PR && break_class[i+1] == b_HL) ||
                (break_class[i] == b_PO && break_class[i+1] == b_AL) ||
                (break_class[i] == b_PO && break_class[i+1] == b_HL))
                    else_break(&break_before[i+1],b_x);

            /* LB25 */
            if ((break_class[i] == b_CL && break_class[i+1] == b_PO) ||
                (break_class[i] == b_CP && break_class[i+1] == b_PO) ||
                (break_class[i] == b_CL && break_class[i+1] == b_PR) ||
                (break_class[i] == b_CP && break_class[i+1] == b_PR) ||
                (break_class[i] == b_NU && break_class[i+1] == b_PO) ||
                (break_class[i] == b_NU && break_class[i+1] == b_PR) ||
                (break_class[i] == b_PO && break_class[i+1] == b_OP) ||
                (break_class[i] == b_PO && break_class[i+1] == b_NU) ||
                (break_class[i] == b_PR && break_class[i+1] == b_OP) ||
                (break_class[i] == b_PR && break_class[i+1] == b_NU) ||
                (break_class[i] == b_HY && break_class[i+1] == b_NU) ||
                (break_class[i] == b_IS && break_class[i+1] == b_NU) ||
                (break_class[i] == b_NU && break_class[i+1] == b_NU) ||
                (break_class[i] == b_SY && break_class[i+1] == b_NU))
                    else_break(&break_before[i+1],b_x);

            /* LB26 */
            if (break_class[i] == b_JL)
            {
                switch (break_class[i+1])
                {
                    case b_JL:
                    case b_JV:
                    case b_H2:
                    case b_H3:
                        else_break(&break_before[i+1],b_x);
                }
            }
            if ((break_class[i] == b_JV || break_class[i] == b_H2) &&
                (break_class[i+1] == b_JV || break_class[i+1] == b_JT))
                    else_break(&break_before[i+1],b_x);
            if ((break_class[i] == b_JT || break_class[i] == b_H3) &&
                 break_class[i+1] == b_JT)
                    else_break(&break_before[i+1],b_x);

            /* LB27 */
            switch (break_class[i])
            {
                case b_JL:
                case b_JV:
                case b_JT:
                case b_H2:
                case b_H3:
                    if (break_class[i+1] == b_IN || break_class[i+1] == b_PO)
                        else_break(&break_before[i+1],b_x);
            }
            if (break_class[i] == b_PR)
            {
                switch (break_class[i+1])
                {
                    case b_JL:
                    case b_JV:
                    case b_JT:
                    case b_H2:
                    case b_H3:
                        else_break(&break_before[i+1],b_x);
                }
            }

            /* LB28 */
            if ((break_class[i] == b_AL && break_class[i+1] == b_AL) ||
                (break_class[i] == b_AL && break_class[i+1] == b_HL) ||
                (break_class[i] == b_HL && break_class[i+1] == b_AL) ||
                (break_class[i] == b_HL && break_class[i+1] == b_HL))
                else_break(&break_before[i+1],b_x);

            /* LB29 */
            if ((break_class[i] == b_IS && break_class[i+1] == b_AL) ||
                (break_class[i] == b_IS && break_class[i+1] == b_HL))
                else_break(&break_before[i+1],b_x);

            /* LB30 */
            if ((break_class[i] == b_AL || break_class[i] == b_HL || break_class[i] == b_NU) &&
                 break_class[i+1] == b_OP)
                else_break(&break_before[i+1],b_x);
            if (break_class[i] == b_CP &&
                (break_class[i+1] == b_AL || break_class[i+1] == b_HL || break_class[i+1] == b_NU))
                else_break(&break_before[i+1],b_x);

            /* LB30a */
            if (break_class[i] == b_RI && break_class[i+1] == b_RI)
                else_break(&break_before[i+1],b_x);
        }
    }
    debug_output_breaks(break_before,count);

    /* LB31 */
    for (i = 0; i < count-1; i++)
        else_break(&break_before[i+1],b_s);

    debug_output_breaks(break_before,count);
    for (i = 0; i < count; i++)
    {
        if (break_before[i] != b_x)
        {
            la[i].fSoftBreak = TRUE;
            la[i].fWordStop = TRUE;
        }
    }

    heap_free(break_before);
    heap_free(break_class);
}