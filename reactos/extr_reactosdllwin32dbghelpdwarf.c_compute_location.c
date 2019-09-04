#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct location {void* kind; scalar_t__ reg; int offset; } ;
typedef  enum location_error { ____Placeholder_location_error } location_error ;
struct TYPE_11__ {scalar_t__ data; scalar_t__ end_data; int word_size; } ;
typedef  TYPE_1__ dwarf2_traverse_context_t ;
typedef  int /*<<< orphan*/  deref ;
struct TYPE_12__ {int /*<<< orphan*/  (* fetch_regname ) (void*) ;} ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD_PTR ;
typedef  int DWORD64 ;
typedef  void* DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  DW_OP_abs 175 
#define  DW_OP_addr 174 
#define  DW_OP_and 173 
#define  DW_OP_bra 172 
 unsigned char DW_OP_breg0 ; 
 unsigned char DW_OP_breg31 ; 
#define  DW_OP_bregx 171 
#define  DW_OP_const1s 170 
#define  DW_OP_const1u 169 
#define  DW_OP_const2s 168 
#define  DW_OP_const2u 167 
#define  DW_OP_const4s 166 
#define  DW_OP_const4u 165 
#define  DW_OP_const8s 164 
#define  DW_OP_const8u 163 
#define  DW_OP_consts 162 
#define  DW_OP_constu 161 
#define  DW_OP_deref 160 
#define  DW_OP_deref_size 159 
#define  DW_OP_div 158 
#define  DW_OP_drop 157 
#define  DW_OP_dup 156 
#define  DW_OP_eq 155 
#define  DW_OP_fbreg 154 
#define  DW_OP_ge 153 
#define  DW_OP_gt 152 
#define  DW_OP_le 151 
 unsigned char DW_OP_lit0 ; 
 unsigned char DW_OP_lit31 ; 
 unsigned char DW_OP_lo_user ; 
#define  DW_OP_lt 150 
#define  DW_OP_minus 149 
#define  DW_OP_mod 148 
#define  DW_OP_mul 147 
#define  DW_OP_ne 146 
#define  DW_OP_neg 145 
#define  DW_OP_nop 144 
#define  DW_OP_not 143 
#define  DW_OP_or 142 
#define  DW_OP_over 141 
#define  DW_OP_pick 140 
#define  DW_OP_piece 139 
#define  DW_OP_plus 138 
#define  DW_OP_plus_uconst 137 
 unsigned char DW_OP_reg0 ; 
 unsigned char DW_OP_reg31 ; 
#define  DW_OP_regx 136 
#define  DW_OP_rot 135 
#define  DW_OP_shl 134 
#define  DW_OP_shr 133 
#define  DW_OP_shra 132 
#define  DW_OP_skip 131 
#define  DW_OP_stack_value 130 
#define  DW_OP_swap 129 
#define  DW_OP_xor 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  ReadProcessMemory (int /*<<< orphan*/ ,void*,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ Wine_DW_no_register ; 
 TYPE_9__* dbghelp_current_cpu ; 
 int dwarf2_leb128_as_signed (TYPE_1__*) ; 
 int dwarf2_leb128_as_unsigned (TYPE_1__*) ; 
 void* dwarf2_map_register (int) ; 
 int dwarf2_parse_addr (TYPE_1__*) ; 
 unsigned int dwarf2_parse_byte (TYPE_1__*) ; 
 int dwarf2_parse_u2 (TYPE_1__*) ; 
 int dwarf2_parse_u4 (TYPE_1__*) ; 
 int dwarf2_parse_u8 (TYPE_1__*) ; 
 int labs (int) ; 
 void* loc_absolute ; 
 void* loc_dwarf2_block ; 
 int loc_err_cant_read ; 
 int loc_err_internal ; 
 int loc_err_too_complex ; 
 void* loc_register ; 
 void* loc_regrel ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 int /*<<< orphan*/  stub3 (void*) ; 
 int /*<<< orphan*/  stub4 (void*) ; 
 int /*<<< orphan*/  stub5 (void*) ; 

__attribute__((used)) static enum location_error
compute_location(dwarf2_traverse_context_t* ctx, struct location* loc,
                 HANDLE hproc, const struct location* frame)
{
    DWORD_PTR tmp, stack[64];
    unsigned stk;
    unsigned char op;
    BOOL piece_found = FALSE;

    stack[stk = 0] = 0;

    loc->kind = loc_absolute;
    loc->reg = Wine_DW_no_register;

    while (ctx->data < ctx->end_data)
    {
        op = dwarf2_parse_byte(ctx);

        if (op >= DW_OP_lit0 && op <= DW_OP_lit31)
            stack[++stk] = op - DW_OP_lit0;
        else if (op >= DW_OP_reg0 && op <= DW_OP_reg31)
        {
            /* dbghelp APIs don't know how to cope with this anyway
             * (for example 'long long' stored in two registers)
             * FIXME: We should tell winedbg how to deal with it (sigh)
             */
            if (!piece_found)
            {
                DWORD   cvreg = dwarf2_map_register(op - DW_OP_reg0);
                if (loc->reg != Wine_DW_no_register)
                    FIXME("Only supporting one reg (%s/%d -> %s/%d)\n",
                          dbghelp_current_cpu->fetch_regname(loc->reg), loc->reg,
                          dbghelp_current_cpu->fetch_regname(cvreg), cvreg);
                loc->reg = cvreg;
            }
            loc->kind = loc_register;
        }
        else if (op >= DW_OP_breg0 && op <= DW_OP_breg31)
        {
            /* dbghelp APIs don't know how to cope with this anyway
             * (for example 'long long' stored in two registers)
             * FIXME: We should tell winedbg how to deal with it (sigh)
             */
            if (!piece_found)
            {
                DWORD   cvreg = dwarf2_map_register(op - DW_OP_breg0);
                if (loc->reg != Wine_DW_no_register)
                    FIXME("Only supporting one breg (%s/%d -> %s/%d)\n",
                          dbghelp_current_cpu->fetch_regname(loc->reg), loc->reg,
                          dbghelp_current_cpu->fetch_regname(cvreg), cvreg);
                loc->reg = cvreg;
            }
            stack[++stk] = dwarf2_leb128_as_signed(ctx);
            loc->kind = loc_regrel;
        }
        else switch (op)
        {
        case DW_OP_nop:         break;
        case DW_OP_addr:        stack[++stk] = dwarf2_parse_addr(ctx); break;
        case DW_OP_const1u:     stack[++stk] = dwarf2_parse_byte(ctx); break;
        case DW_OP_const1s:     stack[++stk] = dwarf2_parse_byte(ctx); break;
        case DW_OP_const2u:     stack[++stk] = dwarf2_parse_u2(ctx); break;
        case DW_OP_const2s:     stack[++stk] = dwarf2_parse_u2(ctx); break;
        case DW_OP_const4u:     stack[++stk] = dwarf2_parse_u4(ctx); break;
        case DW_OP_const4s:     stack[++stk] = dwarf2_parse_u4(ctx); break;
        case DW_OP_const8u:     stack[++stk] = dwarf2_parse_u8(ctx); break;
        case DW_OP_const8s:     stack[++stk] = dwarf2_parse_u8(ctx); break;
        case DW_OP_constu:      stack[++stk] = dwarf2_leb128_as_unsigned(ctx); break;
        case DW_OP_consts:      stack[++stk] = dwarf2_leb128_as_signed(ctx); break;
        case DW_OP_dup:         stack[stk + 1] = stack[stk]; stk++; break;
        case DW_OP_drop:        stk--; break;
        case DW_OP_over:        stack[stk + 1] = stack[stk - 1]; stk++; break;
        case DW_OP_pick:        stack[stk + 1] = stack[stk - dwarf2_parse_byte(ctx)]; stk++; break;
        case DW_OP_swap:        tmp = stack[stk]; stack[stk] = stack[stk-1]; stack[stk-1] = tmp; break;
        case DW_OP_rot:         tmp = stack[stk]; stack[stk] = stack[stk-1]; stack[stk-1] = stack[stk-2]; stack[stk-2] = tmp; break;
        case DW_OP_abs:         stack[stk] = labs(stack[stk]); break;
        case DW_OP_neg:         stack[stk] = -stack[stk]; break;
        case DW_OP_not:         stack[stk] = ~stack[stk]; break;
        case DW_OP_and:         stack[stk-1] &= stack[stk]; stk--; break;
        case DW_OP_or:          stack[stk-1] |= stack[stk]; stk--; break;
        case DW_OP_minus:       stack[stk-1] -= stack[stk]; stk--; break;
        case DW_OP_mul:         stack[stk-1] *= stack[stk]; stk--; break;
        case DW_OP_plus:        stack[stk-1] += stack[stk]; stk--; break;
        case DW_OP_xor:         stack[stk-1] ^= stack[stk]; stk--; break;
        case DW_OP_shl:         stack[stk-1] <<= stack[stk]; stk--; break;
        case DW_OP_shr:         stack[stk-1] >>= stack[stk]; stk--; break;
        case DW_OP_plus_uconst: stack[stk] += dwarf2_leb128_as_unsigned(ctx); break;
        case DW_OP_shra:        stack[stk-1] = stack[stk-1] / (1 << stack[stk]); stk--; break;
        case DW_OP_div:         stack[stk-1] = stack[stk-1] / stack[stk]; stk--; break;
        case DW_OP_mod:         stack[stk-1] = stack[stk-1] % stack[stk]; stk--; break;
        case DW_OP_ge:          stack[stk-1] = (stack[stk-1] >= stack[stk]); stk--; break;
        case DW_OP_gt:          stack[stk-1] = (stack[stk-1] >  stack[stk]); stk--; break;
        case DW_OP_le:          stack[stk-1] = (stack[stk-1] <= stack[stk]); stk--; break;
        case DW_OP_lt:          stack[stk-1] = (stack[stk-1] <  stack[stk]); stk--; break;
        case DW_OP_eq:          stack[stk-1] = (stack[stk-1] == stack[stk]); stk--; break;
        case DW_OP_ne:          stack[stk-1] = (stack[stk-1] != stack[stk]); stk--; break;
        case DW_OP_skip:        tmp = dwarf2_parse_u2(ctx); ctx->data += tmp; break;
        case DW_OP_bra:         tmp = dwarf2_parse_u2(ctx); if (!stack[stk--]) ctx->data += tmp; break;
        case DW_OP_regx:
            tmp = dwarf2_leb128_as_unsigned(ctx);
            if (!piece_found)
            {
                if (loc->reg != Wine_DW_no_register)
                    FIXME("Only supporting one reg\n");
                loc->reg = dwarf2_map_register(tmp);
            }
            loc->kind = loc_register;
            break;
        case DW_OP_bregx:
            tmp = dwarf2_leb128_as_unsigned(ctx);
            if (loc->reg != Wine_DW_no_register)
                FIXME("Only supporting one regx\n");
            loc->reg = dwarf2_map_register(tmp);
            stack[++stk] = dwarf2_leb128_as_signed(ctx);
            loc->kind = loc_regrel;
            break;
        case DW_OP_fbreg:
            if (loc->reg != Wine_DW_no_register)
                FIXME("Only supporting one reg (%s/%d -> -2)\n",
                      dbghelp_current_cpu->fetch_regname(loc->reg), loc->reg);
            if (frame && frame->kind == loc_register)
            {
                loc->kind = loc_regrel;
                loc->reg = frame->reg;
                stack[++stk] = dwarf2_leb128_as_signed(ctx);
            }
            else if (frame && frame->kind == loc_regrel)
            {
                loc->kind = loc_regrel;
                loc->reg = frame->reg;
                stack[++stk] = dwarf2_leb128_as_signed(ctx) + frame->offset;
            }
            else
            {
                /* FIXME: this could be later optimized by not recomputing
                 * this very location expression
                 */
                loc->kind = loc_dwarf2_block;
                stack[++stk] = dwarf2_leb128_as_signed(ctx);
            }
            break;
        case DW_OP_piece:
            {
                unsigned sz = dwarf2_leb128_as_unsigned(ctx);
                WARN("Not handling OP_piece (size=%d)\n", sz);
                piece_found = TRUE;
            }
            break;
        case DW_OP_deref:
            if (!stk)
            {
                FIXME("Unexpected empty stack\n");
                return loc_err_internal;
            }
            if (loc->reg != Wine_DW_no_register)
            {
                WARN("Too complex expression for deref\n");
                return loc_err_too_complex;
            }
            if (hproc)
            {
                DWORD_PTR addr = stack[stk--];
                DWORD_PTR deref;

                if (!ReadProcessMemory(hproc, (void*)addr, &deref, sizeof(deref), NULL))
                {
                    WARN("Couldn't read memory at %lx\n", addr);
                    return loc_err_cant_read;
                }
                stack[++stk] = deref;
            }
            else
            {
               loc->kind = loc_dwarf2_block;
            }
            break;
        case DW_OP_deref_size:
            if (!stk)
            {
                FIXME("Unexpected empty stack\n");
                return loc_err_internal;
            }
            if (loc->reg != Wine_DW_no_register)
            {
                WARN("Too complex expression for deref\n");
                return loc_err_too_complex;
            }
            if (hproc)
            {
                DWORD_PTR addr = stack[stk--];
                BYTE derefsize = dwarf2_parse_byte(ctx);
                DWORD64 deref;

                if (!ReadProcessMemory(hproc, (void*)addr, &deref, derefsize, NULL))
                {
                    WARN("Couldn't read memory at %lx\n", addr);
                       return loc_err_cant_read;
                }

                switch (derefsize)
                {
                   case 1: stack[++stk] = *(unsigned char*)&deref; break;
                   case 2: stack[++stk] = *(unsigned short*)&deref; break;
                   case 4: stack[++stk] = *(DWORD*)&deref; break;
                   case 8: if (ctx->word_size >= derefsize) stack[++stk] = deref; break;
                }
            }
            else
            {
                dwarf2_parse_byte(ctx);
                loc->kind = loc_dwarf2_block;
            }
            break;
        case DW_OP_stack_value:
            /* Expected behaviour is that this is the last instruction of this
             * expression and just the "top of stack" value should be put to loc->offset. */
            break;
        default:
            if (op < DW_OP_lo_user) /* as DW_OP_hi_user is 0xFF, we don't need to test against it */
                FIXME("Unhandled attr op: %x\n", op);
            /* FIXME else unhandled extension */
            return loc_err_internal;
        }
    }
    loc->offset = stack[stk];
    return 0;
}