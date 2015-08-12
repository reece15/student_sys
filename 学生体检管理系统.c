/*
 * 学生体检信息管理系统
 * 
 * 默认用户名:admin      密码:admin 
 *  
 * VC 6.0
 *
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define QT "%d,%d,%lf,%lf,%lf\n"
#define PT &p1->old,&p1->sex,&p1->height,&p1->weight,&p1->Lung_vol
#define BUF_PQ "%s,%s,%d,%d,%.2lf,%.2lf,%.2lf\n",p1->name,p1->num,p1->old,p1->sex,p1->height,p1->weight,p1->Lung_vol
#define N sizeof(struct student_info)
#define menu_print "\n%-14s %-10s %-10s %-10s %-10s %-10s %-10s","姓名","学号","年龄","性别","身高(cm)","体重(kg)","肺活量(ml)"
#define STINFO  "%-14s %-10s %-10d %-10s %-10.2lf %-10.2lf %-10.2lf",p1->name,p1->num,p1->old,p1->sex == 1?"男":"女",p1->height,p1->weight,p1->Lung_vol
#define ST_SIX_INFO "%s %d %d %lf %lf %lf",p1->num,&p1->old,&p1->sex,&p1->height,&p1->weight,&p1->Lung_vol
#define M sizeof(struct find_link)
#define CHECK_INFO ((p1->sex != 0 && p1->sex != 1) || p1->height < 0 || p1->height > 300 || p1->Lung_vol <0 || p1->old < 0 || p1->old > 120 || p1->weight <0)
#define TURE 1
#define FALSE 0
#define T_T sizeof(struct sort_link)

typedef struct student_info
{
	char name[14];
	char num[10];
	int old;
	int sex;
	double height;
	double weight;
	double Lung_vol;
	struct student_info *next;
}st_info;		//学生体检信息数据结构

typedef struct find_link
{
	st_info *buf_find;
	struct find_link *next;
}find_link;		//存储查找到的结果的结点指针

typedef struct sort_link
{
	st_info *sort_point;
	struct sort_link *next;
}sort_link;			//对主链表的结点指针排序

unsigned int flag_page = 10;	//单页显示行数
unsigned int flag_login = FALSE;	//登陆标志  0匿名  1管理员
unsigned int flag_color = TURE;	//颜色开关  
unsigned int flag_file = TURE;		//文件加载成功标志
unsigned int flag_save = TURE;		//数据流已存标志

void system_init(st_info *buf_head,char *data_name);	//系统初始化
unsigned int login(char *local_name,char *local_password);			//登陆系统
void main_menu(char *local_name,char *local_password,char *data_name,st_info *buf_head);				//主菜单
void system_help();					//系统帮助与说明
void system_set(char *data_name);	//系统设置
int baseprint(st_info *buf_head,char *data_name);		//基本输出
int st_linklist(st_info *buf_head,char *data_name);			//生成用户录入链表
int find(st_info *buf_head,const int flag_num);	//查找信息，生成查询结果链表
void print_star();		//打印分割线
void print_tips(char *name);	//打印标题
int del_info(find_link *find_head,unsigned int flag_find);	//删除数据
int find_print(find_link *find_head,unsigned int flag_find);	//打印找到的结果
int change_info(find_link *find_head,unsigned int flag_find);	//修改学生信息
int free_find(find_link *find_head);	//释放查询结果链表
void myflush();
int save_file(void *head,char *data_name,size_t n);	//保存文件
void system_quit(st_info *buf_head,char *data_name);	//退出系统
int math_info(st_info *buf_head);	//数据处理
int sort_info(st_info *buf_head,char *data_name,const int check);	//排序
int sort_print(sort_link *sort_head,char *data_name);		//输出排序后链表
int sort_free(sort_link *sort_head);		//释放排序链表

int main(void)
{
	char *local_name = {"admin"};		
	char *local_password = {"admin"};		//管理员账户 密码
	char data_name[16]={"data.csv"};			//默认数据文件
	FILE *data_file = NULL;
    st_info *buf_head = NULL;
	buf_head = (st_info *)malloc(N);
	buf_head->next =NULL;
	system("mode con:cols=80 lines=30");
	system("color 0a");
	while(1)
	{
		main_menu(local_name,local_password,data_name,buf_head);
	}
}

void main_menu(char *local_name,char *local_password,char *data_name,st_info *buf_head)
{
	unsigned int switcher,n = 0,swap = 0;
	st_info *p1=NULL;
	do			
	{
		char system_input[20];
		system("cls");
		sprintf(system_input,"color 0%c",'a'+ (n == 100?n=0:n) % 5);
		++n;
		system(system_input);
		print_tips("学生体检信息管理系统");
		if(flag_login == 1)
			printf("\n\n\n\nDear admin, Welcome! \n\n\n\n");
		else
			printf("\n\nDear anonymous,Welcome! \n\nTips:Please Login In.\n\n\n\n");
		printf("\n\t\t   ┎──────────────────┒");
		printf("\n\t\t   ┃                                    ┃");
		printf("\n\t\t   ┃  1.系统帮助         2.系统设置     ┃");
		printf("\n\t\t   ┃                                    ┃");
		if(flag_login == 1)
		{
			printf("\n\t\t   ┃  3.浏览信息         4.查找信息     ┃");
			printf("\n\t\t   ┃                                    ┃");
			printf("\n\t\t   ┃  5.统计分析         6.录入数据     ┃");
			printf("\n\t\t   ┃                                    ┃");
			printf("\n\t\t   ┃  7.查找删除         8.查找修改     ┃");
			printf("\n\t\t   ┃                                    ┃");
		}
		printf("\n\t\t   ┃                                    ┃");
		if(flag_login == FALSE)
			printf("\n\t\t   ┃  3.登陆系统                        ┃");
		printf("\n\t\t   ┃                                    ┃");
		printf("\n\t\t   ┃*按相应数字进入子菜单  ESC:退出系统 ┃");
		printf("\n\t\t   ┖──────────────────┚\n");
		printf("\n-----Waiting...");
		if(swap == 0)
			_sleep(1000);
	//	flushall();
	}while(!(swap = kbhit()) && flag_color != 0); 
	switcher = getch();
	fflush(stdin);
	switch(switcher)
	{
	case '1':system_help();break;	
	case '2':system_set(data_name);break;	
	case '3':if(flag_login == TURE)
				baseprint(buf_head,data_name);	//输出所有信息	
			else
			{
				system("cls");
				flag_login = login(local_name,local_password);
				if (flag_login == TURE)
				{
					system("mode con:cols=80 lines=30");
					system_init(buf_head,data_name);
				}
				system("mode con:cols=80 lines=30");
			}
			break;	
	case '4':if(flag_login == TURE)
			 {
				 find(buf_head,0);fflush(stdin);
				 getch();
			 }
			break; 	//只查找，不修改或者删除
	case '5':if(flag_login == TURE);
				math_info(buf_head);
		     break;					
	case '6':if(flag_login == TURE)
				 st_linklist(buf_head,data_name);
			 fflush(stdin);
			 getch();
			 break;
	case '7':if(flag_login == TURE)
			 {
				if(find(buf_head,1) == 1)
					save_file(buf_head,data_name,N);
				fflush(stdin);
				getch();
			 }								//查找后可删除数据
			break;
	case '8':if(flag_login == TURE)
			 {
				 if(find(buf_head,2) == 1)			//查找后可修改数据
					save_file(buf_head,data_name,N);
				 fflush(stdin);
				 getch();
			 }
			break;
	case 27:system_quit(buf_head,data_name);break;
	default:break;
	}
}
void system_init(st_info *buf_head,char *data_name)
{
	FILE *p;
	int check;
	char ch; 
	st_info * p1 = NULL,*p2 = NULL;
	unsigned int value = 0,flag_eof = 0,i = 1,n = 0,len = 0;
	char *buffer = NULL;
	printf("\n\n****************************欢迎使用学生体检信息管理系统***********************");
	printf("\n\n\n >>>-----系统正在初始化...");
	if((p = fopen(data_name,"r")) == NULL)
	{
		printf("\n\n Warning!-----加载文件失败!%s不存在于当前目录!",data_name);
		if((p = fopen("data.csv.bk","r")) == NULL)
		{
			printf("\n\n Warning!-----备份文件不存在!");
			flag_file = FALSE;
			buf_head->next = NULL;
		}
		else
			printf("\n\n OK!-----尝试读取备份文件成功!");
	}
	if(flag_file == TURE)
	{
		printf("\n\n OK!-----读取文件成功!\n\n");
		ch=fgetc(p);
		if(ch==EOF)
		{
			printf("\n Warning!-----数据文件内容为空!\n\n");
			buf_head->next = NULL;
		}
		else
		{
			fseek(p,0,SEEK_END);
			len = ftell(p);
			rewind(p);
			p1 = (st_info *)malloc(N);
			buf_head->next = p1;
			while(!feof(p))
			{
				++value;
				n = 0;
				ch = '\0';
				memset(p1->name,'\0',sizeof(p1->name));
				memset(p1->num,'\0',sizeof(p1->num));
				while (1)
				{
					while((ch = fgetc(p)) == '\n' || ch == '\r');
					if(n >= 12 || ch == ',' || ch == ' ' || ch == EOF)
						break;
					*(p1->name + n) = ch;
					++n;
				}
				n = 0;
				ch = '\0';
				while (1)
				{
					while((ch = fgetc(p)) == '\n' || ch == '\r');
					if(n >= 13 || ch == ',' || ch == ' ' || ch == EOF)
						break;
					*(p1->num + n) = ch;
					++n;
				}
				check = fscanf(p,QT,PT);
				printf("\r Tips:-----正在验证数据，已完成: %4.1lf %%   当前项目:   %14s ",(double)ftell(p)/(double)len *100,p1->name);
				if(len < 1024 * 10)
					_sleep(10);
				if(check != 5 || CHECK_INFO)
				{
					printf("\n\n Warning!-----文件数据验证失败!在文件%s的数据第%u行中发现错误!请检查!",data_name,value);
					p1 = buf_head->next;
					while(i < value)
					{
						p2 = p1;
						p1 = p1->next;
						free(p2);
						++i;
					}
					buf_head->next = NULL;
					printf("\n\n OK!-----已释放内存!\n");
					break;
				}
				else
				{
					p2 = p1;
					p1 = (st_info *)malloc(N);
					p2->next = p1;
				}
			}
			if (buf_head->next !=NULL)
			{
				free(p1);
				p2->next = NULL;
				printf("\n\n OK!-----文件数据验证成功!已读取%u条数据!",value);
			}
		}
		fclose(p);
	}
	if(buf_head->next == NULL)
		printf("\n\n\n\n Warning!-----初始化并未全部完成!部分功能可能无法使用!按任意键进入系统!");
	else
		printf("\n\n\n\n OK!-----所有初始化完成!按任意键进入系统!");
	getch(); 
	return ;
}
unsigned int login(char *local_name,char *local_password)
{
	char user_name[16],user_password[16];
	char swap;
	int i,error = 0;
	system("mode con:cols=40 lines=15");
	while(1)
	{
		memset(user_name,'\0',sizeof(user_name));
		memset(user_password,'\0',sizeof(user_password));
		printf("\n\n\n\t\t管理员登陆\n\n\t*Tips:访 客 : anonymous");
		printf("\n  用户名：");
		for(i = 0;i < 15;i++)
		{
			swap=getchar();
			if(swap == '\n')
				break;
			else 
			{
				user_name[i] = swap;
			}
			
		}
		user_name[i]='\0';
		fflush(stdin);
		printf("\n  密  码：");
		for(i = 0;i < 15;i++)
		{
			swap = getch();
			if(swap == '\r'|| swap == '\n')
				break;
			else 
			{
				user_password[i] = swap;
				printf("*");
			}
			
		}
		user_password[i]='\0';
		system("cls");
		if(strcmp(user_password,local_password) != 0 || strcmp(user_name,local_name) !=0)
		{
			system("cls");
			printf("Warning: Error!-----用户名或密码错误！\n\t还可重试%d次***",2 - error);
			++error;
			if(error == 3)
			{
				printf("\n\n Warning!-----尝试次数已到!请等待3秒后再试");
				_sleep(2000);
				return FALSE;
			}
		}
		else
		{
			break;
		}
	} 
	return TURE;
}
void system_help()
{
	system("cls");
	printf("\n\n\n\n\n\t\t\t      *使用帮助&说明*\n\n\n");
	printf("\n\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	printf("\n\t┃                                                      ┃");
	printf("\n\t┃         1.本程序使用VC6.0,在WIN7下编写。             ┃");
	printf("\n\t┃                                                      ┃");
	printf("\n\t┃         2.程序界面可根据喜好在系统设置中进行设置。   ┃");
	printf("\n\t┃                                                      ┃");
	printf("\n\t┃         3.提交的过长字符串将被截断。                 ┃");
	printf("\n\t┃                                                      ┃");
	printf("\n\t┃         4.需要操作数据请登录。                       ┃");
	printf("\n\t┃                                                      ┃");
	printf("\n\t┃         5.作者：任强        时间： 2014-06-03        ┃");
	printf("\n\t┃                                                      ┃");
	printf("\n\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	printf("\n\n\n\n\n Tips:-----按任意键返回主菜单！");
	getch();

}
void system_set(char *data_name)
{
	char tmp;
	unsigned int flag_window = 0;
	while(1)
	{
		system("cls");
		print_tips(">>>     设置     <<<");
		printf("\n\n\n\n");
		printf("\n\t\t┏━━━━━━━━━━━━━━━━━━━━━┓");
		printf("\n\t\t┃                                          ┃");
		printf("\n\t\t┃         1.主菜单颜色闪动         %3s     ┃",flag_color ==TURE ?"开":"关");
		printf("\n\t\t┃                                          ┃");
		printf("\n\t\t┃         2.信息单页显示行数       %2u      ┃",flag_page);
		printf("\n\t\t┃                                          ┃");
		printf("\n\t\t┃   数字键选择菜单                 ESC返回 ┃");
		printf("\n\t\t┗━━━━━━━━━━━━━━━━━━━━━┛");
		tmp = getch();
		if(tmp == 27)
			break;
		switch(tmp)
		{
		case '1':flag_color += 1;
			    flag_color %= 2;
			break;
		
		case '2':flag_page -= 1;
				if(flag_page == 4)
					flag_page = 10; 
			break;
		default:break;
		}
	}
	
}
int st_linklist(st_info *buf_head,char *data_name)
{
	st_info *p1 = NULL,*p2 = buf_head,*p3 = buf_head;
	int flag_link = 0,i = 0;

	system("cls");
	p1 = (st_info *)malloc(N);
	while(p2->next)
	{
		p2 = p2->next;
	}
	p2->next = p1;
	printf(menu_print);
	printf("\n Tips:-----输入示例:小豆豆 30130 12 0 123.52 15.9 800.2\n\n");
	fflush(stdin);
	scanf("%14s",p1->name);
	if(strcmp(p1->name,"quit") != 0 || strcmp(p1->name,"QUIT") != 0)
	{
		while(((scanf(ST_SIX_INFO)) != 6) || CHECK_INFO)
		{
			printf("\n Error!-----格式错误!(注意:性别1代表男，0代表女)请重新输入:\n");
			fflush(stdin);
			scanf("%14s",p1->name);
		}
		++i;
		printf("\n OK!-----录入成功!结束录入请输入quit或者QUIT\n");
		while(1)
		{
			p2->next = p1;
			p2 = p1; 
			p1 = (st_info *)malloc(N);
			while(1)
			{
				fflush(stdin);
				scanf("%14s",p1->name);
				if(strcmp(p1->name,"quit") == 0 || strcmp(p1->name,"QUIT") == 0)
				{
					flag_link = 1;
					break;
				}
				if(scanf(ST_SIX_INFO)==6 && (p1->sex == 0 || p1->sex == 1))
				{
					printf("\n OK!-----录入成功！结束录入请输入quit或者QUIT\n");
					++i;
					break;
				}
				printf("\n Error!-----格式错误!(注意:性别1代表男，0代表女)请重新输入:\n");
			}
			if(flag_link == 1)
				break;
		}
	}
	p2->next = NULL;
	free(p1);
	printf("\n Tips:-----录入结束,共录入信息%d条!按任意键继续!",i);
	save_file(buf_head,data_name,N);
	return 0;
}
int baseprint(st_info *buf_head,char *data_name)
{
	unsigned int i = 0,j = 0,check;
	st_info *p1 = buf_head->next;
	system("cls");
	print_tips("  浏览学生体检信息  ");
	printf(menu_print);
	if(p1 == NULL)
	{
		printf("\n\n\n Error!-----没有数据可以显示!请录入!按任意键返回");
		fflush(stdin);
		getch();
		return 0;
	}
	while(p1)
	{
		++j;
		p1 = p1->next;
	}
	p1 = buf_head->next;
	while(p1!= NULL)
	{
		++i;
		printf("\n");
		printf(STINFO);
		p1 = p1->next;
		if(i % flag_page == 0 || i == j)
		{
			print_star();
			if(i == j) 
				printf("\n****************************          输出完毕          ***********************");
			printf("\n 1.按身高升序         2.按体重升序          3.按肺活量升序        4.按学号升序");
			printf("\n 5.按身高降序         6.按体重降序          7.按肺活量降序        8.按学号降序");
			printf("\n **共%u页***************ESC键:返回菜单********字母键:翻页***********第%u页****\r",j/flag_page + 1,(i/flag_page + (( i==j )?1:0)));
			fflush(stdin);
			check = getch();
			if(check <= 56 && check >= 49)
			{
				sort_info(buf_head,data_name,check - 48);
				getch();
				p1 = buf_head->next;
			}
			switch (check)
			{
			case 0:math_info(buf_head);break;
			case 27:return 1;
			default:if(i == j)
						return 1;
					break;
			}
			system("cls");
			print_tips("  浏览学生体检信息  ");
			printf(menu_print);
		}
	}
	getch();
	return 1;
}
void print_star()
{
	printf("\n*******************************************************************************");
}
void print_tips(char *name)
{
	printf("\n\n*************************  >>>%s<<<  *************************",name);
}
int find(st_info *buf_head,const int flag_num)
{
	char check[21];
	st_info *p1 = buf_head,*p2 = NULL,*p3 = NULL;
	find_link *q1,*q2,*find_head=NULL;
	unsigned int flag_find = 0;
	system("cls");
	switch (flag_num)
	{
	case 0:print_tips("  查询学生体检信息  ");break;
	case 2:print_tips("  修改学生体检信息  ");break;
	case 1:print_tips("  删除学生体检信息  ");break;
	}
	if(buf_head->next == NULL)
	{
		printf("\n Error!-----没有数据可供查询!请录入!");
		return 0;
	}
	printf("\n\n\n\n Tips:-----请输入姓名或者学号:");
	fflush(stdin);
	scanf("%20s",check);
	print_star();
	printf(menu_print);
	while (p1->next)
	{
		p2 = p1;
		p1 = p1->next;
		if(strcmp(p1->name,check) == 0 || strcmp(p1->num,check) == 0)
		{
			++flag_find;
			if(flag_find == 1)
			{
				find_head = (find_link *)malloc(M);
				q1 = (find_link *)malloc(M);
				find_head->next = q1;
			}
			q1->buf_find = p2;
			q2 = q1;
			q1 = (find_link *)malloc(M); 
			q2->next = q1;
		}
	}
	if(flag_find != 0)
	{
		free(q1);
		q2->next = NULL;
	}
	printf("\n\n");
	if(flag_find > 10)
	{
		free_find(find_head);
		printf("\n\n Warning!-----系统检测到您的查询结果已超过10个，数据文件可能存在问题!请检查!");
		return 0;
	}
	find_print(find_head,flag_find);
	if(find_head == NULL)
	{
		return 0;
	}
	switch (flag_num)
	{
	case 0:free_find(find_head);break;
	case 1:del_info(find_head,flag_find);free_find(find_head);break;
	case 2:change_info(find_head,flag_find);free_find(find_head);break;
	}
	return 1;
}
int del_info(find_link *find_head,unsigned int flag_find)
{
	unsigned int check,i = 0;
	find_link *q1 = find_head;
	st_info *p1 = NULL,*p2 = NULL;
	if(q1 == NULL)
	{
		return 0;
	}
	else
	{
		fflush(stdin);
		printf("\n Tips:-----按数字键选择您要删除第几条数据!:");
		while(scanf("%u",&check) != 1 || check > flag_find || check == 0)
		{
			fflush(stdin);
			printf("\n Error!-----输入有误，请重新输入!");
		}
		while(q1->next)
		{
			++i;
			q1 = q1->next;
			if(check == i)
			{	
				p1 = q1->buf_find; 
				p2 = (p1->next);
				p1->next = p2->next;	
				free(p2);	
			}
			
		}
		printf("\n OK!-----命令成功执行!第%u条搜索结果已删除!",check);
	return 1;
	}
}
int find_print(find_link *find_head,unsigned int flag_find)
{
	//unsigned int flag_print = 0;
	find_link *q1 = find_head;
	st_info *p1;
	if(find_head ==NULL)
	{
		print_star();
		printf("\n Tips:-----没有找到任何记录,请仔细核对关键词!按任意键返回主菜单!");
		fflush(stdin);
		return 0;
	}
	do
	{
		q1 = q1->next;
		p1 = (q1->buf_find)->next;
		printf(STINFO);
	}while(q1->next);
	print_star();
	printf("\n OK!-----查找完成!共找到%u条记录!",flag_find);
	return 1;
}
int change_info(find_link *find_head,unsigned int flag_find)
{
	find_link *q1 = find_head,*q2 = NULL;
	st_info *p1 = NULL;
	unsigned int check,i = 0;
	if(find_head == NULL)
	{
		return 0;
	}
	printf("\n Tips:-----按数字选择您要修改第几条信息!");
	while(scanf("%u",&check) != 1 || check > flag_find || check == 0)
	{
		fflush(stdin);
		printf("\n Error!-----输入有误，请重新输入!");
	}
	printf("\n Tips:-----您将修改第%u条信息!请输入此项的所有信息:",check);
	while(q1->next)
	{
		++i;
		q1 = q1->next;
		if(check == i)
		{
			p1 = (q1->buf_find)->next;
			fflush(stdin);
			scanf("%s",p1->name);
			while(scanf(ST_SIX_INFO) != 6 || (p1->sex != 0 && p1->sex != 1))
			{
				fflush(stdin);
				printf("\n Error!-----输入有误，请重新输入!");
				scanf("%s",p1->name);
			}
		}
	}
	printf("\n OK!-----数据已更新!");
	return 1;
}
int free_find(find_link *find_head)
{
	find_link *q1 = find_head,*q2 = NULL;
	if(find_head == NULL)
	{
		return 0;
	}
	else
	{
		while(q1->next)
		{
			q2 = q1;
			q1 = q1->next;
			free(q2);
		}
		free(q1);
	}
	printf("\n OK!-----已释放搜索行为所占内存!");
	return 1;
}
int save_file(void *head,char *data_name,size_t n)
{
	st_info *p1 = NULL;
	sort_link *r1 = NULL;
	FILE *fp;
	char check;
	unsigned int size_check;
	printf("\n\n Tips:-----是否更新数据到文件?(Y/N)");
	fflush(stdin);
	check = getch();
	if(check == 'Y'||check == 'y')
	{
		printf("\n");
		if(flag_file == TURE)
		{
			printf("\n");
			system("copy data.csv databk.csv");
			printf("\n OK!-----源文件已备份为databk.csv!");
		}
		if((fp = fopen(data_name,"w")) != NULL)
		{
			if ((size_check = N) == n)
			{
				p1 = ((st_info *)head)->next;
				while(p1)
				{
					fprintf(fp,BUF_PQ);
					p1 = p1->next;
				}
			}
			if ((size_check = T_T) == n)
			{
				r1 = ((sort_link *)head)->next;
				while(r1)
				{
					p1 = r1->sort_point;
					fprintf(fp,BUF_PQ);
					r1 = r1->next;
				}
			}
			
		
			fclose(fp);
			printf("\n OK!-----数据已更新到%s!",data_name);
		}
		else
			printf("\n Waring!-----保存文件出错!");
	}
	else
	{
		flag_save = FALSE;
	}
	printf("\n Tips:-----请按任意键返回!");
	return 0;
}
void system_quit(st_info *buf_head,char *data_name)
{
	char check;
	system("cls");
	printf("\n");
	print_tips("       退出系统     ");
	print_star();
	if(flag_save == TURE)
		printf("\n\n OK!-----可以安全退出!");
	else
	{
		printf("\n\n Warning!-----部分修改并未保存到数据文件!是否继续退出？(确认退出请输入Y)");
		fflush(stdin);
		check = getch();
		if(check != 'Y' || check != 'y')
		{
			save_file(buf_head,data_name,N);
		}
	}
	printf("\n\n OK!-----系统将在三秒后自动退出!感谢您的使用!");
	printf("\n\n Tips:-----您对本程序有任何建议与意见都可发送邮件到364986007@qq.com!");
	print_star();
	printf("\n\n\n\n \t\t\t 学生体检信息管理系统V1.0");
	printf("\n\n \t\t\t       2014.6.7");
	printf("\n\n \t\t\t      作者:任强\n");
	_sleep(3000);
	exit(1);
}
int math_info(st_info *buf_head)
{
	st_info *p1 = NULL,*p2 = NULL;
	long double aver_weight = 0,aver_height = 0,aver_Lungvol = 0;
	long double sum_weight = 0,sum_height = 0,sum_Lungvol = 0;
	unsigned int i = 0,sex_num = 0;
	system("cls");
	print_tips("     数据分析     ");
	if(buf_head->next == NULL)
	{
		printf("\n\n Error!-----没有数据可供处理!请录入!");
		getch();
		return 0;
	}
	p1 = buf_head->next;
	while (p1)
	{
		++i;
		if(p1->sex == 1)
			sex_num += 1;
		sum_weight+=p1->weight;
		sum_height+=p1->height;
		sum_Lungvol+=p1->Lung_vol;
		p1 = p1->next;
	}
	aver_weight = sum_weight/i;
	aver_height = sum_height/i;
	aver_Lungvol = sum_Lungvol/i;
	printf("\n\n\n\n 【人数】     男:%u人      女:%u人      总人数:%10u人",sex_num,i-sex_num,i);
	printf("\n\n\n 【平均值】");
	printf("\n\n\t\t -->身高:     %.2Lfcm",aver_height);
	printf("\n\n\t\t -->体重:     %.2Lfkg",aver_weight);
	printf("\n\n\t\t -->肺活量:   %.2Lfml",aver_Lungvol);
	printf("\n\n Tips:-----按任意键返回!");
	getch();
	return 1;
}
int sort_info(st_info *buf_head,char *data_name,const int check)	//排序 
{
	sort_link *sort_head = NULL,*r1 = NULL,*r2 = NULL,*r3 = NULL,*r4 = NULL;
	st_info *p1 = buf_head->next,*p2 = NULL;
	unsigned int i = 0,j = 0,flag_end = FALSE;
	int cmp = FALSE;
	sort_head = (sort_link *)malloc(M);
	r1 = (sort_link *)malloc(M);
	sort_head->next = r1;
	r1->next = NULL;
	r1->sort_point = p1;
	while (1)
	{
		p1 = p1->next;
		if(p1 == NULL)
			break;
		r1 = (sort_link *)malloc(N);
		r1->next = NULL;
		r1->sort_point = p1;
		r2 = sort_head;
		flag_end = FALSE;
		do{
			r3 = r2;
			r2 = r2->next;
			if(r2 == NULL)
			{
				r3->next = r1;
				break;
			}
			switch (check)
			{
			case 1:cmp = ((r1->sort_point)->height <= (r2->sort_point)->height);break;
			case 2:cmp = ((r1->sort_point)->weight <= (r2->sort_point)->weight);break;
			case 3:cmp = ((r1->sort_point)->Lung_vol <= (r2->sort_point)->Lung_vol);break;
			case 4:cmp = (strcmp((r1->sort_point)->num,(r2->sort_point)->num) <= 0);break;
			case 5:cmp = ((r1->sort_point)->height >= (r2->sort_point)->height);break;
			case 6:cmp = ((r1->sort_point)->weight >= (r2->sort_point)->weight);break;
			case 7:cmp = ((r1->sort_point)->Lung_vol >= (r2->sort_point)->Lung_vol);break;
			case 8:cmp = (strcmp((r1->sort_point)->num,(r2->sort_point)->num) >= 0);break;
			default:break;
			}
			if(cmp)
			{
				r3->next = r1;
				r1->next = r2;
				break;
			}
		}while(1);	
	}
	sort_print(sort_head,data_name);
	return 1;
}
int sort_print(sort_link *sort_head,char *data_name)
{
	sort_link *r1 = sort_head,*r2 = NULL;
	st_info *p1 = NULL;
	unsigned int i = 0,j = 0;
	char check;
	system("cls");
	print_tips("  学生体检信息排序 ");
	printf(menu_print);
	while(r1)
	{
		++j;
		r1 = r1->next;
	}
	for (r1 = sort_head->next;r1;r1 = r1->next)
	{
		++i;
		p1 = r1->sort_point;
		printf("\n");
		printf(STINFO);
		if(i % flag_page == 0)
		{
			print_star();
			printf(" Tips:-----数据过多，当前页面可能无法完全显示，请按任意键翻页!");
			printf(" \n  共%u页          按S键:更新排序到文件        按ESC键:返回    第%7u   页",j/flag_page + 1,i/flag_page);
			printf("\r");
			if((check = getch()) == 27)
			{
				sort_free(sort_head);
				return 0;
			}
			if (check == 's' || check == 'S')
			{
				system("cls");
				save_file(sort_head,data_name,T_T);
				getch();
			}
			system("cls");
			print_tips("  学生体检信息排序 ");
			printf(menu_print);	
		}
	}
	printf("\n**************************          输出完毕            ***********************");
	sort_free(sort_head);
	return 1;
}
int sort_free(sort_link *sort_head)
{
	sort_link *r1 = sort_head,*r2 = NULL;
	while(r1->next)
	{
		r2 = r1;
		r1 = r1->next;
		free(r2);
	}
	return 1;
}
