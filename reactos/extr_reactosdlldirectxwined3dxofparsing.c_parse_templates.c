#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* pdxf; } ;
typedef  TYPE_2__ parse_buffer ;
struct TYPE_6__ {int nb_xtemplates; int /*<<< orphan*/ * xtemplates; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TOKEN_NONE ; 
 scalar_t__ TOKEN_TEMPLATE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ check_TOKEN (TYPE_2__*) ; 
 int /*<<< orphan*/  d3dxof_parsing ; 
 int /*<<< orphan*/  dump_template (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_template (TYPE_2__*) ; 

BOOL parse_templates(parse_buffer * buf, BOOL templates_only)
{
  while (check_TOKEN(buf) != TOKEN_NONE)
  {
    if (templates_only && (check_TOKEN(buf) != TOKEN_TEMPLATE))
      return TRUE;
    if (!parse_template(buf))
    {
      WARN("Template is not correct\n");
      return FALSE;
    }
    else
    {
      TRACE("Template successfully parsed:\n");
      if (TRACE_ON(d3dxof_parsing))
        dump_template(buf->pdxf->xtemplates, &buf->pdxf->xtemplates[buf->pdxf->nb_xtemplates - 1]);
    }
  }
  return TRUE;
}