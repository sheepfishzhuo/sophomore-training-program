#include <gtk/gtk.h>
int main(int argc, char *argv[])
{
	gtk_init(&argc,&argv);
	GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window,300,100);
	gtk_window_set_title(GTK_WINDOW(window),"羊鱼串");
	gtk_widget_show(window);
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();
	return 0;
}