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
typedef  scalar_t__ SOCKET ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  R_DELTA ; 
 int /*<<< orphan*/  R_ERROR ; 
 int /*<<< orphan*/  R_PROGRESS ; 
 int /*<<< orphan*/  R_STATUS ; 
 int /*<<< orphan*/  R_WARNING ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SOCKET_ERROR ; 
 char* WSAGetLastError () ; 
 scalar_t__ close_http (scalar_t__) ; 
 char const* errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ftell (int /*<<< orphan*/ *) ; 
 int memcmp (char*,char*,size_t) ; 
 scalar_t__ open_http (char*) ; 
 size_t recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,...) ; 
 scalar_t__ send_buf (scalar_t__,char const*,int) ; 
 scalar_t__ send_str (scalar_t__,char const*,int) ; 
 char* strmake (size_t*,char const*,char const*,...) ; 
 char* strstr (char*,char*) ; 

int
send_file (const char *name)
{
    SOCKET s;
    FILE *f;
#define BUFLEN 8192
    char buffer[BUFLEN+1];
    size_t bytes_read, total, filesize;
    char *str;
    int ret;

    /* RFC 2616 */
#define SEP "--8<--cut-here--8<--"
    static const char head[] = "POST /submit HTTP/1.0\r\n"
        "Host: test.winehq.org\r\n"
        "User-Agent: Winetest Shell\r\n"
        "Content-Type: multipart/form-data; boundary=\"" SEP "\"\r\n"
        "Content-Length: %u\r\n\r\n";
    static const char body1[] = "--" SEP "\r\n"
        "Content-Disposition: form-data; name=\"reportfile\"; filename=\"%s\"\r\n"
        "Content-Type: application/octet-stream\r\n\r\n";
    static const char body2[] = "\r\n--" SEP "\r\n"
        "Content-Disposition: form-data; name=\"submit\"\r\n\r\n"
        "Upload File\r\n"
        "--" SEP "--\r\n";

    s = open_http ("test.winehq.org");
    if (s == INVALID_SOCKET) return 1;

    f = fopen (name, "rb");
    if (!f) {
        report (R_WARNING, "Can't open file '%s': %d", name, errno);
        goto abort1;
    }
    fseek (f, 0, SEEK_END);
    filesize = ftell (f);
    if (filesize > 1.5*1024*1024) {
        report (R_WARNING,
                "File too big (%.1f MB > 1.5 MB); submitting partial report.",
                filesize/1024.0/1024);
        filesize = 1.5*1024*1024;
    }
    fseek (f, 0, SEEK_SET);

    report (R_STATUS, "Sending header");
    str = strmake (&total, body1, name);
    ret = send_str (s, head, filesize + total + sizeof body2 - 1) ||
        send_buf (s, str, total);
    free (str);
    if (ret) {
        report (R_WARNING, "Error sending header: %d, %d",
                errno, WSAGetLastError ());
        goto abort2;
    }

    report (R_STATUS, "Sending %u bytes of data", filesize);
    report (R_PROGRESS, 2, filesize);
    total = 0;
    while (total < filesize && (bytes_read = fread (buffer, 1, BUFLEN/2, f))) {
        if ((signed)bytes_read == -1) {
            report (R_WARNING, "Error reading log file: %d", errno);
            goto abort2;
        }
        total += bytes_read;
        if (total > filesize) bytes_read -= total - filesize;
        if (send_buf (s, buffer, bytes_read)) {
            report (R_WARNING, "Error sending body: %d, %d",
                    errno, WSAGetLastError ());
            goto abort2;
        }
        report (R_DELTA, bytes_read, "Network transfer: In progress");
    }
    fclose (f);

    if (send_buf (s, body2, sizeof body2 - 1)) {
        report (R_WARNING, "Error sending trailer: %d, %d",
                errno, WSAGetLastError ());
        goto abort1;
    }
    report (R_DELTA, 0, "Network transfer: Done");

    total = 0;
    while ((bytes_read = recv (s, buffer+total, BUFLEN-total, 0))) {
        if ((signed)bytes_read == SOCKET_ERROR) {
            report (R_WARNING, "Error receiving reply: %d, %d",
                    errno, WSAGetLastError ());
            goto abort1;
        }
        total += bytes_read;
        if (total == BUFLEN) {
            report (R_WARNING, "Buffer overflow");
            goto abort1;
        }
    }
    if (close_http (s)) {
        report (R_WARNING, "Error closing connection: %d, %d",
                errno, WSAGetLastError ());
        return 1;
    }

    str = strmake (&bytes_read, "Received %s (%d bytes).\n",
                   name, filesize);
    ret = memcmp (str, buffer + total - bytes_read, bytes_read);
    free (str);
    if (ret) {
        buffer[total] = 0;
        str = strstr (buffer, "\r\n\r\n");
        if (!str) str = buffer;
        else str = str + 4;
        report (R_ERROR, "Can't submit logfile '%s'. "
                "Server response: %s", name, str);
    }
    return ret;

 abort2:
    fclose (f);
 abort1:
    close_http (s);
    return 1;
}