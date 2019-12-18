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
typedef  enum js_AstType { ____Placeholder_js_AstType } js_AstType ;

/* Variables and functions */
#define  AST_IDENTIFIER 192 
#define  EXP_ADD 191 
#define  EXP_ARRAY 190 
#define  EXP_ASS 189 
#define  EXP_ASS_ADD 188 
#define  EXP_ASS_BITAND 187 
#define  EXP_ASS_BITOR 186 
#define  EXP_ASS_BITXOR 185 
#define  EXP_ASS_DIV 184 
#define  EXP_ASS_MOD 183 
#define  EXP_ASS_MUL 182 
#define  EXP_ASS_SHL 181 
#define  EXP_ASS_SHR 180 
#define  EXP_ASS_SUB 179 
#define  EXP_ASS_USHR 178 
#define  EXP_BITAND 177 
#define  EXP_BITNOT 176 
#define  EXP_BITOR 175 
#define  EXP_BITXOR 174 
#define  EXP_CALL 173 
#define  EXP_COMMA 172 
#define  EXP_COND 171 
#define  EXP_DELETE 170 
#define  EXP_DIV 169 
#define  EXP_EQ 168 
#define  EXP_FALSE 167 
#define  EXP_FUN 166 
#define  EXP_GE 165 
#define  EXP_GT 164 
#define  EXP_IDENTIFIER 163 
#define  EXP_IN 162 
#define  EXP_INDEX 161 
#define  EXP_INSTANCEOF 160 
#define  EXP_LE 159 
#define  EXP_LOGAND 158 
#define  EXP_LOGNOT 157 
#define  EXP_LOGOR 156 
#define  EXP_LT 155 
#define  EXP_MEMBER 154 
#define  EXP_MOD 153 
#define  EXP_MUL 152 
#define  EXP_NE 151 
#define  EXP_NEG 150 
#define  EXP_NEW 149 
#define  EXP_NULL 148 
#define  EXP_NUMBER 147 
#define  EXP_OBJECT 146 
#define  EXP_POS 145 
#define  EXP_POSTDEC 144 
#define  EXP_POSTINC 143 
#define  EXP_PREDEC 142 
#define  EXP_PREINC 141 
#define  EXP_REGEXP 140 
#define  EXP_SHL 139 
#define  EXP_SHR 138 
#define  EXP_STRICTEQ 137 
#define  EXP_STRICTNE 136 
#define  EXP_STRING 135 
#define  EXP_SUB 134 
#define  EXP_THIS 133 
#define  EXP_TRUE 132 
#define  EXP_TYPEOF 131 
#define  EXP_UNDEF 130 
#define  EXP_USHR 129 
#define  EXP_VOID 128 

__attribute__((used)) static int prec(enum js_AstType type)
{
	switch (type) {
	case AST_IDENTIFIER:
	case EXP_IDENTIFIER:
	case EXP_NUMBER:
	case EXP_STRING:
	case EXP_REGEXP:
	case EXP_UNDEF:
	case EXP_NULL:
	case EXP_TRUE:
	case EXP_FALSE:
	case EXP_THIS:
	case EXP_ARRAY:
	case EXP_OBJECT:
		return 170;

	case EXP_FUN:
	case EXP_INDEX:
	case EXP_MEMBER:
	case EXP_CALL:
	case EXP_NEW:
		return 160;

	case EXP_POSTINC:
	case EXP_POSTDEC:
		return 150;

	case EXP_DELETE:
	case EXP_VOID:
	case EXP_TYPEOF:
	case EXP_PREINC:
	case EXP_PREDEC:
	case EXP_POS:
	case EXP_NEG:
	case EXP_BITNOT:
	case EXP_LOGNOT:
		return 140;

	case EXP_MOD:
	case EXP_DIV:
	case EXP_MUL:
		return 130;

	case EXP_SUB:
	case EXP_ADD:
		return 120;

	case EXP_USHR:
	case EXP_SHR:
	case EXP_SHL:
		return 110;

	case EXP_IN:
	case EXP_INSTANCEOF:
	case EXP_GE:
	case EXP_LE:
	case EXP_GT:
	case EXP_LT:
		return 100;

	case EXP_STRICTNE:
	case EXP_STRICTEQ:
	case EXP_NE:
	case EXP_EQ:
		return 90;

	case EXP_BITAND: return 80;
	case EXP_BITXOR: return 70;
	case EXP_BITOR: return 60;
	case EXP_LOGAND: return 50;
	case EXP_LOGOR: return 40;

	case EXP_COND:
		return 30;

	case EXP_ASS:
	case EXP_ASS_MUL:
	case EXP_ASS_DIV:
	case EXP_ASS_MOD:
	case EXP_ASS_ADD:
	case EXP_ASS_SUB:
	case EXP_ASS_SHL:
	case EXP_ASS_SHR:
	case EXP_ASS_USHR:
	case EXP_ASS_BITAND:
	case EXP_ASS_BITXOR:
	case EXP_ASS_BITOR:
		return 20;

#define COMMA 15

	case EXP_COMMA:
		return 10;

	default:
		return 0;
	}
}