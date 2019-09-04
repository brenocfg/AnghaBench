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
typedef  int uint16 ;

/* Variables and functions */
#define  exDiscReasonAPIInitiatedDisconnect 147 
#define  exDiscReasonAPIInitiatedLogoff 146 
#define  exDiscReasonLicenseCantFinishProtocol 145 
#define  exDiscReasonLicenseCantUpgradeLicense 144 
#define  exDiscReasonLicenseClientEndedProtocol 143 
#define  exDiscReasonLicenseErrClientEncryption 142 
#define  exDiscReasonLicenseErrClientLicense 141 
#define  exDiscReasonLicenseErrClientMsg 140 
#define  exDiscReasonLicenseHwidDoesntMatchLicense 139 
#define  exDiscReasonLicenseInternal 138 
#define  exDiscReasonLicenseNoLicense 137 
#define  exDiscReasonLicenseNoLicenseServer 136 
#define  exDiscReasonLicenseNoRemoteConnections 135 
#define  exDiscReasonNoInfo 134 
#define  exDiscReasonOutOfMemory 133 
#define  exDiscReasonReplacedByOtherConnection 132 
#define  exDiscReasonServerDeniedConnection 131 
#define  exDiscReasonServerDeniedConnectionFips 130 
#define  exDiscReasonServerIdleTimeout 129 
#define  exDiscReasonServerLogonTimeout 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
print_disconnect_reason(uint16 reason)
{
	char *text;

	switch (reason)
	{
		case exDiscReasonNoInfo:
			text = "No information available";
			break;

		case exDiscReasonAPIInitiatedDisconnect:
			text = "Server initiated disconnect";
			break;

		case exDiscReasonAPIInitiatedLogoff:
			text = "Server initiated logoff";
			break;

		case exDiscReasonServerIdleTimeout:
			text = "Server idle timeout reached";
			break;

		case exDiscReasonServerLogonTimeout:
			text = "Server logon timeout reached";
			break;

		case exDiscReasonReplacedByOtherConnection:
			text = "The session was replaced";
			break;

		case exDiscReasonOutOfMemory:
			text = "The server is out of memory";
			break;

		case exDiscReasonServerDeniedConnection:
			text = "The server denied the connection";
			break;

		case exDiscReasonServerDeniedConnectionFips:
			text = "The server denied the connection for security reason";
			break;

		case exDiscReasonLicenseInternal:
			text = "Internal licensing error";
			break;

		case exDiscReasonLicenseNoLicenseServer:
			text = "No license server available";
			break;

		case exDiscReasonLicenseNoLicense:
			text = "No valid license available";
			break;

		case exDiscReasonLicenseErrClientMsg:
			text = "Invalid licensing message";
			break;

		case exDiscReasonLicenseHwidDoesntMatchLicense:
			text = "Hardware id doesn't match software license";
			break;

		case exDiscReasonLicenseErrClientLicense:
			text = "Client license error";
			break;

		case exDiscReasonLicenseCantFinishProtocol:
			text = "Network error during licensing protocol";
			break;

		case exDiscReasonLicenseClientEndedProtocol:
			text = "Licensing protocol was not completed";
			break;

		case exDiscReasonLicenseErrClientEncryption:
			text = "Incorrect client license enryption";
			break;

		case exDiscReasonLicenseCantUpgradeLicense:
			text = "Can't upgrade license";
			break;

		case exDiscReasonLicenseNoRemoteConnections:
			text = "The server is not licensed to accept remote connections";
			break;

		default:
			if (reason > 0x1000 && reason < 0x7fff)
			{
				text = "Internal protocol error";
			}
			else
			{
				text = "Unknown reason";
			}
	}
	fprintf(stderr, "disconnect: %s.\n", text);
}