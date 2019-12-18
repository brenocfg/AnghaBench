#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_9__ {int /*<<< orphan*/  hxdll; } ;
typedef  TYPE_2__ vout_display_sys_t ;
struct TYPE_10__ {char* code; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t BUILTIN_SHADERS_COUNT ; 
 int Direct3D9CompileShader (TYPE_1__*,char const*,long) ; 
 int /*<<< orphan*/  Direct3D9DestroyShaders (TYPE_1__*) ; 
 long MAX_SHADER_FILE_SIZE ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SELECTED_SHADER_FILE ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_4__* builtin_shaders ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fread (char*,long,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 long strlen (char const*) ; 
 char* var_InheritString (TYPE_1__*,char*) ; 
 char* vlc_alloc (long,int) ; 
 int /*<<< orphan*/ * vlc_fopen (char*,char*) ; 

__attribute__((used)) static int Direct3D9CreateShaders(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    if (!sys->hxdll)
        return VLC_EGENERIC;

    /* Find which shader was selected in the list. */
    char *selected_shader = var_InheritString(vd, "direct3d9-shader");
    if (!selected_shader)
        return VLC_SUCCESS; /* Nothing to do */

    const char *shader_source_builtin = NULL;
    char *shader_source_file = NULL;
    FILE *fs = NULL;

    for (size_t i = 0; i < BUILTIN_SHADERS_COUNT; ++i) {
        if (!strcmp(selected_shader, builtin_shaders[i].name)) {
            shader_source_builtin = builtin_shaders[i].code;
            break;
        }
    }

    if (shader_source_builtin) {
        /* A builtin shader was selected. */
        int err = Direct3D9CompileShader(vd, shader_source_builtin, strlen(shader_source_builtin));
        if (err)
            goto error;
    } else {
        if (strcmp(selected_shader, SELECTED_SHADER_FILE))
            goto error; /* Unrecognized entry in the list. */
        /* The source code of the shader needs to be read from a file. */
        char *filepath = var_InheritString(vd, "direct3d9-shader-file");
        if (!filepath || !*filepath)
        {
            free(filepath);
            goto error;
        }
        /* Open file, find its size with fseek/ftell and read its content in a buffer. */
        fs = vlc_fopen(filepath, "rb");
        if (!fs)
            goto error;
        int ret = fseek(fs, 0, SEEK_END);
        if (ret == -1)
            goto error;
        long length = ftell(fs);
        if (length == -1 || length >= MAX_SHADER_FILE_SIZE)
            goto error;
        rewind(fs);
        shader_source_file = vlc_alloc(length, sizeof(*shader_source_file));
        if (!shader_source_file)
            goto error;
        ret = fread(shader_source_file, length, 1, fs);
        if (ret != 1)
            goto error;
        ret = Direct3D9CompileShader(vd, shader_source_file, length);
        if (ret)
            goto error;
    }

    free(selected_shader);
    free(shader_source_file);
    fclose(fs);

    return VLC_SUCCESS;

error:
    Direct3D9DestroyShaders(vd);
    free(selected_shader);
    free(shader_source_file);
    if (fs)
        fclose(fs);
    return VLC_EGENERIC;
}