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
struct inf_file {int /*<<< orphan*/  const* filename; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  struct inf_file* HINF ;

/* Variables and functions */

const WCHAR *PARSER_get_inf_filename( HINF hinf )
{
    struct inf_file *file = hinf;
    return file->filename;
}