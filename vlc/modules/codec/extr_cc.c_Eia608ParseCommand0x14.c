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
typedef  int uint8_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_row; int /*<<< orphan*/  i_column; } ;
struct TYPE_9__ {void* mode; int /*<<< orphan*/  font; int /*<<< orphan*/  color; TYPE_1__ cursor; int /*<<< orphan*/  i_screen; int /*<<< orphan*/  i_row_rollup; } ;
typedef  TYPE_2__ eia608_t ;
typedef  int eia608_status_t ;
typedef  void* eia608_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIA608_COLOR_DEFAULT ; 
 int /*<<< orphan*/  EIA608_FONT_REGULAR ; 
 void* EIA608_MODE_PAINTON ; 
 void* EIA608_MODE_POPUP ; 
 void* EIA608_MODE_ROLLUP_2 ; 
 void* EIA608_MODE_ROLLUP_3 ; 
 void* EIA608_MODE_ROLLUP_4 ; 
 void* EIA608_MODE_TEXT ; 
 int EIA608_STATUS_CAPTION_CLEARED ; 
 int EIA608_STATUS_CAPTION_ENDED ; 
 int EIA608_STATUS_CHANGED ; 
 int EIA608_STATUS_DEFAULT ; 
 int /*<<< orphan*/  Eia608Erase (TYPE_2__*) ; 
 int /*<<< orphan*/  Eia608EraseScreen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  Eia608EraseToEndOfRow (TYPE_2__*) ; 
 int /*<<< orphan*/  Eia608RollUp (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static eia608_status_t Eia608ParseCommand0x14( eia608_t *h, uint8_t d2 )
{
    eia608_status_t i_status = EIA608_STATUS_DEFAULT;
    eia608_mode_t proposed_mode;

    switch( d2 )
    {
    case 0x20:  /* Resume caption loading */
        Debug(printf("[RCL]"));
        h->mode = EIA608_MODE_POPUP;
        break;
    case 0x21:  /* Backspace */
        Debug(printf("[BS]"));
        Eia608Erase( h );
        i_status = EIA608_STATUS_CHANGED;
        break;
    case 0x22:  /* Reserved */
    case 0x23:
        Debug(printf("[ALARM %d]", d2 - 0x22));
        break;
    case 0x24:  /* Delete to end of row */
        Debug(printf("[DER]"));
        Eia608EraseToEndOfRow( h );
        break;
    case 0x25:  /* Rollup 2 */
    case 0x26:  /* Rollup 3 */
    case 0x27:  /* Rollup 4 */
        Debug(printf("[RU%d]", d2 - 0x23));
        if( h->mode == EIA608_MODE_POPUP || h->mode == EIA608_MODE_PAINTON )
        {
            Eia608EraseScreen( h, true );
            Eia608EraseScreen( h, false );
            i_status = EIA608_STATUS_CHANGED | EIA608_STATUS_CAPTION_CLEARED;
        }

        if( d2 == 0x25 )
            proposed_mode = EIA608_MODE_ROLLUP_2;
        else if( d2 == 0x26 )
            proposed_mode = EIA608_MODE_ROLLUP_3;
        else
            proposed_mode = EIA608_MODE_ROLLUP_4;

        if ( proposed_mode != h->mode )
        {
            h->mode = proposed_mode;
            h->cursor.i_column = 0;
            h->cursor.i_row = h->i_row_rollup;
        }
        break;
    case 0x28:  /* Flash on */
        Debug(printf("[FON]"));
        /* TODO */
        break;
    case 0x29:  /* Resume direct captionning */
        Debug(printf("[RDC]"));
        h->mode = EIA608_MODE_PAINTON;
        break;
    case 0x2a:  /* Text restart */
        Debug(printf("[TR]"));
        /* TODO */
        break;

    case 0x2b: /* Resume text display */
        Debug(printf("[RTD]"));
        h->mode = EIA608_MODE_TEXT;
        break;

    case 0x2c: /* Erase displayed memory */
        Debug(printf("[EDM]"));
        Eia608EraseScreen( h, true );
        i_status = EIA608_STATUS_CHANGED | EIA608_STATUS_CAPTION_CLEARED;
        break;
    case 0x2d: /* Carriage return */
        Debug(printf("[CR]"));
        Eia608RollUp(h);
        i_status = EIA608_STATUS_CHANGED;
        break;
    case 0x2e: /* Erase non displayed memory */
        Debug(printf("[ENM]"));
        Eia608EraseScreen( h, false );
        break;
    case 0x2f: /* End of caption (flip screen if not paint on) */
        Debug(printf("[EOC]"));
        if( h->mode != EIA608_MODE_PAINTON )
            h->i_screen = 1 - h->i_screen;
        h->mode = EIA608_MODE_POPUP;
        h->cursor.i_column = 0;
        h->cursor.i_row = 0;
        h->color = EIA608_COLOR_DEFAULT;
        h->font = EIA608_FONT_REGULAR;
        i_status = EIA608_STATUS_CHANGED | EIA608_STATUS_CAPTION_ENDED;
        break;
    }
    return i_status;
}