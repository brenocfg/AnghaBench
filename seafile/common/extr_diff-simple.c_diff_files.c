#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  files ;
struct TYPE_8__ {int (* file_cb ) (int,char const*,TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ SeafDirent ;
typedef  TYPE_2__ DiffOptions ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__**,int /*<<< orphan*/ ,int) ; 
 int stub1 (int,char const*,TYPE_1__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
diff_files (int n, SeafDirent *dents[], const char *basedir, DiffOptions *opt)
{
    SeafDirent *files[3];
    int i, n_files = 0;

    memset (files, 0, sizeof(files[0])*n);
    for (i = 0; i < n; ++i) {
        if (dents[i] && S_ISREG(dents[i]->mode)) {
            files[i] = dents[i];
            ++n_files;
        }
    }

    if (n_files == 0)
        return 0;

    return opt->file_cb (n, basedir, files, opt->data);
}