#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int firstcol; int /*<<< orphan*/  characters; scalar_t__ lastcol; } ;
typedef  TYPE_1__ cea708_text_row_t ;

/* Variables and functions */
 int CEA708_WINDOW_MAX_COLS ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static cea708_text_row_t * cea708_text_row_New( void )
{
    cea708_text_row_t *p_row = malloc( sizeof(*p_row) );
    if( p_row )
    {
        p_row->firstcol = CEA708_WINDOW_MAX_COLS;
        p_row->lastcol = 0;
        memset(p_row->characters, 0, 4 * CEA708_WINDOW_MAX_COLS);
    }
    return p_row;
}