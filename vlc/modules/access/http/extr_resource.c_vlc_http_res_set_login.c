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
struct vlc_http_resource {char* password; char* username; int /*<<< orphan*/ * response; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_http_msg_destroy (int /*<<< orphan*/ *) ; 
 int vlc_http_msg_get_status (int /*<<< orphan*/ *) ; 

int vlc_http_res_set_login(struct vlc_http_resource *res,
                           const char *username, const char *password)
{
    char *user = NULL;
    char *pass = NULL;

    if (username != NULL)
    {
        user = strdup(username);
        if (unlikely(user == NULL))
            return -1;

        pass = strdup((password != NULL) ? password : "");
        if (unlikely(pass == NULL))
        {
            free(user);
            return -1;
        }
    }

    free(res->password);
    free(res->username);
    res->username = user;
    res->password = pass;

    if (res->response != NULL && vlc_http_msg_get_status(res->response) == 401)
    {
        vlc_http_msg_destroy(res->response);
        res->response = NULL;
    }

    return 0;
}