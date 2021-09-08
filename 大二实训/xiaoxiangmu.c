#include <stdio.h>
#include "sqlite3.h"
#include <gtk/gtk.h>
//------------函数声明区



//-=------------全局变量区
GtkWidget* window_main;
GtkWidget* window_admin_dl;
GtkWidget* window_admin_zc;
GtkWidget* e_admin_dl_id;
GtkWidget* e_admin_dl_passwd;
GtkWidget* e_admin_zc_name;
GtkWidget* e_admin_zc_id;
GtkWidget* e_admin_zc_passwd;
//数据库的初始化工作：创建数据库表
void  my_sqlite_init(void)
{
    sqlite3* db;
    sqlite3_open("datui.db",&db);
    char *errmsg = NULL;
    sqlite3_exec(db,"create table admin (name text, id text, passwd text);",NULL,NULL,&errmsg);
    sqlite3_close(db);
}
void do_admin_zc(GtkButton *button ,gpointer user_data)
{
    //查询注册没有
    const char * name = gtk_entry_get_text(GTK_ENTRY(e_admin_zc_name));
    const char * id = gtk_entry_get_text(GTK_ENTRY(e_admin_zc_id));
    const char * passwd = gtk_entry_get_text(GTK_ENTRY(e_admin_zc_passwd));
    char haha1[100] = "";
    sprintf(haha1,"select *from admin where id = \'%s\'  or name = \'%s\';",id,name);
    sqlite3* db;
    sqlite3_open("datui.db",&db);
    char *errmsg = NULL;
    char **table = NULL;
    int r=0,c=0;
    sqlite3_get_table(db,haha1,&table,&r,&c,&errmsg);
    if (r!=0)
    {
        gtk_entry_set_text(GTK_ENTRY(e_admin_zc_id),"您已经注册过了");
        gtk_entry_set_text(GTK_ENTRY(e_admin_zc_name),"您已经注册过了");
        gtk_entry_set_text(GTK_ENTRY(e_admin_zc_passwd),"您已经注册过了");
        sqlite3_close(db);
        return;
    }
    char haha2[100] = "";
    sprintf(haha2,"insert into admin values (\'%s\',\'%s\',\'%s\');",name,id,passwd);
    errmsg =NULL;
    sqlite3_exec(db,haha2,NULL,NULL,&errmsg);
    if (errmsg == NULL)
    {
        gtk_entry_set_text(GTK_ENTRY(e_admin_zc_name),"您已经注册成功");
    }
    sqlite3_close(db);
}
void do_admin_dl(GtkButton *button ,gpointer user_data)
{
    //查询注册没有
    
    const char * id = gtk_entry_get_text(GTK_ENTRY(e_admin_dl_id));
    const char * passwd = gtk_entry_get_text(GTK_ENTRY(e_admin_dl_passwd));
    char haha1[100] = "";
    sprintf(haha1,"select *from admin where id = \'%s\'  and passwd = \'%s\';",id,passwd);
    sqlite3* db;
    sqlite3_open("datui.db",&db);
    char *errmsg = NULL;
    char **table = NULL;
    int r=0,c=0;
    sqlite3_get_table(db,haha1,&table,&r,&c,&errmsg);
    if (r!=0)
    {
        gtk_entry_set_text(GTK_ENTRY(e_admin_dl_id),"成功登录");
        sqlite3_close(db);
        //跳转就行
        return;
    }
    gtk_entry_set_text(GTK_ENTRY(e_admin_dl_id),"输入不正确");
    
    sqlite3_close(db);
}

//数据库的开发思维：
//1.思考自己要做什么数据库操作
//2.获取你需要的数据
//3.组一个你实现自己数据库控制的sql语句
//4.看sql语句是读还是写
//  读：  sqlite3_get_table
//  写：  sqlite3_exec
//5.关闭数据库
//-------------------------跳转回调函数区--------
void main_to_admin_dl(GtkButton *button ,gpointer user_data)
{
    gtk_entry_set_text(GTK_ENTRY(e_admin_dl_id),"");
    gtk_entry_set_text(GTK_ENTRY(e_admin_dl_passwd),"");
    gtk_widget_show_all(window_admin_dl);
    gtk_widget_hide_all(window_main);
}
void admin_dl_to_main(GtkButton *button ,gpointer user_data)
{
    gtk_widget_hide_all(window_admin_dl);
    gtk_widget_show_all(window_main);
}
void admin_dl_to_zc(GtkButton *button ,gpointer user_data)
{
    gtk_entry_set_text(GTK_ENTRY(e_admin_zc_name),"");
    gtk_entry_set_text(GTK_ENTRY(e_admin_zc_id),"");
    gtk_entry_set_text(GTK_ENTRY(e_admin_zc_passwd),"");
    gtk_widget_hide_all(window_admin_dl);
    gtk_widget_show_all(window_admin_zc);
}
void admin_zc_to_dl(GtkButton *button ,gpointer user_data)
{
    gtk_entry_set_text(GTK_ENTRY(e_admin_dl_id),"");
    gtk_entry_set_text(GTK_ENTRY(e_admin_dl_passwd),"");
    gtk_widget_show_all(window_admin_dl);
    gtk_widget_hide_all(window_admin_zc);
}
//---------------------------外部函数用于设置背景图
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
    GdkPixmap *pixmap = NULL;   /* 创建pixmap图像;   * NULL：不需要蒙版;   * 123： 0~255，透明到不透明     */ 
    gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);  
    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE  
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);  // 释放资源 
    g_object_unref(src_pixbuf); 
    g_object_unref(dst_pixbuf); 
    g_object_unref(pixmap);
}


//------------------------------页面区-----------
void  window_main_init(void)
{
    window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_main,714,447);
    chang_background(window_main,714,447,"1.png");
    GtkWidget* table_main  = gtk_table_new(2,3,TRUE);//5行3列均匀排放
    gtk_container_add(GTK_CONTAINER(window_main),table_main);
    GtkWidget* l_main_title  = gtk_label_new("大腿零售");
    gtk_table_attach_defaults(GTK_TABLE(table_main),l_main_title,0,3,0,1);
    GtkWidget* b_main_boss = gtk_button_new_with_label("老板");
    gtk_table_attach_defaults(GTK_TABLE(table_main),b_main_boss,0,1,1,2);
    GtkWidget* b_main_admin = gtk_button_new_with_label("员工");
    gtk_table_attach_defaults(GTK_TABLE(table_main),b_main_admin,1,2,1,2);
    GtkWidget* b_main_user = gtk_button_new_with_label("客户");
    gtk_table_attach_defaults(GTK_TABLE(table_main),b_main_user,2,3,1,2);

    //信号连接
    g_signal_connect(b_main_admin,"pressed",G_CALLBACK(main_to_admin_dl),NULL);
}
void  window_admin_dl_init(void)
{
    window_admin_dl = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_admin_dl,714,447);
    chang_background(window_admin_dl,714,447,"1.png");
    GtkWidget* table_admin_dl  = gtk_table_new(4,3,TRUE);//5行3列均匀排放
    gtk_container_add(GTK_CONTAINER(window_admin_dl),table_admin_dl);
    GtkWidget* l_admin_dl_title  = gtk_label_new("大腿零售员工登录");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),l_admin_dl_title,0,3,0,1);
    GtkWidget* l_admin_dl_id  = gtk_label_new("工号：");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),l_admin_dl_id,0,1,1,2);
    GtkWidget* l_admin_dl_passwd = gtk_label_new("密码：");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),l_admin_dl_passwd,0,1,2,3);

    e_admin_dl_id = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),e_admin_dl_id,1,2,1,2);
    e_admin_dl_passwd = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),e_admin_dl_passwd,1,2,2,3);

    GtkWidget* b_admin_dl_dl = gtk_button_new_with_label("登录");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),b_admin_dl_dl,0,1,3,4);
    GtkWidget* b_admin_dl_zc = gtk_button_new_with_label("注册");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),b_admin_dl_zc,1,2,3,4);
    GtkWidget* b_admin_dl_fh = gtk_button_new_with_label(" 返回");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_dl),b_admin_dl_fh,2,3,3,4);
    //信号连接
    g_signal_connect(b_admin_dl_fh,"pressed",G_CALLBACK(admin_dl_to_main),NULL);
    g_signal_connect(b_admin_dl_zc,"pressed",G_CALLBACK(admin_dl_to_zc),NULL);

    g_signal_connect(b_admin_dl_dl,"pressed",G_CALLBACK(do_admin_dl),NULL);

}

void  window_admin_zc_init(void)
{
    window_admin_zc = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window_admin_zc,714,447);
    chang_background(window_admin_zc,714,447,"1.png");
    GtkWidget* table_admin_zc  = gtk_table_new(5,3,TRUE);//5行3列均匀排放
    gtk_container_add(GTK_CONTAINER(window_admin_zc),table_admin_zc);
    GtkWidget* l_title  = gtk_label_new("大腿零售员工注册");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),l_title,0,3,0,1);
    GtkWidget* l_name  = gtk_label_new("姓名：");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),l_name,0,1,1,2);
    GtkWidget* l_id  = gtk_label_new("工号：");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),l_id,0,1,2,3);
    GtkWidget* l_passwd = gtk_label_new("密码：");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),l_passwd,0,1,3,4);
    e_admin_zc_name = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),e_admin_zc_name,1,2,1,2);
    e_admin_zc_id = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),e_admin_zc_id,1,2,2,3);
    e_admin_zc_passwd = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),e_admin_zc_passwd,1,2,3,4);

    GtkWidget* b_zc = gtk_button_new_with_label("注册");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),b_zc,0,1,4,5);
    GtkWidget* b_qk = gtk_button_new_with_label("清空");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),b_qk,1,2,4,5);
    GtkWidget* b_fh = gtk_button_new_with_label("返回");
    gtk_table_attach_defaults(GTK_TABLE(table_admin_zc),b_fh,2,3,4,5);
    //信号连接
    g_signal_connect(b_fh,"pressed",G_CALLBACK(admin_zc_to_dl),NULL);
    g_signal_connect(b_zc,"pressed",G_CALLBACK(do_admin_zc),NULL);
    
    
}


int main(int argc, char  *argv[])
{
    my_sqlite_init();
    gtk_init(&argc,&argv);
    window_main_init();//让这个页面存在
    window_admin_dl_init();
    window_admin_zc_init();
    //只给主窗口设置关闭信号
    g_signal_connect(window_main,"destroy" , G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show_all(window_main);//你想让谁第一个显示就show谁
    gtk_main();
    return 0;
}