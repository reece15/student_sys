/*
 * ѧ�������Ϣ����ϵͳ
 * 
 * Ĭ���û���:admin      ����:admin 
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
#define menu_print "\n%-14s %-10s %-10s %-10s %-10s %-10s %-10s","����","ѧ��","����","�Ա�","���(cm)","����(kg)","�λ���(ml)"
#define STINFO  "%-14s %-10s %-10d %-10s %-10.2lf %-10.2lf %-10.2lf",p1->name,p1->num,p1->old,p1->sex == 1?"��":"Ů",p1->height,p1->weight,p1->Lung_vol
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
}st_info;		//ѧ�������Ϣ���ݽṹ

typedef struct find_link
{
	st_info *buf_find;
	struct find_link *next;
}find_link;		//�洢���ҵ��Ľ���Ľ��ָ��

typedef struct sort_link
{
	st_info *sort_point;
	struct sort_link *next;
}sort_link;			//��������Ľ��ָ������

unsigned int flag_page = 10;	//��ҳ��ʾ����
unsigned int flag_login = FALSE;	//��½��־  0����  1����Ա
unsigned int flag_color = TURE;	//��ɫ����  
unsigned int flag_file = TURE;		//�ļ����سɹ���־
unsigned int flag_save = TURE;		//�������Ѵ��־

void system_init(st_info *buf_head,char *data_name);	//ϵͳ��ʼ��
unsigned int login(char *local_name,char *local_password);			//��½ϵͳ
void main_menu(char *local_name,char *local_password,char *data_name,st_info *buf_head);				//���˵�
void system_help();					//ϵͳ������˵��
void system_set(char *data_name);	//ϵͳ����
int baseprint(st_info *buf_head,char *data_name);		//�������
int st_linklist(st_info *buf_head,char *data_name);			//�����û�¼������
int find(st_info *buf_head,const int flag_num);	//������Ϣ�����ɲ�ѯ�������
void print_star();		//��ӡ�ָ���
void print_tips(char *name);	//��ӡ����
int del_info(find_link *find_head,unsigned int flag_find);	//ɾ������
int find_print(find_link *find_head,unsigned int flag_find);	//��ӡ�ҵ��Ľ��
int change_info(find_link *find_head,unsigned int flag_find);	//�޸�ѧ����Ϣ
int free_find(find_link *find_head);	//�ͷŲ�ѯ�������
void myflush();
int save_file(void *head,char *data_name,size_t n);	//�����ļ�
void system_quit(st_info *buf_head,char *data_name);	//�˳�ϵͳ
int math_info(st_info *buf_head);	//���ݴ���
int sort_info(st_info *buf_head,char *data_name,const int check);	//����
int sort_print(sort_link *sort_head,char *data_name);		//������������
int sort_free(sort_link *sort_head);		//�ͷ���������

int main(void)
{
	char *local_name = {"admin"};		
	char *local_password = {"admin"};		//����Ա�˻� ����
	char data_name[16]={"data.csv"};			//Ĭ�������ļ�
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
		print_tips("ѧ�������Ϣ����ϵͳ");
		if(flag_login == 1)
			printf("\n\n\n\nDear admin, Welcome! \n\n\n\n");
		else
			printf("\n\nDear anonymous,Welcome! \n\nTips:Please Login In.\n\n\n\n");
		printf("\n\t\t   ����������������������������������������");
		printf("\n\t\t   ��                                    ��");
		printf("\n\t\t   ��  1.ϵͳ����         2.ϵͳ����     ��");
		printf("\n\t\t   ��                                    ��");
		if(flag_login == 1)
		{
			printf("\n\t\t   ��  3.�����Ϣ         4.������Ϣ     ��");
			printf("\n\t\t   ��                                    ��");
			printf("\n\t\t   ��  5.ͳ�Ʒ���         6.¼������     ��");
			printf("\n\t\t   ��                                    ��");
			printf("\n\t\t   ��  7.����ɾ��         8.�����޸�     ��");
			printf("\n\t\t   ��                                    ��");
		}
		printf("\n\t\t   ��                                    ��");
		if(flag_login == FALSE)
			printf("\n\t\t   ��  3.��½ϵͳ                        ��");
		printf("\n\t\t   ��                                    ��");
		printf("\n\t\t   ��*����Ӧ���ֽ����Ӳ˵�  ESC:�˳�ϵͳ ��");
		printf("\n\t\t   ����������������������������������������\n");
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
				baseprint(buf_head,data_name);	//���������Ϣ	
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
			break; 	//ֻ���ң����޸Ļ���ɾ��
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
			 }								//���Һ��ɾ������
			break;
	case '8':if(flag_login == TURE)
			 {
				 if(find(buf_head,2) == 1)			//���Һ���޸�����
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
	printf("\n\n****************************��ӭʹ��ѧ�������Ϣ����ϵͳ***********************");
	printf("\n\n\n >>>-----ϵͳ���ڳ�ʼ��...");
	if((p = fopen(data_name,"r")) == NULL)
	{
		printf("\n\n Warning!-----�����ļ�ʧ��!%s�������ڵ�ǰĿ¼!",data_name);
		if((p = fopen("data.csv.bk","r")) == NULL)
		{
			printf("\n\n Warning!-----�����ļ�������!");
			flag_file = FALSE;
			buf_head->next = NULL;
		}
		else
			printf("\n\n OK!-----���Զ�ȡ�����ļ��ɹ�!");
	}
	if(flag_file == TURE)
	{
		printf("\n\n OK!-----��ȡ�ļ��ɹ�!\n\n");
		ch=fgetc(p);
		if(ch==EOF)
		{
			printf("\n Warning!-----�����ļ�����Ϊ��!\n\n");
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
				printf("\r Tips:-----������֤���ݣ������: %4.1lf %%   ��ǰ��Ŀ:   %14s ",(double)ftell(p)/(double)len *100,p1->name);
				if(len < 1024 * 10)
					_sleep(10);
				if(check != 5 || CHECK_INFO)
				{
					printf("\n\n Warning!-----�ļ�������֤ʧ��!���ļ�%s�����ݵ�%u���з��ִ���!����!",data_name,value);
					p1 = buf_head->next;
					while(i < value)
					{
						p2 = p1;
						p1 = p1->next;
						free(p2);
						++i;
					}
					buf_head->next = NULL;
					printf("\n\n OK!-----���ͷ��ڴ�!\n");
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
				printf("\n\n OK!-----�ļ�������֤�ɹ�!�Ѷ�ȡ%u������!",value);
			}
		}
		fclose(p);
	}
	if(buf_head->next == NULL)
		printf("\n\n\n\n Warning!-----��ʼ����δȫ�����!���ֹ��ܿ����޷�ʹ��!�����������ϵͳ!");
	else
		printf("\n\n\n\n OK!-----���г�ʼ�����!�����������ϵͳ!");
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
		printf("\n\n\n\t\t����Ա��½\n\n\t*Tips:�� �� : anonymous");
		printf("\n  �û�����");
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
		printf("\n  ��  �룺");
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
			printf("Warning: Error!-----�û������������\n\t��������%d��***",2 - error);
			++error;
			if(error == 3)
			{
				printf("\n\n Warning!-----���Դ����ѵ�!��ȴ�3�������");
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
	printf("\n\n\n\n\n\t\t\t      *ʹ�ð���&˵��*\n\n\n");
	printf("\n\t����������������������������������������������������������");
	printf("\n\t��                                                      ��");
	printf("\n\t��         1.������ʹ��VC6.0,��WIN7�±�д��             ��");
	printf("\n\t��                                                      ��");
	printf("\n\t��         2.�������ɸ���ϲ����ϵͳ�����н������á�   ��");
	printf("\n\t��                                                      ��");
	printf("\n\t��         3.�ύ�Ĺ����ַ��������ضϡ�                 ��");
	printf("\n\t��                                                      ��");
	printf("\n\t��         4.��Ҫ�����������¼��                       ��");
	printf("\n\t��                                                      ��");
	printf("\n\t��         5.���ߣ���ǿ        ʱ�䣺 2014-06-03        ��");
	printf("\n\t��                                                      ��");
	printf("\n\t����������������������������������������������������������");
	printf("\n\n\n\n\n Tips:-----��������������˵���");
	getch();

}
void system_set(char *data_name)
{
	char tmp;
	unsigned int flag_window = 0;
	while(1)
	{
		system("cls");
		print_tips(">>>     ����     <<<");
		printf("\n\n\n\n");
		printf("\n\t\t����������������������������������������������");
		printf("\n\t\t��                                          ��");
		printf("\n\t\t��         1.���˵���ɫ����         %3s     ��",flag_color ==TURE ?"��":"��");
		printf("\n\t\t��                                          ��");
		printf("\n\t\t��         2.��Ϣ��ҳ��ʾ����       %2u      ��",flag_page);
		printf("\n\t\t��                                          ��");
		printf("\n\t\t��   ���ּ�ѡ��˵�                 ESC���� ��");
		printf("\n\t\t����������������������������������������������");
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
	printf("\n Tips:-----����ʾ��:С���� 30130 12 0 123.52 15.9 800.2\n\n");
	fflush(stdin);
	scanf("%14s",p1->name);
	if(strcmp(p1->name,"quit") != 0 || strcmp(p1->name,"QUIT") != 0)
	{
		while(((scanf(ST_SIX_INFO)) != 6) || CHECK_INFO)
		{
			printf("\n Error!-----��ʽ����!(ע��:�Ա�1�����У�0����Ů)����������:\n");
			fflush(stdin);
			scanf("%14s",p1->name);
		}
		++i;
		printf("\n OK!-----¼��ɹ�!����¼��������quit����QUIT\n");
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
					printf("\n OK!-----¼��ɹ�������¼��������quit����QUIT\n");
					++i;
					break;
				}
				printf("\n Error!-----��ʽ����!(ע��:�Ա�1�����У�0����Ů)����������:\n");
			}
			if(flag_link == 1)
				break;
		}
	}
	p2->next = NULL;
	free(p1);
	printf("\n Tips:-----¼�����,��¼����Ϣ%d��!�����������!",i);
	save_file(buf_head,data_name,N);
	return 0;
}
int baseprint(st_info *buf_head,char *data_name)
{
	unsigned int i = 0,j = 0,check;
	st_info *p1 = buf_head->next;
	system("cls");
	print_tips("  ���ѧ�������Ϣ  ");
	printf(menu_print);
	if(p1 == NULL)
	{
		printf("\n\n\n Error!-----û�����ݿ�����ʾ!��¼��!�����������");
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
				printf("\n****************************          ������          ***********************");
			printf("\n 1.���������         2.����������          3.���λ�������        4.��ѧ������");
			printf("\n 5.����߽���         6.�����ؽ���          7.���λ�������        8.��ѧ�Ž���");
			printf("\n **��%uҳ***************ESC��:���ز˵�********��ĸ��:��ҳ***********��%uҳ****\r",j/flag_page + 1,(i/flag_page + (( i==j )?1:0)));
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
			print_tips("  ���ѧ�������Ϣ  ");
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
	case 0:print_tips("  ��ѯѧ�������Ϣ  ");break;
	case 2:print_tips("  �޸�ѧ�������Ϣ  ");break;
	case 1:print_tips("  ɾ��ѧ�������Ϣ  ");break;
	}
	if(buf_head->next == NULL)
	{
		printf("\n Error!-----û�����ݿɹ���ѯ!��¼��!");
		return 0;
	}
	printf("\n\n\n\n Tips:-----��������������ѧ��:");
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
		printf("\n\n Warning!-----ϵͳ��⵽���Ĳ�ѯ����ѳ���10���������ļ����ܴ�������!����!");
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
		printf("\n Tips:-----�����ּ�ѡ����Ҫɾ���ڼ�������!:");
		while(scanf("%u",&check) != 1 || check > flag_find || check == 0)
		{
			fflush(stdin);
			printf("\n Error!-----������������������!");
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
		printf("\n OK!-----����ɹ�ִ��!��%u�����������ɾ��!",check);
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
		printf("\n Tips:-----û���ҵ��κμ�¼,����ϸ�˶Թؼ���!��������������˵�!");
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
	printf("\n OK!-----�������!���ҵ�%u����¼!",flag_find);
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
	printf("\n Tips:-----������ѡ����Ҫ�޸ĵڼ�����Ϣ!");
	while(scanf("%u",&check) != 1 || check > flag_find || check == 0)
	{
		fflush(stdin);
		printf("\n Error!-----������������������!");
	}
	printf("\n Tips:-----�����޸ĵ�%u����Ϣ!����������������Ϣ:",check);
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
				printf("\n Error!-----������������������!");
				scanf("%s",p1->name);
			}
		}
	}
	printf("\n OK!-----�����Ѹ���!");
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
	printf("\n OK!-----���ͷ�������Ϊ��ռ�ڴ�!");
	return 1;
}
int save_file(void *head,char *data_name,size_t n)
{
	st_info *p1 = NULL;
	sort_link *r1 = NULL;
	FILE *fp;
	char check;
	unsigned int size_check;
	printf("\n\n Tips:-----�Ƿ�������ݵ��ļ�?(Y/N)");
	fflush(stdin);
	check = getch();
	if(check == 'Y'||check == 'y')
	{
		printf("\n");
		if(flag_file == TURE)
		{
			printf("\n");
			system("copy data.csv databk.csv");
			printf("\n OK!-----Դ�ļ��ѱ���Ϊdatabk.csv!");
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
			printf("\n OK!-----�����Ѹ��µ�%s!",data_name);
		}
		else
			printf("\n Waring!-----�����ļ�����!");
	}
	else
	{
		flag_save = FALSE;
	}
	printf("\n Tips:-----�밴���������!");
	return 0;
}
void system_quit(st_info *buf_head,char *data_name)
{
	char check;
	system("cls");
	printf("\n");
	print_tips("       �˳�ϵͳ     ");
	print_star();
	if(flag_save == TURE)
		printf("\n\n OK!-----���԰�ȫ�˳�!");
	else
	{
		printf("\n\n Warning!-----�����޸Ĳ�δ���浽�����ļ�!�Ƿ�����˳���(ȷ���˳�������Y)");
		fflush(stdin);
		check = getch();
		if(check != 'Y' || check != 'y')
		{
			save_file(buf_head,data_name,N);
		}
	}
	printf("\n\n OK!-----ϵͳ����������Զ��˳�!��л����ʹ��!");
	printf("\n\n Tips:-----���Ա��������κν�����������ɷ����ʼ���364986007@qq.com!");
	print_star();
	printf("\n\n\n\n \t\t\t ѧ�������Ϣ����ϵͳV1.0");
	printf("\n\n \t\t\t       2014.6.7");
	printf("\n\n \t\t\t      ����:��ǿ\n");
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
	print_tips("     ���ݷ���     ");
	if(buf_head->next == NULL)
	{
		printf("\n\n Error!-----û�����ݿɹ�����!��¼��!");
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
	printf("\n\n\n\n ��������     ��:%u��      Ů:%u��      ������:%10u��",sex_num,i-sex_num,i);
	printf("\n\n\n ��ƽ��ֵ��");
	printf("\n\n\t\t -->���:     %.2Lfcm",aver_height);
	printf("\n\n\t\t -->����:     %.2Lfkg",aver_weight);
	printf("\n\n\t\t -->�λ���:   %.2Lfml",aver_Lungvol);
	printf("\n\n Tips:-----�����������!");
	getch();
	return 1;
}
int sort_info(st_info *buf_head,char *data_name,const int check)	//���� 
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
	print_tips("  ѧ�������Ϣ���� ");
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
			printf(" Tips:-----���ݹ��࣬��ǰҳ������޷���ȫ��ʾ���밴�������ҳ!");
			printf(" \n  ��%uҳ          ��S��:���������ļ�        ��ESC��:����    ��%7u   ҳ",j/flag_page + 1,i/flag_page);
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
			print_tips("  ѧ�������Ϣ���� ");
			printf(menu_print);	
		}
	}
	printf("\n**************************          ������            ***********************");
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
