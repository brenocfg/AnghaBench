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
struct RTFTable {int gapH; } ;
struct TYPE_3__ {int /*<<< orphan*/  bEmulateVersion10; } ;
typedef  struct RTFTable RTFTable ;
typedef  TYPE_1__ ME_TextEditor ;

/* Variables and functions */
 struct RTFTable* heap_alloc_zero (int) ; 

struct RTFTable *ME_MakeTableDef(ME_TextEditor *editor)
{
  RTFTable *tableDef = heap_alloc_zero(sizeof(*tableDef));

  if (!editor->bEmulateVersion10) /* v4.1 */
    tableDef->gapH = 10;
  return tableDef;
}