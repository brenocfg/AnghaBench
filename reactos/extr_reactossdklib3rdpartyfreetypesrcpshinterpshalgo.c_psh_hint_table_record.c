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
struct TYPE_9__ {struct TYPE_9__* parent; } ;
struct TYPE_8__ {scalar_t__ hints; scalar_t__ max_hints; scalar_t__ num_hints; TYPE_2__** sort_global; } ;
typedef  TYPE_1__* PSH_Hint_Table ;
typedef  TYPE_2__* PSH_Hint ;
typedef  scalar_t__ FT_UInt ;

/* Variables and functions */
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  psh_hint_activate (TYPE_2__*) ; 
 scalar_t__ psh_hint_is_active (TYPE_2__*) ; 
 scalar_t__ psh_hint_overlap (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static void
  psh_hint_table_record( PSH_Hint_Table  table,
                         FT_UInt         idx )
  {
    PSH_Hint  hint = table->hints + idx;


    if ( idx >= table->max_hints )
    {
      FT_TRACE0(( "psh_hint_table_record: invalid hint index %d\n", idx ));
      return;
    }

    /* ignore active hints */
    if ( psh_hint_is_active( hint ) )
      return;

    psh_hint_activate( hint );

    /* now scan the current active hint set to check */
    /* whether `hint' overlaps with another hint     */
    {
      PSH_Hint*  sorted = table->sort_global;
      FT_UInt    count  = table->num_hints;
      PSH_Hint   hint2;


      hint->parent = NULL;
      for ( ; count > 0; count--, sorted++ )
      {
        hint2 = sorted[0];

        if ( psh_hint_overlap( hint, hint2 ) )
        {
          hint->parent = hint2;
          break;
        }
      }
    }

    if ( table->num_hints < table->max_hints )
      table->sort_global[table->num_hints++] = hint;
    else
      FT_TRACE0(( "psh_hint_table_record: too many sorted hints!  BUG!\n" ));
  }