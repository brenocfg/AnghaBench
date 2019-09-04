#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cdata; } ;
typedef  TYPE_1__ mxwriter ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  close_element_starttag (TYPE_1__*) ; 
 int /*<<< orphan*/  set_element_name (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_data_to_stream (TYPE_1__*) ; 

__attribute__((used)) static inline HRESULT flush_output_buffer(mxwriter *This)
{
    close_element_starttag(This);
    set_element_name(This, NULL, 0);
    This->cdata = FALSE;
    return write_data_to_stream(This);
}