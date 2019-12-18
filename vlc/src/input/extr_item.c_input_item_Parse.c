#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  input_item_t ;
struct TYPE_8__ {scalar_t__ input; void* userdata; TYPE_2__ const* cbs; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ input_item_parser_id_t ;
struct TYPE_9__ {scalar_t__ on_ended; } ;
typedef  TYPE_2__ input_item_parser_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_S ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  input_Close (scalar_t__) ; 
 scalar_t__ input_CreatePreparser (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ input_Start (scalar_t__) ; 
 int /*<<< orphan*/  input_item_parser_InputEvent ; 
 TYPE_1__* malloc (int) ; 

input_item_parser_id_t *
input_item_Parse(input_item_t *item, vlc_object_t *obj,
                 const input_item_parser_cbs_t *cbs, void *userdata)
{
    assert(cbs && cbs->on_ended);
    input_item_parser_id_t *parser = malloc(sizeof(*parser));
    if (!parser)
        return NULL;

    parser->state = INIT_S;
    parser->cbs = cbs;
    parser->userdata = userdata;
    parser->input = input_CreatePreparser(obj, input_item_parser_InputEvent,
                                          parser, item);
    if (!parser->input || input_Start(parser->input))
    {
        if (parser->input)
            input_Close(parser->input);
        free(parser);
        return NULL;
    }
    return parser;
}