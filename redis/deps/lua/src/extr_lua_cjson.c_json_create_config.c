#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* escape2char; void** ch2token; int /*<<< orphan*/  encode_buf; int /*<<< orphan*/  encode_number_precision; int /*<<< orphan*/  encode_keep_buffer; int /*<<< orphan*/  decode_invalid_numbers; int /*<<< orphan*/  encode_invalid_numbers; int /*<<< orphan*/  decode_max_depth; int /*<<< orphan*/  encode_max_depth; int /*<<< orphan*/  encode_sparse_safe; int /*<<< orphan*/  encode_sparse_ratio; int /*<<< orphan*/  encode_sparse_convert; } ;
typedef  TYPE_1__ json_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DECODE_INVALID_NUMBERS ; 
 int /*<<< orphan*/  DEFAULT_DECODE_MAX_DEPTH ; 
 int /*<<< orphan*/  DEFAULT_ENCODE_INVALID_NUMBERS ; 
 int /*<<< orphan*/  DEFAULT_ENCODE_KEEP_BUFFER ; 
 int /*<<< orphan*/  DEFAULT_ENCODE_MAX_DEPTH ; 
 int /*<<< orphan*/  DEFAULT_ENCODE_NUMBER_PRECISION ; 
 int /*<<< orphan*/  DEFAULT_SPARSE_CONVERT ; 
 int /*<<< orphan*/  DEFAULT_SPARSE_RATIO ; 
 int /*<<< orphan*/  DEFAULT_SPARSE_SAFE ; 
 void* T_ARR_BEGIN ; 
 void* T_ARR_END ; 
 void* T_COLON ; 
 void* T_COMMA ; 
 void* T_END ; 
 void* T_ERROR ; 
 void* T_OBJ_BEGIN ; 
 void* T_OBJ_END ; 
 void* T_UNKNOWN ; 
 void* T_WHITESPACE ; 
 int /*<<< orphan*/  json_destroy_config ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 TYPE_1__* lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void json_create_config(lua_State *l)
{
    json_config_t *cfg;
    int i;

    cfg = lua_newuserdata(l, sizeof(*cfg));

    /* Create GC method to clean up strbuf */
    lua_newtable(l);
    lua_pushcfunction(l, json_destroy_config);
    lua_setfield(l, -2, "__gc");
    lua_setmetatable(l, -2);

    cfg->encode_sparse_convert = DEFAULT_SPARSE_CONVERT;
    cfg->encode_sparse_ratio = DEFAULT_SPARSE_RATIO;
    cfg->encode_sparse_safe = DEFAULT_SPARSE_SAFE;
    cfg->encode_max_depth = DEFAULT_ENCODE_MAX_DEPTH;
    cfg->decode_max_depth = DEFAULT_DECODE_MAX_DEPTH;
    cfg->encode_invalid_numbers = DEFAULT_ENCODE_INVALID_NUMBERS;
    cfg->decode_invalid_numbers = DEFAULT_DECODE_INVALID_NUMBERS;
    cfg->encode_keep_buffer = DEFAULT_ENCODE_KEEP_BUFFER;
    cfg->encode_number_precision = DEFAULT_ENCODE_NUMBER_PRECISION;

#if DEFAULT_ENCODE_KEEP_BUFFER > 0
    strbuf_init(&cfg->encode_buf, 0);
#endif

    /* Decoding init */

    /* Tag all characters as an error */
    for (i = 0; i < 256; i++)
        cfg->ch2token[i] = T_ERROR;

    /* Set tokens that require no further processing */
    cfg->ch2token['{'] = T_OBJ_BEGIN;
    cfg->ch2token['}'] = T_OBJ_END;
    cfg->ch2token['['] = T_ARR_BEGIN;
    cfg->ch2token[']'] = T_ARR_END;
    cfg->ch2token[','] = T_COMMA;
    cfg->ch2token[':'] = T_COLON;
    cfg->ch2token['\0'] = T_END;
    cfg->ch2token[' '] = T_WHITESPACE;
    cfg->ch2token['\t'] = T_WHITESPACE;
    cfg->ch2token['\n'] = T_WHITESPACE;
    cfg->ch2token['\r'] = T_WHITESPACE;

    /* Update characters that require further processing */
    cfg->ch2token['f'] = T_UNKNOWN;     /* false? */
    cfg->ch2token['i'] = T_UNKNOWN;     /* inf, ininity? */
    cfg->ch2token['I'] = T_UNKNOWN;
    cfg->ch2token['n'] = T_UNKNOWN;     /* null, nan? */
    cfg->ch2token['N'] = T_UNKNOWN;
    cfg->ch2token['t'] = T_UNKNOWN;     /* true? */
    cfg->ch2token['"'] = T_UNKNOWN;     /* string? */
    cfg->ch2token['+'] = T_UNKNOWN;     /* number? */
    cfg->ch2token['-'] = T_UNKNOWN;
    for (i = 0; i < 10; i++)
        cfg->ch2token['0' + i] = T_UNKNOWN;

    /* Lookup table for parsing escape characters */
    for (i = 0; i < 256; i++)
        cfg->escape2char[i] = 0;          /* String error */
    cfg->escape2char['"'] = '"';
    cfg->escape2char['\\'] = '\\';
    cfg->escape2char['/'] = '/';
    cfg->escape2char['b'] = '\b';
    cfg->escape2char['t'] = '\t';
    cfg->escape2char['n'] = '\n';
    cfg->escape2char['f'] = '\f';
    cfg->escape2char['r'] = '\r';
    cfg->escape2char['u'] = 'u';          /* Unicode parsing required */
}