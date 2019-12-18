#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* string; } ;
struct TYPE_7__ {TYPE_1__ value; scalar_t__ index; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ json_token_t ;
struct TYPE_8__ {scalar_t__ data; scalar_t__ ptr; } ;
typedef  TYPE_3__ json_parse_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_ERROR ; 

__attribute__((used)) static void json_set_token_error(json_token_t *token, json_parse_t *json,
                                 const char *errtype)
{
    token->type = T_ERROR;
    token->index = json->ptr - json->data;
    token->value.string = errtype;
}