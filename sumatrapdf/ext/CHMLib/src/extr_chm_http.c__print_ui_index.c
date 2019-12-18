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
struct chmUnitInfo {char* path; scalar_t__ length; } ;
struct chmFile {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CHM_ENUMERATOR_CONTINUE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,char*,char*) ; 

__attribute__((used)) static int _print_ui_index(struct chmFile *h, struct chmUnitInfo *ui, 
                           void *context)
{
    FILE *fout = (FILE*) context;
    fprintf(fout,
            "<tr>"
            "<td align=right>%8d\n</td>"
            "<td><a href=\"%s\">%s</a></td>"
            "</tr>",
            (int)ui->length, ui->path, ui->path);
    return CHM_ENUMERATOR_CONTINUE;
}