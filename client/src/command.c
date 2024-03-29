#include <command.h>

#define COMMAND_LOCK       "lock"
#define COMMAND_UNLOCK     "unlock"
#define COMMAND_PING       "ping"
#define COMMAND_MESSAGE    "message"
#define COMMAND_POWEROFF   "poweroff"
#define COMMAND_ACTION     "action"
#define COMMAND_GETDETAILS "getdetails"
#define COMMAND_SCREENSHOT "screenshot"
#define COMMAND_NOTIFICATION "notification"
#define COMMAND_CLIENT "client"

#define COMMAND_LOCK_URI       "/lock"
#define COMMAND_UNLOCK_URI     "/unlock"
#define COMMAND_PING_URI       "/ping"
#define COMMAND_MESSAGE_URI    "/message"
#define COMMAND_POWEROFF_URI   "/poweroff"
#define COMMAND_ACTION_URI     "/action"
#define COMMAND_GETDETAILS_URI "/getdetails"
#define COMMAND_SCREENSHOT_URI "/screenshot"
#define COMMAND_NOTIFICATION_URI "/notification"
#define COMMAND_CLIENT_URI       "/client"

const struct command commands[] = {
	{COMMAND_LOCK       , COMMAND_LOCK_URI, ecafe_request_lock, NULL},
	{COMMAND_UNLOCK     , COMMAND_UNLOCK_URI     , ecafe_request_unlock, NULL},
	{COMMAND_PING       , COMMAND_PING_URI       , ecafe_request_ping, NULL},
	{COMMAND_MESSAGE    , COMMAND_MESSAGE_URI    , ecafe_request_message, NULL},
	{COMMAND_POWEROFF   , COMMAND_POWEROFF_URI   , ecafe_request_poweroff, NULL},
	{COMMAND_ACTION     , COMMAND_ACTION_URI     , ecafe_request_action, NULL},
	{COMMAND_GETDETAILS , COMMAND_GETDETAILS_URI , ecafe_request_getdetails, NULL},
	{COMMAND_SCREENSHOT , COMMAND_SCREENSHOT_URI , NULL, ecafe_request_screenshot},
	{COMMAND_NOTIFICATION , COMMAND_NOTIFICATION_URI , ecafe_request_notification, NULL},
	{COMMAND_CLIENT       , COMMAND_CLIENT_URI , ecafe_request_getdetails, NULL},
	{NULL, NULL, NULL}
};

int command_get_index(const char *cmd)
{
	for (int i = 0; commands[i].cmd; ++i) {
		if (strcmp(cmd, commands[i].cmd) == 0)
			return i;
	}

	return -1;
}

int command_get_index_by_uri(const char *uri)
{
	for (int i = 0; commands[i].uri; ++i) {
		if (strcmp(uri, commands[i].uri) == 0)
			return i;
	}

	return -1;
}