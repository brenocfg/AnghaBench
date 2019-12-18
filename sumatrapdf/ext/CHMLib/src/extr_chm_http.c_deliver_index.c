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
struct chmFile {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CHM_ENUMERATE_ALL ; 
 int /*<<< orphan*/  _print_ui_index ; 
 int /*<<< orphan*/  chm_enumerate (struct chmFile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void deliver_index(FILE *fout, struct chmFile *file)
{
    fprintf(fout, 
            "HTTP/1.1 200 OK\r\n"
            "Connection: close\r\n"
         /* "Content-Length: 1000000\r\n" */
            "Content-Type: text/html\r\n\r\n"

            "<h2><u>CHM contents:</u></h2>"
            "<body><table>"
            "<tr><td><h5>Size:</h5></td><td><h5>File:</h5></td></tr>"
            "<tt>");
    if (! chm_enumerate(file, CHM_ENUMERATE_ALL, _print_ui_index, fout))
        fprintf(fout,"<br>   *** ERROR ***\r\n");
    fprintf(fout,"</tt> </table></body></html>");
}