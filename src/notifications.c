#include <stdio.h>
#include "notifications.h"

void send_notification(const char *title, const char *message) {
    printf("Notification: %s - %s\n", title, message);
}
