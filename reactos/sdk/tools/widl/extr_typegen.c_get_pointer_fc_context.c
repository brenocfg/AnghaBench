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
typedef  int /*<<< orphan*/  type_t ;
typedef  enum type_context { ____Placeholder_type_context } type_context ;
typedef  int /*<<< orphan*/  attr_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_OUT ; 
 int FC_OP ; 
 int FC_UP ; 
 int TYPE_CONTEXT_PARAM ; 
 int TYPE_CONTEXT_TOPLEVELPARAM ; 
 int /*<<< orphan*/  current_iface ; 
 int get_pointer_fc (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ is_attr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_object (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char get_pointer_fc_context( const type_t *type, const attr_list_t *attrs,
                                             enum type_context context )
{
    int pointer_fc = get_pointer_fc(type, attrs, context == TYPE_CONTEXT_TOPLEVELPARAM);

    if (pointer_fc == FC_UP && is_attr( attrs, ATTR_OUT ) &&
        context == TYPE_CONTEXT_PARAM && is_object( current_iface ))
        pointer_fc = FC_OP;

    return pointer_fc;
}