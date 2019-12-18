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
struct TYPE_8__ {int quot; int rem; } ;
typedef  TYPE_1__ lldiv_t ;
struct TYPE_9__ {int* p_buffer; int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 TYPE_2__* block_Realloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ lldiv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static block_t *Pack_Opus(block_t *p_data)
{
    lldiv_t d = lldiv(p_data->i_buffer, 255);
    p_data = block_Realloc(p_data, 2 + d.quot + 1, p_data->i_buffer);
    if (p_data) { /* no flags */
        p_data->p_buffer[0] = 0x7f;
        p_data->p_buffer[1] = 0xe0;
        memset(&p_data->p_buffer[2], 0xff, d.quot);
        p_data->p_buffer[2+d.quot] = d.rem;
    }

    return p_data;
}