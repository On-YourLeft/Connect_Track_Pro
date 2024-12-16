#include <gtk/gtk.h>

// Function to load CSS
void load_css() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();

    gtk_css_provider_load_from_path(provider, "assets/style.css");
    gtk_style_context_add_provider_for_display(
        display,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER
    );
}

// Function to create the main window
void create_main_window(GtkApplication *app, gpointer user_data) {
    (void)user_data; // Mark 'user_data' as unused

    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Connect Track Pro");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Load CSS
    load_css();

    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);

    button = gtk_button_new_with_label("Click Me");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

    gtk_widget_set_visible(window, TRUE);
}