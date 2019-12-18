#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  font; int /*<<< orphan*/  color; } ;
typedef  TYPE_1__ eia608_t ;
typedef  int /*<<< orphan*/  eia608_status_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_font; int /*<<< orphan*/  i_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIA608_STATUS_DEFAULT ; 
 int /*<<< orphan*/  Eia608Cursor (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* pac2_attribs ; 
 int /*<<< orphan*/  printf (char*,int const) ; 

__attribute__((used)) static eia608_status_t Eia608ParseTextAttribute( eia608_t *h, uint8_t d2 )
{
    const int i_index = d2 - 0x20;
    assert( d2 >= 0x20 && d2 <= 0x2f );

    Debug(printf("[TA %d]", i_index));
    h->color = pac2_attribs[i_index].i_color;
    h->font  = pac2_attribs[i_index].i_font;
    Eia608Cursor( h, 1 );

    return EIA608_STATUS_DEFAULT;
}