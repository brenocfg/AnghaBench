#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {TYPE_2__* p_sys; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  psz_path; int /*<<< orphan*/  p_cfg; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_11__ {int /*<<< orphan*/ * context; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
struct TYPE_12__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_3__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AVUNERROR (int) ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  OutControl ; 
 int /*<<< orphan*/  OutSeek ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  Write ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_3__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int avio_open2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  config_ChainParse (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppsz_sout_options ; 
 char* var_InheritString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vlc_av_get_options (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vlc_init_avformat (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_obj_malloc (int /*<<< orphan*/ *,int) ; 

int OutOpenAvio(vlc_object_t *object)
{
    sout_access_out_t *access = (sout_access_out_t*)object;

    config_ChainParse( access, "sout-avio-", ppsz_sout_options, access->p_cfg );

    sout_access_out_sys_t *sys = vlc_obj_malloc(object, sizeof(*sys));
    if (!sys)
        return VLC_ENOMEM;
    sys->context = NULL;

    /* */
    vlc_init_avformat(object);

    if (!access->psz_path)
        return VLC_EGENERIC;

    int ret;
    AVDictionary *options = NULL;
    char *psz_opts = var_InheritString(access, "sout-avio-options");
    if (psz_opts) {
        vlc_av_get_options(psz_opts, &options);
        free(psz_opts);
    }
    ret = avio_open2(&sys->context, access->psz_path, AVIO_FLAG_WRITE,
                     NULL, &options);
    AVDictionaryEntry *t = NULL;
    while ((t = av_dict_get(options, "", t, AV_DICT_IGNORE_SUFFIX)))
        msg_Err( access, "unknown option \"%s\"", t->key );
    av_dict_free(&options);
    if (ret < 0) {
        errno = AVUNERROR(ret);
        msg_Err(access, "Failed to open %s", access->psz_path);
        return VLC_EGENERIC;
    }

    access->pf_write = Write;
    access->pf_control = OutControl;
    access->pf_seek = OutSeek;
    access->p_sys = sys;

    return VLC_SUCCESS;
}