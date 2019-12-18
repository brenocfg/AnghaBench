#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_url_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_12__ {int /*<<< orphan*/  pf_cancel; int /*<<< orphan*/  pf_display_login; } ;
typedef  TYPE_3__ vlc_dialog_cbs ;
struct TYPE_13__ {char* psz_realm; char* psz_authtype; char* psz_username; char* psz_password; } ;
typedef  TYPE_4__ vlc_credential ;
struct TYPE_11__ {int /*<<< orphan*/  psz_pwd; int /*<<< orphan*/  psz_user; int /*<<< orphan*/  psz_authtype; int /*<<< orphan*/  psz_realm; } ;
struct TYPE_10__ {int /*<<< orphan*/ * psz_pwd; int /*<<< orphan*/ * psz_user; } ;
struct testcase {char* psz_url; char* psz_realm; int b_found; char* psz_authtype; TYPE_2__ result; TYPE_1__ opt; } ;
struct dialog_ctx {int b_abort; struct testcase const* p_test; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cancel_cb ; 
 int /*<<< orphan*/  display_login_cb ; 
 int /*<<< orphan*/  printf (char*,unsigned int,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_UrlClean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_UrlParse (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlc_credential_clean (TYPE_4__*) ; 
 scalar_t__ vlc_credential_get (TYPE_4__*,int /*<<< orphan*/ *,char const*,char const*,char*,char*) ; 
 int /*<<< orphan*/  vlc_credential_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_credential_store (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_dialog_provider_set_callbacks (int /*<<< orphan*/ *,TYPE_3__ const*,struct dialog_ctx*) ; 

__attribute__((used)) static void
test(vlc_object_t *p_obj, unsigned int i_id, const struct testcase *p_test)
{
    printf("test(%u): url %s%s%s%s (%sexpected: %s:%s)\n", i_id, p_test->psz_url,
           p_test->psz_realm != NULL ? " (realm: " : "",
           p_test->psz_realm != NULL ? p_test->psz_realm : "",
           p_test->psz_realm != NULL ? ")" : "",
           p_test->b_found ? "" : "not ", p_test->result.psz_user,
           p_test->result.psz_pwd);

    const vlc_dialog_cbs cbs = {
        .pf_display_login = display_login_cb,
        .pf_cancel = cancel_cb,
    };
    struct dialog_ctx dialog_ctx = {
        .b_abort = false,
        .p_test = p_test,
    };
    vlc_dialog_provider_set_callbacks(p_obj, &cbs, &dialog_ctx);

    const char *psz_opt_user = NULL, *psz_opt_pwd = NULL;
    if (p_test->opt.psz_user != NULL)
    {
        psz_opt_user = "test-user";
        var_SetString(p_obj, psz_opt_user, p_test->opt.psz_user);
    }
    if (p_test->opt.psz_pwd != NULL)
    {
        psz_opt_pwd = "test-pwd";
        var_SetString(p_obj, psz_opt_pwd, p_test->opt.psz_pwd);
    }

    vlc_url_t url;
    vlc_UrlParse(&url, p_test->psz_url);

    vlc_credential credential;
    vlc_credential_init(&credential, &url);
    credential.psz_realm = p_test->psz_realm;
    credential.psz_authtype = p_test->psz_authtype;

    bool b_found = false;
    while (vlc_credential_get(&credential, p_obj, psz_opt_user, psz_opt_pwd,
                              "test authentication", "this a test"))
    {
        bool realm_match = !p_test->result.psz_realm
            || (credential.psz_realm
            && strcmp(credential.psz_realm, p_test->result.psz_realm) == 0);
        bool authtype_match = !p_test->result.psz_authtype
            || (credential.psz_authtype
            && strcmp(credential.psz_authtype, p_test->result.psz_authtype) == 0);

        if (realm_match && authtype_match
         && strcmp(credential.psz_username, p_test->result.psz_user) == 0
         && strcmp(credential.psz_password, p_test->result.psz_pwd) == 0)
        {
            b_found = true;
            break;
        }
    }
    assert(b_found == p_test->b_found);
    vlc_credential_store(&credential, p_obj);

    vlc_UrlClean(&url);
    vlc_credential_clean(&credential);

    vlc_dialog_provider_set_callbacks(p_obj, NULL, NULL);
}