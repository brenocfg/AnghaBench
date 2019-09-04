#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct module {TYPE_3__** format_info; } ;
struct cpu_stack_walk {int dummy; } ;
struct TYPE_16__ {unsigned char const* data; unsigned char const* end_data; int /*<<< orphan*/  word_size; } ;
typedef  TYPE_4__ dwarf2_traverse_context_t ;
typedef  int ULONG_PTR ;
struct TYPE_14__ {TYPE_1__* dwarf2_info; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
struct TYPE_13__ {int /*<<< orphan*/  word_size; } ;
typedef  int LONG_PTR ;
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 size_t DFI_DWARF ; 
#define  DW_OP_GNU_encoded_addr 173 
#define  DW_OP_abs 172 
#define  DW_OP_addr 171 
#define  DW_OP_and 170 
#define  DW_OP_bra 169 
 unsigned char DW_OP_breg0 ; 
 unsigned char DW_OP_breg31 ; 
#define  DW_OP_bregx 168 
#define  DW_OP_const1s 167 
#define  DW_OP_const1u 166 
#define  DW_OP_const2s 165 
#define  DW_OP_const2u 164 
#define  DW_OP_const4s 163 
#define  DW_OP_const4u 162 
#define  DW_OP_const8s 161 
#define  DW_OP_const8u 160 
#define  DW_OP_consts 159 
#define  DW_OP_constu 158 
#define  DW_OP_deref 157 
#define  DW_OP_deref_size 156 
#define  DW_OP_div 155 
#define  DW_OP_drop 154 
#define  DW_OP_dup 153 
#define  DW_OP_eq 152 
#define  DW_OP_ge 151 
#define  DW_OP_gt 150 
#define  DW_OP_le 149 
 unsigned char DW_OP_lit0 ; 
 unsigned char DW_OP_lit31 ; 
#define  DW_OP_lt 148 
#define  DW_OP_minus 147 
#define  DW_OP_mod 146 
#define  DW_OP_mul 145 
#define  DW_OP_ne 144 
#define  DW_OP_neg 143 
#define  DW_OP_nop 142 
#define  DW_OP_not 141 
#define  DW_OP_or 140 
#define  DW_OP_over 139 
#define  DW_OP_pick 138 
#define  DW_OP_plus 137 
#define  DW_OP_plus_uconst 136 
 unsigned char DW_OP_reg0 ; 
 unsigned char DW_OP_reg31 ; 
#define  DW_OP_regx 135 
#define  DW_OP_rot 134 
#define  DW_OP_shl 133 
#define  DW_OP_shr 132 
#define  DW_OP_shra 131 
#define  DW_OP_skip 130 
#define  DW_OP_swap 129 
#define  DW_OP_xor 128 
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  FIXME (char*,unsigned char) ; 
 int dwarf2_leb128_as_signed (TYPE_4__*) ; 
 int dwarf2_leb128_as_unsigned (TYPE_4__*) ; 
 int dwarf2_parse_addr (TYPE_4__*) ; 
 int dwarf2_parse_augmentation_ptr (TYPE_4__*,int) ; 
 int dwarf2_parse_byte (TYPE_4__*) ; 
 int dwarf2_parse_u2 (TYPE_4__*) ; 
 int dwarf2_parse_u4 (TYPE_4__*) ; 
 int dwarf2_parse_u8 (TYPE_4__*) ; 
 int get_context_reg (int /*<<< orphan*/ *,int) ; 
 int labs (int) ; 
 int /*<<< orphan*/  sw_read_mem (struct cpu_stack_walk*,int,int*,int) ; 

__attribute__((used)) static ULONG_PTR eval_expression(const struct module* module, struct cpu_stack_walk* csw,
                                 const unsigned char* zp, CONTEXT *context)
{
    dwarf2_traverse_context_t    ctx;
    ULONG_PTR reg, sz, tmp, stack[64];
    int sp = -1;
    ULONG_PTR len;

    ctx.data = zp;
    ctx.end_data = zp + 4;
    len = dwarf2_leb128_as_unsigned(&ctx);
    ctx.end_data = ctx.data + len;
    ctx.word_size = module->format_info[DFI_DWARF]->u.dwarf2_info->word_size;

    while (ctx.data < ctx.end_data)
    {
        unsigned char opcode = dwarf2_parse_byte(&ctx);

        if (opcode >= DW_OP_lit0 && opcode <= DW_OP_lit31)
            stack[++sp] = opcode - DW_OP_lit0;
        else if (opcode >= DW_OP_reg0 && opcode <= DW_OP_reg31)
            stack[++sp] = get_context_reg(context, opcode - DW_OP_reg0);
        else if (opcode >= DW_OP_breg0 && opcode <= DW_OP_breg31)
            stack[++sp] = get_context_reg(context, opcode - DW_OP_breg0) + dwarf2_leb128_as_signed(&ctx);
        else switch (opcode)
        {
        case DW_OP_nop:         break;
        case DW_OP_addr:        stack[++sp] = dwarf2_parse_addr(&ctx); break;
        case DW_OP_const1u:     stack[++sp] = dwarf2_parse_byte(&ctx); break;
        case DW_OP_const1s:     stack[++sp] = (signed char)dwarf2_parse_byte(&ctx); break;
        case DW_OP_const2u:     stack[++sp] = dwarf2_parse_u2(&ctx); break;
        case DW_OP_const2s:     stack[++sp] = (short)dwarf2_parse_u2(&ctx); break;
        case DW_OP_const4u:     stack[++sp] = dwarf2_parse_u4(&ctx); break;
        case DW_OP_const4s:     stack[++sp] = (signed int)dwarf2_parse_u4(&ctx); break;
        case DW_OP_const8u:     stack[++sp] = dwarf2_parse_u8(&ctx); break;
        case DW_OP_const8s:     stack[++sp] = (LONG_PTR)dwarf2_parse_u8(&ctx); break;
        case DW_OP_constu:      stack[++sp] = dwarf2_leb128_as_unsigned(&ctx); break;
        case DW_OP_consts:      stack[++sp] = dwarf2_leb128_as_signed(&ctx); break;
        case DW_OP_deref:
            if (!sw_read_mem(csw, stack[sp], &tmp, sizeof(tmp)))
            {
                ERR("Couldn't read memory at %lx\n", stack[sp]);
                tmp = 0;
            }
            stack[sp] = tmp;
            break;
        case DW_OP_dup:         stack[sp + 1] = stack[sp]; sp++; break;
        case DW_OP_drop:        sp--; break;
        case DW_OP_over:        stack[sp + 1] = stack[sp - 1]; sp++; break;
        case DW_OP_pick:        stack[sp + 1] = stack[sp - dwarf2_parse_byte(&ctx)]; sp++; break;
        case DW_OP_swap:        tmp = stack[sp]; stack[sp] = stack[sp-1]; stack[sp-1] = tmp; break;
        case DW_OP_rot:         tmp = stack[sp]; stack[sp] = stack[sp-1]; stack[sp-1] = stack[sp-2]; stack[sp-2] = tmp; break;
        case DW_OP_abs:         stack[sp] = labs(stack[sp]); break;
        case DW_OP_neg:         stack[sp] = -stack[sp]; break;
        case DW_OP_not:         stack[sp] = ~stack[sp]; break;
        case DW_OP_and:         stack[sp-1] &= stack[sp]; sp--; break;
        case DW_OP_or:          stack[sp-1] |= stack[sp]; sp--; break;
        case DW_OP_minus:       stack[sp-1] -= stack[sp]; sp--; break;
        case DW_OP_mul:         stack[sp-1] *= stack[sp]; sp--; break;
        case DW_OP_plus:        stack[sp-1] += stack[sp]; sp--; break;
        case DW_OP_xor:         stack[sp-1] ^= stack[sp]; sp--; break;
        case DW_OP_shl:         stack[sp-1] <<= stack[sp]; sp--; break;
        case DW_OP_shr:         stack[sp-1] >>= stack[sp]; sp--; break;
        case DW_OP_plus_uconst: stack[sp] += dwarf2_leb128_as_unsigned(&ctx); break;
        case DW_OP_shra:        stack[sp-1] = (LONG_PTR)stack[sp-1] / (1 << stack[sp]); sp--; break;
        case DW_OP_div:         stack[sp-1] = (LONG_PTR)stack[sp-1] / (LONG_PTR)stack[sp]; sp--; break;
        case DW_OP_mod:         stack[sp-1] = (LONG_PTR)stack[sp-1] % (LONG_PTR)stack[sp]; sp--; break;
        case DW_OP_ge:          stack[sp-1] = ((LONG_PTR)stack[sp-1] >= (LONG_PTR)stack[sp]); sp--; break;
        case DW_OP_gt:          stack[sp-1] = ((LONG_PTR)stack[sp-1] >  (LONG_PTR)stack[sp]); sp--; break;
        case DW_OP_le:          stack[sp-1] = ((LONG_PTR)stack[sp-1] <= (LONG_PTR)stack[sp]); sp--; break;
        case DW_OP_lt:          stack[sp-1] = ((LONG_PTR)stack[sp-1] <  (LONG_PTR)stack[sp]); sp--; break;
        case DW_OP_eq:          stack[sp-1] = (stack[sp-1] == stack[sp]); sp--; break;
        case DW_OP_ne:          stack[sp-1] = (stack[sp-1] != stack[sp]); sp--; break;
        case DW_OP_skip:        tmp = (short)dwarf2_parse_u2(&ctx); ctx.data += tmp; break;
        case DW_OP_bra:         tmp = (short)dwarf2_parse_u2(&ctx); if (!stack[sp--]) ctx.data += tmp; break;
        case DW_OP_GNU_encoded_addr:
            tmp = dwarf2_parse_byte(&ctx);
            stack[++sp] = dwarf2_parse_augmentation_ptr(&ctx, tmp);
            break;
        case DW_OP_regx:
            stack[++sp] = get_context_reg(context, dwarf2_leb128_as_unsigned(&ctx));
            break;
        case DW_OP_bregx:
            reg = dwarf2_leb128_as_unsigned(&ctx);
            tmp = dwarf2_leb128_as_signed(&ctx);
            stack[++sp] = get_context_reg(context, reg) + tmp;
            break;
        case DW_OP_deref_size:
            sz = dwarf2_parse_byte(&ctx);
            if (!sw_read_mem(csw, stack[sp], &tmp, sz))
            {
                ERR("Couldn't read memory at %lx\n", stack[sp]);
                tmp = 0;
            }
            /* do integral promotion */
            switch (sz)
            {
            case 1: stack[sp] = *(unsigned char*)&tmp; break;
            case 2: stack[sp] = *(unsigned short*)&tmp; break;
            case 4: stack[sp] = *(unsigned int*)&tmp; break;
            case 8: stack[sp] = *(ULONG_PTR*)&tmp; break; /* FIXME: won't work on 32bit platform */
            default: FIXME("Unknown size for deref 0x%lx\n", sz);
            }
            break;
        default:
            FIXME("unhandled opcode %02x\n", opcode);
        }
    }
    return stack[sp];
}