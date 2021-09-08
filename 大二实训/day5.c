#include <stdio.h>
#include "sqlite3.h"
#include <gtk/gtk.h>
//-------所有的函数的外面，就是定义全局变量的地方--------
//也就是当前的文件内所有位置都可以使用
GtkWidget* window_main;
GtkWidget* window_menu;
GtkWidget* window_zc;
GtkWidget* window_login;
GtkWidget* entry_login_id;
GtkWidget* entry_login_passwd;
GtkWidget* entry_zc_id;
GtkWidget* entry_zc_passwd;
GtkWidget* entry_zc_name;

//--------其他函数-----------
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{   
    gtk_widget_set_app_paintable(widget, TRUE);     
    //允许窗口可以绘图  
    gtk_widget_realize(widget);     
    /* 更改背景图时，图片会重叠  * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。    */ 
    gtk_widget_queue_draw(widget);  
    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);   
    // 创建图片资源对象 // w, h是指定图片的宽度和高度  
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);     
    GdkPixmap *pixmap = NULL;   
    /* 创建pixmap图像;   * NULL：不需要蒙版;   * 123： 0~255，透明到不透明*/  
     gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128); 
     // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE 
     gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);     
     // 释放资源    
     g_object_unref(src_pixbuf);    
     g_object_unref(dst_pixbuf);    
     g_object_unref(pixmap);
 }







//-----------数据库函数区---------------
void my_sql_init(void)
{
    //打开数据库
    sqlite3* db;
    sqlite3_open("atm.db",&db);
    //看你要做什么
    //获取你需要的数据
    //组一个sql语句
    char sql1[100] = "create table user (name text,id text, rmb int,passwd text);";
    char sql2[100] = "create table login_text (id text,time time);";
    //看是读还是写---建表--写
    char *errmsg = NULL;
    sqlite3_exec(db,sql1,NULL,NULL,&errmsg);
    sqlite3_exec(db,sql2,NULL,NULL,&errmsg);
    //发给数据库
    //关闭数据库
    sqlite3_close(db);
}

//----------回调函数区-----------------

//--跳转区--
void window_main_to_window_menu(GtkButton* button,gpointer user_data)
{
    //显示下一个页面
    gtk_widget_show_all(window_menu);
    //隐藏当前的页面
    gtk_widget_hide_all(window_main);
}
void window_menu_to_window_zc(GtkButton* button,gpointer user_data)
{
    //先清空界面
    gtk_entry_set_text(GTK_ENTRY(entry_zc_id),"");
    gtk_entry_set_text(GTK_ENTRY(entry_zc_name),"");
    gtk_entry_set_text(GTK_ENTRY(entry_zc_passwd),"");
    //显示下一个页面
    gtk_widget_show_all(window_zc);
    //隐藏当前的页面
    gtk_widget_hide_all(window_menu);
}
void window_menu_to_window_dl(GtkButton* button,gpointer user_data)
{
    //先清空界面
    gtk_entry_set_text(GTK_ENTRY(entry_login_id),"");
    gtk_entry_set_text(GTK_ENTRY(entry_login_passwd),"");
    //显示下一个页面
    gtk_widget_show_all(window_login);
    //隐藏当前的页面
    gtk_widget_hide_all(window_menu);
}

void window_dl_to_window_menu(GtkButton* button,gpointer user_data)
{
    //显示下一个页面
    gtk_widget_show_all(window_menu);
    //隐藏当前的页面
    gtk_widget_hide_all(window_login);
}
void window_zc_to_window_menu(GtkButton* button,gpointer user_data)
{
    //显示下一个页面
    gtk_widget_show_all(window_menu);
    //隐藏当前的页面
    gtk_widget_hide_all(window_zc);
}
//-----------窗口初始化区---------------

void my_window_main_init(void)
{
    //创建窗口、设置窗口
    window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_main,1014,564);
    chang_background(window_main,1014,564,"./1014564.jpg");
    //创建布局、将布局放入窗口
    GtkWidget* table = gtk_table_new(3,4,TRUE);
    gtk_container_add(GTK_CONTAINER(window_main),table);
    //创建其他的控件、放入布局中
    GtkWidget*label_title = gtk_label_new("欢迎来到大江银行");
    gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>欢迎来到大江银行</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,4,0,1);
    GtkWidget* button = gtk_button_new_with_label("办理无卡业务");
    gtk_table_attach_defaults(GTK_TABLE(table),button,1,3,2,3);
    //  信号连接    
    g_signal_connect(button,"pressed",G_CALLBACK(window_main_to_window_menu),NULL);
}
void my_window_menu_init(void)
{
    //创建窗口、设置窗口
    window_menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_menu,1014,564);
    chang_background(window_menu,1014,564,"./1014564.jpg");
    //创建布局、将布局放入窗口
    GtkWidget* table = gtk_table_new(3,5,TRUE);
    gtk_container_add(GTK_CONTAINER(window_menu),table);
    //创建其他的控件、放入布局中
    GtkWidget*label_title = gtk_label_new("欢迎来到大江银行");
    gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>欢迎来到大江银行</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
    GtkWidget* button_zc = gtk_button_new_with_label("开户-注册");
    gtk_table_attach_defaults(GTK_TABLE(table),button_zc,0,2,1,2);
    GtkWidget* button_dl = gtk_button_new_with_label("老户-登录");
    gtk_table_attach_defaults(GTK_TABLE(table),button_dl,3,5,1,2);

    g_signal_connect(button_zc,"pressed",G_CALLBACK(window_menu_to_window_zc),NULL);

    g_signal_connect(button_dl,"pressed",G_CALLBACK(window_menu_to_window_dl),NULL);
}

void my_window_zc_init(void)
{
    //创建窗口、设置窗口
    window_zc = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_zc,1014,564);
    chang_background(window_zc,1014,564,"./1014564.jpg");
    //创建布局、将布局放入窗口
    GtkWidget* table = gtk_table_new(5,3,TRUE);
    gtk_container_add(GTK_CONTAINER(window_zc),table);
    //创建其他的控件、放入布局中
    GtkWidget*label_title = gtk_label_new("欢迎来到大江银行注册界面");
    gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>欢迎来到大江银行注册界面</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,3,0,1);
    GtkWidget*label_name = gtk_label_new("姓名：");
    gtk_label_set_markup(GTK_LABEL(label_name),"<span foreground='red'   font_desc='27'>姓名：</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_name,0,1,1,2);
    GtkWidget*label_id = gtk_label_new("ID：");
    gtk_label_set_markup(GTK_LABEL(label_id),"<span foreground='red'   font_desc='27'>ID：</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_id,0,1,2,3);
    GtkWidget*label_passwd = gtk_label_new("密码：");
    gtk_label_set_markup(GTK_LABEL(label_passwd),"<span foreground='red'   font_desc='27'>密码：</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_passwd,0,1,3,4);

    //输入框是全局变量因此直接使用
    entry_zc_name = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entry_zc_name,1,2,1,2);
    entry_zc_id = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entry_zc_id,1,2,2,3);
    entry_zc_passwd = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entry_zc_passwd,1,2,3,4);
    GtkWidget* button_zc = gtk_button_new_with_label("注册");
    gtk_table_attach_defaults(GTK_TABLE(table),button_zc,0,1,4,5);
    GtkWidget* button_sx = gtk_button_new_with_label("刷新");
    gtk_table_attach_defaults(GTK_TABLE(table),button_sx,1,2,4,5);
    GtkWidget* button_fh = gtk_button_new_with_label("返回");
    gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,4,5);
    g_signal_connect(button_fh,"pressed",G_CALLBACK(window_zc_to_window_menu),NULL);


}
void my_window_login_init(void)
{
    //创建窗口、设置窗口
    window_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_login,1014,564);
    chang_background(window_login,1014,564,"./1014564.jpg");
    //创建布局、将布局放入窗口
    GtkWidget* table = gtk_table_new(4,3,TRUE);
    gtk_container_add(GTK_CONTAINER(window_login),table);
    //创建其他的控件、放入布局中
    GtkWidget*label_title = gtk_label_new("欢迎来到大江银行登录界面");
    gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>欢迎来到大江银行登录界面</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,3,0,1);
    GtkWidget*label_id = gtk_label_new("ID：");
    gtk_label_set_markup(GTK_LABEL(label_id),"<span foreground='red'   font_desc='27'>ID：</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_id,0,1,1,2);
    GtkWidget*label_passwd = gtk_label_new("密码：");
    gtk_label_set_markup(GTK_LABEL(label_passwd),"<span foreground='red'   font_desc='27'>密码：</span>");
    //                              给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
    gtk_table_attach_defaults(GTK_TABLE(table),label_passwd,0,1,2,3);

    entry_login_id = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entry_login_id,1,2,1,2);
    entry_login_passwd = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table),entry_login_passwd,1,2,2,3);
    GtkWidget* button_login = gtk_button_new_with_label("注册");
    gtk_table_attach_defaults(GTK_TABLE(table),button_login,0,1,3,4);
    GtkWidget* button_sx = gtk_button_new_with_label("刷新");
    gtk_table_attach_defaults(GTK_TABLE(table),button_sx,1,2,3,4);
    GtkWidget* button_fh = gtk_button_new_with_label("返回");
    gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,3,4);
    g_signal_connect(button_fh,"pressed",G_CALLBACK(window_dl_to_window_menu),NULL);

}

//-----------main函数区----------------
int main(int argc, char  *argv[])//由于要写GTK所以去掉const
{
    my_sql_init();//初始化数据库
    gtk_init(&argc,&argv);//初始化gtk环境
    my_window_main_init();//主窗口初始化（创建）
    my_window_menu_init();
    my_window_zc_init();
    my_window_login_init();
    //显示主窗口
    gtk_widget_show_all(window_main);
    g_signal_connect(window_main,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_main();

    return 0;
}

