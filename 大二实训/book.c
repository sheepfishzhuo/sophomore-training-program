#include <stdio.h>
#include "sqlite3.h"
#include <gtk/gtk.h>
//-------所有的函数的外面，就是定义全局变量的地方--------
//也就是当前的文件内所有位置都可以使用
GtkWidget* window_main;
GtkWidget* window_menu;
GtkWidget* window_zc;
GtkWidget* window_yk;
GtkWidget* window_login;
GtkWidget* window_book;
GtkWidget* window_book1;
GtkWidget* window_waiter;
GtkWidget* window_food;
GtkWidget* window_drink;
GtkWidget* window_connect;
GtkWidget* entry_login_id;
GtkWidget* entry_login_passwd;
GtkWidget* entry_zc_id;
GtkWidget* entry_zc_passwd;
GtkWidget* entry_zc_name;
GtkWidget* window_user_menu;
GtkWidget* window_user_cx;
GtkWidget* window_user_ck;
GtkWidget* label_user_cx_yue;
GtkWidget* entry_ck_rmb;

//--------其他函数-----------
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{	
	gtk_widget_set_app_paintable(widget, TRUE);		
	//允许窗口可以绘图	
	gtk_widget_realize(widget);	 	
	/* 更改背景图时，图片会重叠	 * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。	 */	
	gtk_widget_queue_draw(widget); 	
	GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);	
	// 创建图片资源对象	// w, h是指定图片的宽度和高度	
	GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR); 	
	GdkPixmap *pixmap = NULL; 	
	/* 创建pixmap图像; 	 * NULL：不需要蒙版; 	 * 123： 0~255，透明到不透明*/	
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
void window_menu_to_window_yk(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_yk);
	//隐藏当前的页面
	gtk_widget_hide_all(window_menu);
}
void window_dl_to_window_yk(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_yk);
	//隐藏当前的页面
	gtk_widget_hide_all(window_zc);
}
void window_yk_to_window_book(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_book);
	//隐藏当前的页面
	gtk_widget_hide_all(window_yk);
}
void window_hy_to_window_book(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_book1);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
void window_hy_to_window_waiter(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_waiter);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
void window_hy_to_window_food(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_food);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
void window_hy_to_window_drink(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_drink);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
void window_hy_to_window_connect(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_connect);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
void window_book_to_window_yk(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_yk);
	//隐藏当前的页面
	gtk_widget_hide_all(window_book);
}
void window_book_to_window_hy(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_user_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_book1);
}
void window_waiter_to_window_hy(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_user_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_waiter);
}
void window_food_to_window_hy(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_user_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_food);
}
void window_drink_to_window_hy(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_user_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_drink);
}
void window_connect_to_window_hy(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_user_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_connect);
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
	gtk_widget_hide_all(window_yk);
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
void window_dl_to_window_menu1(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_yk);
}
void window_zc_to_window_menu(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_zc);
}
void window_menu_to_window_fh()
{
    //显示下一个页面
    gtk_widget_show_all(window_main);
    //隐藏当前的页面
    gtk_widget_hide_all(window_menu);
}
void window_user_menu_to_window_menu(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
void window_user_ck_to_window_user_menu(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_user_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_ck);
}
void window_user_cx_to_window_user_menu(GtkButton* button,gpointer user_data)
{
	//显示下一个页面
	gtk_widget_show_all(window_user_menu);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_cx);
}
void window_user_menu_to_window_user_ck(GtkButton* button,gpointer user_data)
{
	//先清空界面
	gtk_entry_set_text(GTK_ENTRY(entry_ck_rmb),"");

	//显示下一个页面
	gtk_widget_show_all(window_user_ck);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
void window_user_menu_to_window_user_cx(GtkButton* button,gpointer user_data)
{
	//先查询余额，设置到label上
	sqlite3* db;
	sqlite3_open("atm.db",&db);

	const char * id = gtk_entry_get_text(GTK_ENTRY(entry_login_id));
	char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
	sprintf(sql1,"select rmb from user where id = \'%s\';",id);//进行组合
	char **table = NULL;
	int r = 0, c = 0;
	char *errmsg = NULL;
	sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
	//因为我们查询一列
	//因此我们的结果集应该是2行1列
	//第一行是列名称“rmb”   table[0]
	//第二行就是我们的rmb的值  table[1]
	//所以我们用的余额这个值就是table[1]
	if (r!=0)
	{
		//我们table[1]就是我们的余额的值
		char haha[200] = "";
		sprintf(haha,"<span foreground='red' font_desc='27'>%s</span>",table[1]);
		gtk_label_set_markup(GTK_LABEL(label_user_cx_yue),haha);
		sqlite3_close(db);
	}
	
	//显示下一个页面
	gtk_widget_show_all(window_user_cx);
	//隐藏当前的页面
	gtk_widget_hide_all(window_user_menu);
}
//----------刷新区--------
void user_do_zc_sx(GtkButton* button,gpointer user_data)
{
	//先清空界面
	gtk_entry_set_text(GTK_ENTRY(entry_zc_id),"");
	gtk_entry_set_text(GTK_ENTRY(entry_zc_name),"");
	gtk_entry_set_text(GTK_ENTRY(entry_zc_passwd),"");
}
void user_do_login_sx(GtkButton* button,gpointer user_data)
{
	//先清空界面
	gtk_entry_set_text(GTK_ENTRY(entry_login_id),"");
	gtk_entry_set_text(GTK_ENTRY(entry_login_passwd),"");
}
void user_do_cz_sx(GtkButton* button,gpointer user_data)
{
	gtk_entry_set_text(GTK_ENTRY(entry_ck_rmb),"");
}
//-----------数据库操作的回调函数----------
void user_do_zc_zc(GtkButton* button,gpointer user_data)
{
	sqlite3* db;
	sqlite3_open("atm.db",&db);

	const char * id = gtk_entry_get_text(GTK_ENTRY(entry_zc_id));
	const char * passwd = gtk_entry_get_text(GTK_ENTRY(entry_zc_passwd));
	const char * name = gtk_entry_get_text(GTK_ENTRY(entry_zc_name));
	
	char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
	sprintf(sql1,"select *from user where id = \'%s\';",id);//进行组合
	char **table = NULL;
	int r = 0, c = 0;
	char *errmsg = NULL;
	sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
	if(r!=0)//说明有效数据行不为0 也就是查询到了
	{
		gtk_entry_set_text(GTK_ENTRY(entry_zc_id),"您注册过了，请直接登录");
		sqlite3_close(db);
		return;
	}
	char sql2[100] = "";
	sprintf(sql2,"insert into user values (\'%s\',\'%s\',0,\'%s\');",name,id,passwd);
	//name text,id text, rmb int,passwd text
	sqlite3_exec(db,sql2,NULL,NULL,&errmsg);
	if(errmsg!=NULL)
		printf("%s\n", errmsg);
	gtk_entry_set_text(GTK_ENTRY(entry_zc_id),"注册成功");
		
	sqlite3_close(db);
}
void user_do_login_login(GtkButton* button,gpointer user_data)
{
	sqlite3* db;
	sqlite3_open("atm.db",&db);

	const char * id = gtk_entry_get_text(GTK_ENTRY(entry_login_id));
	const char * passwd = gtk_entry_get_text(GTK_ENTRY(entry_login_passwd));
	
	char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
	sprintf(sql1,"select *from user where id = \'%s\' and passwd = \'%s\';",id,passwd);//进行组合
	char **table = NULL;
	int r = 0, c = 0;
	char *errmsg = NULL;
	sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
	if (r != 0 )//查询到了就登录成功
	{
		gtk_widget_show_all(window_user_menu);
		gtk_widget_hide_all(window_login);
		sqlite3_close(db);
		return;
	}
	gtk_entry_set_text(GTK_ENTRY(entry_login_id),"您输入的账号或密码有误");
	sqlite3_close(db);
}
void user_do_ck(GtkButton* button,gpointer user_data)
{
	//打开数据库
	// 获取需要的数据
	// 组合一个sql语句
	// 发给数据库
	// 关闭数据库
	sqlite3* db;
	sqlite3_open("atm.db",&db);

	const char * id = gtk_entry_get_text(GTK_ENTRY(entry_login_id));
	const char * ck_rmb = gtk_entry_get_text(GTK_ENTRY(entry_ck_rmb));
	//先查询余额
	char sql1[100] = "";//定义一个字符数组用于存储你组合的sql语句
	sprintf(sql1,"select rmb from user where id = \'%s\';",id);//进行组合
	char **table = NULL;
	int r = 0, c = 0;
	char *errmsg = NULL;
	sqlite3_get_table(db,sql1,&table,&r,&c,&errmsg);
	if (r!=0)
	{
		//然后相加
		//然后修改到数据库中
		int rmb_new = atoi(table[1]) + atoi(ck_rmb);
		//atoi表示将数字字符串转为int
		char sql2[200] = "";
		sprintf(sql2,"update user set rmb = %d where id = \'%s\';",rmb_new,id);
		sqlite3_exec(db,sql2,NULL,NULL,&errmsg);
		//注意转账或取款的时候需要判断结果是否小于0
		sqlite3_close(db);
		gtk_entry_set_text(GTK_ENTRY(entry_ck_rmb),"充值成功");
	}
	
}


//-----------窗口初始化区---------------

void my_window_main_init(void)
{
	//创建窗口、设置窗口
	window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_main,1014,564);
	chang_background(window_main,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(6,6,TRUE);
	gtk_container_add(GTK_CONTAINER(window_main),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋！");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>欢迎来到魔幻森林书屋！</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,6,0,2);
	GtkWidget* button = gtk_button_new_with_label("点击这里进入书屋");
	gtk_table_attach_defaults(GTK_TABLE(table),button,2,4,3,4);
	//	信号连接	
	g_signal_connect(button,"pressed",G_CALLBACK(window_main_to_window_menu),NULL);
}
void my_window_menu_init(void)
{
	//创建窗口、设置窗口
	window_menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_menu,1014,564);
	chang_background(window_menu,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(6,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_menu),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋！");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>这里是魔幻森林书屋！</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
	GtkWidget* button_zc = gtk_button_new_with_label("游客登录");
	gtk_table_attach_defaults(GTK_TABLE(table),button_zc,1,2,2,3);
	GtkWidget* button_dl = gtk_button_new_with_label("VIP用户登录");
	gtk_table_attach_defaults(GTK_TABLE(table),button_dl,3,4,2,3);
	GtkWidget* button_fh = gtk_button_new_with_label("返回主菜单");
    gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,4,5);

	g_signal_connect(button_zc,"pressed",G_CALLBACK(window_menu_to_window_yk),NULL);

	g_signal_connect(button_dl,"pressed",G_CALLBACK(window_menu_to_window_dl),NULL);

	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_menu_to_window_fh),NULL);
}

void my_window_zc_init(void)
{
	//创建窗口、设置窗口
	window_zc = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_zc,1014,564);
	chang_background(window_zc,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(8,7,TRUE);
	gtk_container_add(GTK_CONTAINER(window_zc),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋注册界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋注册界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,7,0,1);
	GtkWidget*label_name = gtk_label_new("姓名：");
	gtk_label_set_markup(GTK_LABEL(label_name),"<span foreground='red'   font_desc='27'>姓名：</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_name,2,3,2,3);
	GtkWidget*label_id = gtk_label_new("ID：");
	gtk_label_set_markup(GTK_LABEL(label_id),"<span foreground='red'   font_desc='27'>ID：</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_id,2,3,3,4);
	GtkWidget*label_passwd = gtk_label_new("密码：");
	gtk_label_set_markup(GTK_LABEL(label_passwd),"<span foreground='red'   font_desc='27'>密码：</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_passwd,2,3,4,5);

	//输入框是全局变量因此直接使用
	entry_zc_name = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),entry_zc_name,3,5,2,3);
	entry_zc_id = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),entry_zc_id,3,5,3,4);
	entry_zc_passwd = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),entry_zc_passwd,3,5,4,5);
	GtkWidget* button_zc = gtk_button_new_with_label("注册");
	gtk_table_attach_defaults(GTK_TABLE(table),button_zc,1,2,6,7);
	GtkWidget* button_sx = gtk_button_new_with_label("刷新");
	gtk_table_attach_defaults(GTK_TABLE(table),button_sx,3,4,6,7);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,5,6,6,7);

	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_dl_to_window_yk),NULL);
	g_signal_connect(button_sx,"pressed",G_CALLBACK(user_do_zc_sx),NULL);
	g_signal_connect(button_zc,"pressed",G_CALLBACK(user_do_zc_zc),NULL);

}

void my_window_login_init(void)
{
	//创建窗口、设置窗口
	window_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_login,1014,564);
	chang_background(window_login,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(8,7,TRUE);
	gtk_container_add(GTK_CONTAINER(window_login),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋登录界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋登录界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,7,0,1);
	GtkWidget*label_id = gtk_label_new("ID：");
	gtk_label_set_markup(GTK_LABEL(label_id),"<span foreground='red'   font_desc='27'>ID：</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_id,2,3,2,3);
	GtkWidget*label_passwd = gtk_label_new("密码：");
	gtk_label_set_markup(GTK_LABEL(label_passwd),"<span foreground='red'   font_desc='27'>密码：</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_passwd,2,3,4,5);

	entry_login_id = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),entry_login_id,3,5,2,3);
	entry_login_passwd = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),entry_login_passwd,3,5,4,5);
	GtkWidget* button_login = gtk_button_new_with_label("登录");
	gtk_table_attach_defaults(GTK_TABLE(table),button_login,1,2,6,7);
	GtkWidget* button_sx = gtk_button_new_with_label("刷新");
	gtk_table_attach_defaults(GTK_TABLE(table),button_sx,3,4,6,7);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,5,6,6,7);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_dl_to_window_menu),NULL);
	g_signal_connect(button_sx,"pressed",G_CALLBACK(user_do_login_sx),NULL);
	g_signal_connect(button_login,"pressed",G_CALLBACK(user_do_login_login),NULL);
	
}
void my_window_yk_init(void)
{
	//创建窗口、设置窗口
	window_yk = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_yk,1014,564);
	chang_background(window_yk,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(8,6,TRUE);
	gtk_container_add(GTK_CONTAINER(window_yk),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋游客登录界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋游客登录界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,6,0,1);
	GtkWidget* button_1 = gtk_button_new_with_label("注册成为VIP用户");
	gtk_table_attach_defaults(GTK_TABLE(table),button_1,2,4,2,3);
	GtkWidget* button_2 = gtk_button_new_with_label("借一本书");
	gtk_table_attach_defaults(GTK_TABLE(table),button_2,2,4,4,5);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,4,6,7);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_dl_to_window_menu1),NULL);
	g_signal_connect(button_1,"pressed",G_CALLBACK(window_menu_to_window_zc),NULL);
	g_signal_connect(button_2,"pressed",G_CALLBACK(window_yk_to_window_book),NULL);
}
void my_window_user_menu_init(void)
{
	//创建窗口、设置窗口
	window_user_menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_user_menu,1014,564);
	chang_background(window_user_menu,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(10,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_user_menu),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋登录菜单");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋登录菜单</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,2);
	GtkWidget* button_ck = gtk_button_new_with_label("充值");
	gtk_table_attach_defaults(GTK_TABLE(table),button_ck,1,2,2,3);
	GtkWidget* button_cx = gtk_button_new_with_label("查询");
	gtk_table_attach_defaults(GTK_TABLE(table),button_cx,3,4,2,3);
	GtkWidget* button_food = gtk_button_new_with_label("来几片面包");
	gtk_table_attach_defaults(GTK_TABLE(table),button_food,1,2,4,5);
	GtkWidget* button_milk = gtk_button_new_with_label("来一杯牛奶");
	gtk_table_attach_defaults(GTK_TABLE(table),button_milk,3,4,4,5);
	GtkWidget* button_book = gtk_button_new_with_label("借书");
	gtk_table_attach_defaults(GTK_TABLE(table),button_book,1,2,6,7);
	GtkWidget* button_waiter = gtk_button_new_with_label("呼叫服务生");
	gtk_table_attach_defaults(GTK_TABLE(table),button_waiter,3,4,6,7);
	GtkWidget* button_connect = gtk_button_new_with_label("联系我们");
	gtk_table_attach_defaults(GTK_TABLE(table),button_connect,1,2,8,9);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,3,4,8,9);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_user_menu_to_window_menu),NULL);
	g_signal_connect(button_ck,"pressed",G_CALLBACK(window_user_menu_to_window_user_ck),NULL);
	g_signal_connect(button_cx,"pressed",G_CALLBACK(window_user_menu_to_window_user_cx),NULL);
	g_signal_connect(button_food,"pressed",G_CALLBACK(window_hy_to_window_food),NULL);
	g_signal_connect(button_book,"pressed",G_CALLBACK(window_hy_to_window_book),NULL);
	g_signal_connect(button_waiter,"pressed",G_CALLBACK(window_hy_to_window_waiter),NULL);
	g_signal_connect(button_milk,"pressed",G_CALLBACK(window_hy_to_window_drink),NULL);
	g_signal_connect(button_connect,"pressed",G_CALLBACK(window_hy_to_window_connect),NULL);
	
}
void yk_window_book_init(void)
{
	window_book = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_book,1014,564);
	chang_background(window_book,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(7,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_book),table);
	//创建其他的控件、放入布局中
	GtkWidget* label_title = gtk_label_new("欢迎来到魔幻森林书屋查询界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>游客借书状态查询界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
	GtkWidget* label_jy = gtk_label_new("您已成功借到书！");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_jy),"<span  font_desc='32'>您已成功借到书！</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_jy,1,4,1,3);
	GtkWidget* label_ts = gtk_label_new("提示");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_ts),"<span  font_desc='26'>【提示】：游客借书只能在书屋阅读</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_ts,1,4,3,4);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,5,6);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_book_to_window_yk),NULL);
}
void hy_window_book_init(void)
{
	window_book1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_book1,1014,564);
	chang_background(window_book1,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(7,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_book1),table);
	//创建其他的控件、放入布局中
	GtkWidget* label_title = gtk_label_new("欢迎来到魔幻森林书屋查询界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>VIP用户借书状态查询界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
	GtkWidget* label_jy = gtk_label_new("您已成功借到书！");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_jy),"<span  font_desc='32'>您已成功借到书！</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_jy,1,4,1,3);
	GtkWidget* label_ts = gtk_label_new("提示");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_ts),"<span  font_desc='26'>【提示】：VIP用户借书时长为7天</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_ts,1,4,3,4);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,5,6);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_book_to_window_hy),NULL);
}
void hy_windows_waiter_init(void)
{
	window_waiter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_waiter,1014,564);
	chang_background(window_waiter,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(7,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_waiter),table);
	//创建其他的控件、放入布局中
	GtkWidget* label_title = gtk_label_new("魔幻森林书屋呼叫服务生界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋呼叫服务生界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
	GtkWidget* label_hj = gtk_label_new("呼叫服务生");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_hj),"<span  font_desc='32'>服务生正在火速赶来为您服务！</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_hj,1,4,2,3);
	GtkWidget* label_ts = gtk_label_new("提示");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_ts),"<span  font_desc='26'>请您稍等片刻</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_ts,1,4,3,4);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,5,6);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_waiter_to_window_hy),NULL);
}
void hy_windows_food_init(void)
{
	window_food = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_food,1014,564);
	chang_background(window_food,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(7,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_food),table);
	//创建其他的控件、放入布局中
	GtkWidget* label_title = gtk_label_new("魔幻森林书屋食物订单界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋食物订单界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
	GtkWidget* label_mianbao = gtk_label_new("来一片面包");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_mianbao),"<span  font_desc='32'>您的面包正在加热中，预计还需1分钟！</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_mianbao,0,5,2,3);
	GtkWidget* label_ts = gtk_label_new("提示");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_ts),"<span  font_desc='26'>欢迎品尝来自森林深处的美味</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_ts,1,4,3,4);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,5,6);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_food_to_window_hy),NULL);
}
void hy_windows_drink_init(void)
{
	window_drink = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_drink,1014,564);
	chang_background(window_drink,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(7,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_drink),table);
	//创建其他的控件、放入布局中
	GtkWidget* label_title = gtk_label_new("魔幻森林书屋饮品订单界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋饮品订单界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
	GtkWidget* label_niunai = gtk_label_new("来一杯牛奶");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_niunai),"<span  font_desc='32'>您的牛奶正在加热中，预计还需半分钟！</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_niunai,0,5,2,3);
	GtkWidget* label_ts = gtk_label_new("提示");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_ts),"<span  font_desc='26'>欢迎品尝纯正鲜牛奶的美味</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_ts,1,4,3,4);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,5,6);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_drink_to_window_hy),NULL);
}
void hy_windows_connect_init(void)
{
	window_connect = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_connect,1014,564);
	chang_background(window_connect,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(9,5,TRUE);
	gtk_container_add(GTK_CONTAINER(window_connect),table);
	//创建其他的控件、放入布局中
	GtkWidget* label_title = gtk_label_new("联系我们");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林书屋联系我们界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,5,0,1);
	GtkWidget* label_dz = gtk_label_new("");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_dz),"<span  font_desc='26'>总店长：唐店长：QQ:1305876466</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_dz,1,4,1,2);
	GtkWidget* label_fdz = gtk_label_new("");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_fdz),"<span  font_desc='26'>副店长：蔡店长：QQ:2531004564</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_fdz,1,4,2,3);
	GtkWidget* label_jsry = gtk_label_new("");//新建一个空内容的label
	gtk_label_set_markup(GTK_LABEL(label_jsry),"<span  font_desc='26'>技术员：杨员工：QQ:2678660795</span>");
	gtk_table_attach_defaults(GTK_TABLE(table),label_jsry,1,4,3,4);
	GtkWidget *image_one =  gtk_image_new_from_file("./lx.png");
    //gtk_container_add(GTK_CONTAINER(hbox), image_one);// 添加到布局里
    gtk_table_attach_defaults(GTK_TABLE(table),image_one,2,3,4,6);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,2,3,7,8);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_connect_to_window_hy),NULL);
}
void my_window_user_cx_init(void)
{
	//创建窗口、设置窗口
	window_user_cx = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_user_cx,1014,564);
	chang_background(window_user_cx,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(6,7,TRUE);
	gtk_container_add(GTK_CONTAINER(window_user_cx),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋查询界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林币余额查询界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,7,0,1);
	GtkWidget*label_project = gtk_label_new("您的魔幻森林币余额为");
	gtk_label_set_markup(GTK_LABEL(label_project),"<span font_desc='26'>您的魔幻森林币余额为</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_project,1,4,2,3);
	label_user_cx_yue = gtk_label_new("");//新建一个空内容的label
	gtk_table_attach_defaults(GTK_TABLE(table),label_user_cx_yue,4,5,2,3);
	GtkWidget*label_danwei = gtk_label_new("币");
	gtk_label_set_markup(GTK_LABEL(label_danwei),"<span font_desc='26'>币</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_danwei,5,6,2,3);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,3,4,4,5);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_user_cx_to_window_user_menu),NULL);
	
	
}
void my_window_user_ck_init(void)
{
	//创建窗口、设置窗口
	window_user_ck = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request(window_user_ck,1014,564);
	chang_background(window_user_ck,1014,564,"./1014564.jpg");
	//创建布局、将布局放入窗口
	GtkWidget* table = gtk_table_new(8,7,TRUE);
	gtk_container_add(GTK_CONTAINER(window_user_ck),table);
	//创建其他的控件、放入布局中
	GtkWidget*label_title = gtk_label_new("欢迎来到魔幻森林书屋充值界面");
	gtk_label_set_markup(GTK_LABEL(label_title),"<span foreground='red' underline='double' underline_color='blue' font_desc='32'>魔幻森林币充值界面</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_title,0,7,0,2);
	GtkWidget* label = gtk_label_new("充值金额：");
	gtk_label_set_markup(GTK_LABEL(label),"<span  font_desc='28'>充值金额：</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label,1,3,3,4);
	
	entry_ck_rmb = gtk_entry_new();
	gtk_table_attach_defaults(GTK_TABLE(table),entry_ck_rmb,3,4,3,4);
	GtkWidget*label_danwei = gtk_label_new("币");
	gtk_label_set_markup(GTK_LABEL(label_danwei),"<span font_desc='26'>币</span>");
	//								给谁设置（label）。         字体颜色。   双下划线             下划线颜色。        字体大小。        文本内容
	gtk_table_attach_defaults(GTK_TABLE(table),label_danwei,4,6,3,4);
	GtkWidget* button_ck = gtk_button_new_with_label("充值");
	gtk_table_attach_defaults(GTK_TABLE(table),button_ck,1,2,6,7);
	GtkWidget* button_sx = gtk_button_new_with_label("刷新");
	gtk_table_attach_defaults(GTK_TABLE(table),button_sx,3,4,6,7);
	GtkWidget* button_fh = gtk_button_new_with_label("返回");
	gtk_table_attach_defaults(GTK_TABLE(table),button_fh,5,6,6,7);
	g_signal_connect(button_fh,"pressed",G_CALLBACK(window_user_ck_to_window_user_menu),NULL);
	g_signal_connect(button_ck,"pressed",G_CALLBACK(user_do_ck),NULL);
	g_signal_connect(button_sx,"pressed",G_CALLBACK(user_do_cz_sx),NULL);
	
}
//-----------main函数区----------------
int main(int argc, char  *argv[])//由于要写GTK所以去掉const
{
	my_sql_init();//初始化数据库
	gtk_init(&argc,&argv);//初始化gtk环境
	my_window_main_init();//主窗口初始化（创建）
	my_window_menu_init();
	my_window_zc_init();
	my_window_yk_init();
	my_window_login_init();
	my_window_user_menu_init();
	my_window_user_cx_init();
	my_window_user_ck_init();
	yk_window_book_init();
	hy_window_book_init();
	hy_windows_waiter_init();
	hy_windows_food_init();
	hy_windows_drink_init();
	hy_windows_connect_init();
	//显示主窗口
	gtk_widget_show_all(window_main);
	g_signal_connect(window_main,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_main();

	return 0;
}





