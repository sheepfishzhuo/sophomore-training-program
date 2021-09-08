#include <gtk/gtk.h>
GtkWidget* entry_id;
GtkWidget* entry_passwd;
void my_clean(GtkButton* button, gpointer user_data);
int main(int argc, char *argv[])
{
    gtk_init(&argc,&argv);
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,500,300);
    gtk_window_set_title(GTK_WINDOW(window),"羊鱼串");

    GtkWidget* table = gtk_table_new(5,4,TRUE);
    gtk_container_add(GTK_CONTAINER(window),table);

    GtkWidget* label_title = gtk_label_new("羊鱼串奶茶店");
    gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,4,0,1);
    GtkWidget* label_pl = gtk_label_new("请输入您的账号和密码：");
    gtk_table_attach_defaults(GTK_TABLE(table),label_pl,0,4,1,2);
    GtkWidget* label_id = gtk_label_new("账号:");
    gtk_table_attach_defaults(GTK_TABLE(table),label_id,0,1,2,3);
    GtkWidget* label_passwd = gtk_label_new("密码:");
    gtk_table_attach_defaults(GTK_TABLE(table),label_passwd,0,1,3,4);

    entry_id = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entry_id,1,3,2,3);
    entry_passwd = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entry_passwd,1,3,3,4);

    GtkWidget* button_dl = gtk_button_new_with_label("注册");
    gtk_table_attach_defaults(GTK_TABLE(table),button_dl,0,1,4,5);
    GtkWidget* button_zc = gtk_button_new_with_label("登录");
    gtk_table_attach_defaults(GTK_TABLE(table),button_zc,1,2,4,5);
    GtkWidget* button_sx = gtk_button_new_with_label("刷新");
    gtk_table_attach_defaults(GTK_TABLE(table),button_sx,2,3,4,5);
    GtkWidget* button_tc = gtk_button_new_with_label("注销");
    gtk_table_attach_defaults(GTK_TABLE(table),button_tc,3,4,4,5);

    g_signal_connect(button_sx,"pressed",G_CALLBACK(my_clean),NULL);

    gtk_widget_show_all(window);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_main();
    return 0;
}

void my_clean(GtkButton* button,gpointer user_data)
{
    gtk_entry_set_text(GTK_ENTRY(entry_id),"");
    gtk_entry_set_text(GTK_ENTRY(entry_passwd),"");
}