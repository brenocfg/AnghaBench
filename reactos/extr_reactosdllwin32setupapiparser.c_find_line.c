#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct section {unsigned int nb_lines; struct line* lines; } ;
struct line {int key_field; } ;
struct inf_file {int nb_sections; TYPE_1__* fields; struct section** sections; } ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmpiW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct line *find_line( struct inf_file *file, int section_index, const WCHAR *name )
{
    struct section *section;
    struct line *line;
    unsigned int i;

    if (section_index < 0 || section_index >= file->nb_sections) return NULL;
    section = file->sections[section_index];
    for (i = 0, line = section->lines; i < section->nb_lines; i++, line++)
    {
        if (line->key_field == -1) continue;
        if (!strcmpiW( name, file->fields[line->key_field].text )) return line;
    }
    return NULL;
}