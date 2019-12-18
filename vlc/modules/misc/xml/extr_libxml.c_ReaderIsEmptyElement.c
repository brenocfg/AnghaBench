#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ xml_reader_t ;
struct TYPE_5__ {int /*<<< orphan*/  xml; } ;
typedef  TYPE_2__ xml_reader_sys_t ;

/* Variables and functions */
 int xmlTextReaderIsEmptyElement (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ReaderIsEmptyElement( xml_reader_t *p_reader )
{
    xml_reader_sys_t *p_sys = p_reader->p_sys;
    return xmlTextReaderIsEmptyElement( p_sys->xml );
}