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
struct TYPE_5__ {TYPE_1__* be_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  tmp_dir; } ;
typedef  TYPE_1__ FsPriv ;
typedef  TYPE_2__ BlockBackend ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 int g_mkstemp (char*) ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
open_tmp_file (BlockBackend *bend,
               const char *basename,
               char **path)
{
    FsPriv *priv = bend->be_priv;
    int fd;

    *path = g_strdup_printf ("%s/%s.XXXXXX", priv->tmp_dir, basename);
    fd = g_mkstemp (*path);
    if (fd < 0)
        g_free (*path);

    return fd;
}