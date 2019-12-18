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
typedef  int uint_fast32_t ;
typedef  int uint8_t ;
struct vlc_tls {int dummy; } ;
struct vlc_h2_frame {int* data; int /*<<< orphan*/ * next; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vlc_h2_frame*) ; 
 struct vlc_h2_frame* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/  (*) (struct vlc_h2_frame*),struct vlc_h2_frame*) ; 
 int vlc_https_recv (struct vlc_tls*,int*,int) ; 

__attribute__((used)) static struct vlc_h2_frame *vlc_h2_frame_recv(struct vlc_tls *tls)
{
    uint8_t header[9];
    ssize_t r = vlc_https_recv(tls, header, 9);
    /* TODO: actually block only until third byte */
    if (r < 3)
        return NULL;

    uint_fast32_t len = 9 + ((header[0] << 16) | (header[1] << 8) | header[2]);

    struct vlc_h2_frame *f = malloc(sizeof (*f) + len);
    if (unlikely(f == NULL))
        return NULL;

    f->next = NULL;
    memcpy(f->data, header, r);
    len -= r;

    if (len > 0)
    {
        vlc_cleanup_push(free, f);
        if (vlc_https_recv(tls, f->data + r, len) < (ssize_t)len)
        {
            free(f);
            f = NULL;
        }
        vlc_cleanup_pop();
    }
    return f;
}