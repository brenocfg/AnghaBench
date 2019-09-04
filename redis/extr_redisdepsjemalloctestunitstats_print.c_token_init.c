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
typedef  int /*<<< orphan*/  token_type_t ;
struct TYPE_3__ {size_t pos; size_t len; size_t line; size_t col; int /*<<< orphan*/  token_type; int /*<<< orphan*/ * parser; } ;
typedef  TYPE_1__ token_t ;
typedef  int /*<<< orphan*/  parser_t ;

/* Variables and functions */

__attribute__((used)) static void
token_init(token_t *token, parser_t *parser, token_type_t token_type,
    size_t pos, size_t len, size_t line, size_t col) {
	token->parser = parser;
	token->token_type = token_type;
	token->pos = pos;
	token->len = len;
	token->line = line;
	token->col = col;
}