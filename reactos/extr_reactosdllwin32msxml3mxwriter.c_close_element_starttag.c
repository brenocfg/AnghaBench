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
struct TYPE_4__ {int /*<<< orphan*/  element; } ;
typedef  TYPE_1__ mxwriter ;
typedef  char WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  write_output_buffer (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static void close_element_starttag(mxwriter *writer)
{
    static const WCHAR gtW[] = {'>'};
    if (!writer->element) return;
    write_output_buffer(writer, gtW, 1);
}