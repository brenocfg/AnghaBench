#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_5__* p; } ;
typedef  TYPE_6__ vout_thread_t ;
struct TYPE_26__ {char* psz_string; int /*<<< orphan*/  i_int; } ;
typedef  TYPE_7__ vlc_value_t ;
struct TYPE_22__ {char* psz; } ;
struct TYPE_20__ {scalar_t__* psz; int /*<<< orphan*/ * i; } ;
struct TYPE_27__ {unsigned int list_count; TYPE_3__ orig; int /*<<< orphan*/ * list_text; TYPE_1__ list; } ;
typedef  TYPE_8__ module_config_t ;
struct TYPE_23__ {int is_interlaced; } ;
struct TYPE_21__ {int has_deint; } ;
struct TYPE_24__ {TYPE_4__ interlacing; TYPE_2__ filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeinterlaceCallback ; 
 int /*<<< orphan*/  DeinterlaceIsModeValid (scalar_t__) ; 
 int /*<<< orphan*/  VLC_VAR_ADDCHOICE ; 
 int VLC_VAR_BOOL ; 
 int /*<<< orphan*/  VLC_VAR_CLEARCHOICES ; 
 int VLC_VAR_DOINHERIT ; 
 int VLC_VAR_INTEGER ; 
 int /*<<< orphan*/  VLC_VAR_SETTEXT ; 
 int /*<<< orphan*/  VLC_VAR_SETVALUE ; 
 int VLC_VAR_STRING ; 
 TYPE_7__ _ (char*) ; 
 TYPE_8__* config_FindConfig (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  var_AddCallback (TYPE_6__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_Change (TYPE_6__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  var_Create (TYPE_6__*,char*,int) ; 
 char* var_CreateGetNonEmptyString (TYPE_6__*,char*) ; 
 int var_GetInteger (TYPE_6__*,char*) ; 
 char* var_GetNonEmptyString (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  var_SetInteger (TYPE_6__*,char*,int) ; 
 int /*<<< orphan*/  vlc_gettext (int /*<<< orphan*/ ) ; 

void vout_InitInterlacingSupport(vout_thread_t *vout)
{
    vlc_value_t val;

    msg_Dbg(vout, "Deinterlacing available");

    vout->p->filter.has_deint = false;

    /* Create the configuration variables */
    /* */
    var_Create(vout, "deinterlace", VLC_VAR_INTEGER | VLC_VAR_DOINHERIT );
    int deinterlace_state = var_GetInteger(vout, "deinterlace");

    var_Change(vout, "deinterlace", VLC_VAR_SETTEXT, _("Deinterlace"));

    const module_config_t *optd = config_FindConfig("deinterlace");
    var_Change(vout, "deinterlace", VLC_VAR_CLEARCHOICES);
    if (likely(optd != NULL))
        for (unsigned i = 0; i < optd->list_count; i++) {
            val.i_int = optd->list.i[i];
            var_Change(vout, "deinterlace", VLC_VAR_ADDCHOICE, val,
                       vlc_gettext(optd->list_text[i]));
        }
    var_AddCallback(vout, "deinterlace", DeinterlaceCallback, NULL);
    /* */
    var_Create(vout, "deinterlace-mode", VLC_VAR_STRING | VLC_VAR_DOINHERIT );
    char *deinterlace_mode = var_GetNonEmptyString(vout, "deinterlace-mode");

    var_Change(vout, "deinterlace-mode", VLC_VAR_SETTEXT,
               _("Deinterlace mode"));

    const module_config_t *optm = config_FindConfig("deinterlace-mode");
    var_Change(vout, "deinterlace-mode", VLC_VAR_CLEARCHOICES);
    if (likely(optm != NULL))
        for (unsigned i = 0; i < optm->list_count; i++) {
             if (!DeinterlaceIsModeValid(optm->list.psz[i]))
                 continue;

             val.psz_string  = (char *)optm->list.psz[i];
             var_Change(vout, "deinterlace-mode", VLC_VAR_ADDCHOICE,
                        val, vlc_gettext(optm->list_text[i]));
         }
    var_AddCallback(vout, "deinterlace-mode", DeinterlaceCallback, NULL);
    /* */
    var_Create(vout, "deinterlace-needed", VLC_VAR_BOOL);
    var_AddCallback(vout, "deinterlace-needed", DeinterlaceCallback, NULL);

    /* Override the initial value from filters if present */
    char *filter_mode = NULL;
    if (vout->p->filter.has_deint)
        filter_mode = var_CreateGetNonEmptyString(vout, "sout-deinterlace-mode");
    if (filter_mode) {
        deinterlace_state = 1;
        free(deinterlace_mode);
        deinterlace_mode = filter_mode;
    }

    /* */
    val.psz_string = deinterlace_mode ? deinterlace_mode : optm->orig.psz;
    var_Change(vout, "deinterlace-mode", VLC_VAR_SETVALUE, val);

    var_SetInteger(vout, "deinterlace", deinterlace_state);
    free(deinterlace_mode);

    vout->p->interlacing.is_interlaced = false;
}