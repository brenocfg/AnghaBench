#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  void* json_token_type_t ;
struct TYPE_14__ {int boolean; } ;
struct TYPE_16__ {void* type; TYPE_1__ value; scalar_t__* index; } ;
typedef  TYPE_3__ json_token_t ;
struct TYPE_17__ {int data; TYPE_2__* cfg; scalar_t__* ptr; } ;
typedef  TYPE_4__ json_parse_t ;
struct TYPE_15__ {scalar_t__ decode_invalid_numbers; void** ch2token; } ;

/* Variables and functions */
 void* T_BOOLEAN ; 
 void* T_END ; 
 void* T_ERROR ; 
 void* T_NULL ; 
 void* T_UNKNOWN ; 
 void* T_WHITESPACE ; 
 scalar_t__ json_is_invalid_number (TYPE_4__*) ; 
 int /*<<< orphan*/  json_next_number_token (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  json_next_string_token (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  json_set_token_error (TYPE_3__*,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,char*,int) ; 

__attribute__((used)) static void json_next_token(json_parse_t *json, json_token_t *token)
{
    const json_token_type_t *ch2token = json->cfg->ch2token;
    int ch;

    /* Eat whitespace. */
    while (1) {
        ch = (unsigned char)*(json->ptr);
        token->type = ch2token[ch];
        if (token->type != T_WHITESPACE)
            break;
        json->ptr++;
    }

    /* Store location of new token. Required when throwing errors
     * for unexpected tokens (syntax errors). */
    token->index = json->ptr - json->data;

    /* Don't advance the pointer for an error or the end */
    if (token->type == T_ERROR) {
        json_set_token_error(token, json, "invalid token");
        return;
    }

    if (token->type == T_END) {
        return;
    }

    /* Found a known single character token, advance index and return */
    if (token->type != T_UNKNOWN) {
        json->ptr++;
        return;
    }

    /* Process characters which triggered T_UNKNOWN
     *
     * Must use strncmp() to match the front of the JSON string.
     * JSON identifier must be lowercase.
     * When strict_numbers if disabled, either case is allowed for
     * Infinity/NaN (since we are no longer following the spec..) */
    if (ch == '"') {
        json_next_string_token(json, token);
        return;
    } else if (ch == '-' || ('0' <= ch && ch <= '9')) {
        if (!json->cfg->decode_invalid_numbers && json_is_invalid_number(json)) {
            json_set_token_error(token, json, "invalid number");
            return;
        }
        json_next_number_token(json, token);
        return;
    } else if (!strncmp(json->ptr, "true", 4)) {
        token->type = T_BOOLEAN;
        token->value.boolean = 1;
        json->ptr += 4;
        return;
    } else if (!strncmp(json->ptr, "false", 5)) {
        token->type = T_BOOLEAN;
        token->value.boolean = 0;
        json->ptr += 5;
        return;
    } else if (!strncmp(json->ptr, "null", 4)) {
        token->type = T_NULL;
        json->ptr += 4;
        return;
    } else if (json->cfg->decode_invalid_numbers &&
               json_is_invalid_number(json)) {
        /* When decode_invalid_numbers is enabled, only attempt to process
         * numbers we know are invalid JSON (Inf, NaN, hex)
         * This is required to generate an appropriate token error,
         * otherwise all bad tokens will register as "invalid number"
         */
        json_next_number_token(json, token);
        return;
    }

    /* Token starts with t/f/n but isn't recognised above. */
    json_set_token_error(token, json, "invalid token");
}