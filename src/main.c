#include <gtk/gtk.h>
#include "ui.h"

static void on_activate(GtkApplication *app, gpointer user_data) {
    create_main_window(app, user_data);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    // Create a new application
    app = gtk_application_new("com.connecttrackpro.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);

    // Run the application
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
