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

/* Variables and functions */
#define  WSAEACCES 169 
#define  WSAEADDRINUSE 168 
#define  WSAEADDRNOTAVAIL 167 
#define  WSAEAFNOSUPPORT 166 
#define  WSAEALREADY 165 
#define  WSAECONNABORTED 164 
#define  WSAECONNREFUSED 163 
#define  WSAECONNRESET 162 
#define  WSAEDESTADDRREQ 161 
#define  WSAEDISCON 160 
#define  WSAEFAULT 159 
#define  WSAEHOSTDOWN 158 
#define  WSAEHOSTUNREACH 157 
#define  WSAEINPROGRESS 156 
#define  WSAEINTR 155 
#define  WSAEINVAL 154 
#define  WSAEISCONN 153 
#define  WSAEMFILE 152 
#define  WSAEMSGSIZE 151 
#define  WSAENETDOWN 150 
#define  WSAENETRESET 149 
#define  WSAENETUNREACH 148 
#define  WSAENOBUFS 147 
#define  WSAENOPROTOOPT 146 
#define  WSAENOTCONN 145 
#define  WSAENOTSOCK 144 
#define  WSAEOPNOTSUPP 143 
#define  WSAEPFNOSUPPORT 142 
#define  WSAEPROCLIM 141 
#define  WSAEPROTONOSUPPORT 140 
#define  WSAEPROTOTYPE 139 
#define  WSAESHUTDOWN 138 
#define  WSAESOCKTNOSUPPORT 137 
#define  WSAETIMEDOUT 136 
#define  WSAEWOULDBLOCK 135 
#define  WSAHOST_NOT_FOUND 134 
#define  WSANOTINITIALISED 133 
#define  WSANO_DATA 132 
#define  WSANO_RECOVERY 131 
#define  WSASYSNOTREADY 130 
#define  WSATRY_AGAIN 129 
#define  WSAVERNOTSUPPORTED 128 

__attribute__((used)) static const char *wstrerror(int err) {
    switch (err) {
        case WSAEINTR: return "Interrupted function call";
        case WSAEACCES: return "Permission denied";
        case WSAEFAULT: return "Bad address";
        case WSAEINVAL: return "Invalid argument";
        case WSAEMFILE: return "Too many open files";
        case WSAEWOULDBLOCK: return "Resource temporarily unavailable";
        case WSAEINPROGRESS: return "Operation now in progress";
        case WSAEALREADY: return "Operation already in progress";
        case WSAENOTSOCK: return "Socket operation on nonsocket";
        case WSAEDESTADDRREQ: return "Destination address required";
        case WSAEMSGSIZE: return "Message too long";
        case WSAEPROTOTYPE: return "Protocol wrong type for socket";
        case WSAENOPROTOOPT: return "Bad protocol option";
        case WSAEPROTONOSUPPORT: return "Protocol not supported";
        case WSAESOCKTNOSUPPORT: return "Socket type not supported";
        case WSAEOPNOTSUPP: return "Operation not supported";
        case WSAEPFNOSUPPORT: return "Protocol family not supported";
        case WSAEAFNOSUPPORT: 
            return "Address family not supported by protocol family"; 
        case WSAEADDRINUSE: return "Address already in use";
        case WSAEADDRNOTAVAIL: return "Cannot assign requested address";
        case WSAENETDOWN: return "Network is down";
        case WSAENETUNREACH: return "Network is unreachable";
        case WSAENETRESET: return "Network dropped connection on reset";
        case WSAECONNABORTED: return "Software caused connection abort";
        case WSAECONNRESET: return "Connection reset by peer";
        case WSAENOBUFS: return "No buffer space available";
        case WSAEISCONN: return "Socket is already connected";
        case WSAENOTCONN: return "Socket is not connected";
        case WSAESHUTDOWN: return "Cannot send after socket shutdown";
        case WSAETIMEDOUT: return "Connection timed out";
        case WSAECONNREFUSED: return "Connection refused";
        case WSAEHOSTDOWN: return "Host is down";
        case WSAEHOSTUNREACH: return "No route to host";
        case WSAEPROCLIM: return "Too many processes";
        case WSASYSNOTREADY: return "Network subsystem is unavailable";
        case WSAVERNOTSUPPORTED: return "Winsock.dll version out of range";
        case WSANOTINITIALISED: 
            return "Successful WSAStartup not yet performed";
        case WSAEDISCON: return "Graceful shutdown in progress";
        case WSAHOST_NOT_FOUND: return "Host not found";
        case WSATRY_AGAIN: return "Nonauthoritative host not found";
        case WSANO_RECOVERY: return "Nonrecoverable name lookup error"; 
        case WSANO_DATA: return "Valid name, no data record of requested type";
        default: return "Unknown error";
    }
}