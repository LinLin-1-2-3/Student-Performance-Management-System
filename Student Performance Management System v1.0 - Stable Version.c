/*
 *  File name  : Student Performance Management System v1.0 - Stable Version.c
 *  Author     : LinLin (tomcat696@163.com)
 *  Date       : 2026-11-05
 *  Description: 学生成绩管理系统
 *  License    : 仅供学习交流使用，未经允许不得用于商业用途
 */

#include<stdio.h>
#include<string.h>



//系统的功能
//1.查询学生信息
//2.显示所有学生
//3.学生成绩排名
//4.增加学生信息
//5.修改学生信息
//6.删除学生信息
//7.退出系统



//定义学生结构体
typedef struct student
{
	char id[20];			//学号
	char name[50];			//姓名
	char sex[8];			//性别，用中文男女表示
	char class_name[20];	//班级
	float chinese;			//语文成绩
	float math;				//数学成绩
	float english;			//英语成绩
	float total;			//总成绩
	float average;			//平均成绩
}S;



//定义：本地文件的缓存
S PlayerData[1024 * 10];
//缓存行数
int p_count = 0;



//函数声明
void menu();
int code();
void road();
void get_student_info();
void show_all_student();
void get_all_student_ranks();
void add_student();
void update_student_info();
void deletd_student();
void save();



int main()
{

	//密码登录
	{
		int x=code();
		if (x == -1)return 0;
	}

	//将文件读进缓存
	road();

	//{//重新计算总分和平均成绩
	//	for (int i = 0; i < p_count; i++)
	//	{
	//		PlayerData[i].total = PlayerData[i].chinese + PlayerData[i].math + PlayerData[i].english;
	//		PlayerData[i].average = PlayerData[i].total / 3;
	//	}
	//}

	while (1)
	{
		int choice;
		menu();
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:get_student_info();		break;
		case 2:show_all_student();		break;
		case 3:get_all_student_ranks();	break;
		case 4:add_student();			break;
		case 5:update_student_info();	break;
		case 6:deletd_student();		break;
		case 7:printf("已退出。蟹蟹您的使用！\n"); break;
		default:printf("无效的选择，请重新输入\n"); break;
		}

		//将缓存写进文件
		save();
		printf("已保存修改...\n");

		if (choice == 7)break;
	}

	return 0;
}



int code()
{
	printf("\t\t学生成绩管理系统\n");
	char input[100] = { 0 }, password[100] = "12345";
	int i = 0;
	while (1)
	{
		i++;
		printf("请输入登录密码:");
		scanf("%s", input);
		if (strcmp(input, password)==0)
		{
			printf("密码正确\n");
			break;
		}
		else
		{
			if (i == 5) return -1;//连续错五次自动退出
			printf("剩余%d次机会\n", 5 - i);
			printf("密码错误请重新输入\n");
		}
	}
	return 0;
}



void menu()
{
	printf("\n\n\n\n==============学生成绩管理系统==============\n\n");
	printf("1.查询学生信息\t\t");
	printf("2.显示所有学生\n");
	printf("3.学生成绩排名\t\t");
	printf("4.增加学生信息\n");
	printf("5.修改学生信息\t\t");
	printf("6.删除学生信息\n");
	printf("7.退出系统\n");
	printf("\n============================================\n");
	printf("请输入选择：");
}



void road()
{
	int i = 0;
	FILE* file1 = fopen("D:学生成绩管理系统（数据）.txt", "r");//r只读
	if (file1 == NULL) { printf("打开失败\n"); return; }//检查是否打开成功

	//printf("学号      姓名    性别     班级       语文成绩   数学成绩   英语成绩    总成绩    平均成绩\n");
	while (i < 1024 * 10 && fscanf_s(file1, "%s  %s    %s    %s       %f       %f       %f       %f       %f",
		PlayerData[i].id, (unsigned)sizeof(PlayerData[i].id),
		PlayerData[i].name, (unsigned)sizeof(PlayerData[i].name), 
		PlayerData[i].sex, (unsigned)sizeof(PlayerData[i].sex),
		PlayerData[i].class_name, (unsigned)sizeof(PlayerData[i].class_name),
		&PlayerData[i].chinese, &PlayerData[i].math, &PlayerData[i].english,
		&PlayerData[i].total, &PlayerData[i].average) == 9)//循环读取
	{
		//printf("%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
			//PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
			//PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
			//PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);//打印读取结果
		i++;
	}
	p_count = i;//最后一个有效数据在playerdata[p_count-1]
	fclose(file1);
}



void get_student_info()
{
	printf("请输入学生学号：");
	char student_id[20];
	scanf("%s", student_id);
	student_id[19] = 0;//为student_id添加终止符
	while (getchar() != '\n');//清除（本行）无关数据
	int i = 0;
	while (i < p_count)
	{
		if (strcmp(student_id, PlayerData[i].id) == 0)
		{
			printf("学号      姓名    性别     班级       语文成绩   数学成绩   英语成绩    总成绩    平均成绩\n");
			printf("%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
				PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
				PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
				PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);
			break;
		}
		i++;
	}
	if (i == p_count)printf("未找到\n");
}



void show_all_student()
{
	int i = 0;
	printf("\n\n学号      姓名    性别     班级       语文成绩   数学成绩   英语成绩    总成绩    平均成绩\n");
	while (i< p_count)
	{
		printf("%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
			PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
			PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
			PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);
		i++;
	}
}



void get_all_student_ranks()
{

	//先完成，再完美，放弃更高级的写法了。。。

	//输入选择
	printf("请输入要排名的选择：1.语文\t2.数学\t3.英语\t4.总成绩\t5.平均成绩\n");
	char choice2[5];
	scanf("%4s", choice2);//最多接收4个字符
	while (getchar() != '\n');//清除（本行）无关数据

	//1.确认选择	2.冒泡排序
	if (strcmp(choice2, "1") == 0)
	{
		for (int i = 0; i < p_count; i++)
		{
			for (int j = p_count - 1; j >= i + 1; j--)
			{
				if (PlayerData[j - 1].chinese < PlayerData[j].chinese)
				{
					S temp2;
					temp2 = PlayerData[j];
					PlayerData[j] = PlayerData[j - 1];
					PlayerData[j - 1] = temp2;
				}
			}
		}
	}

	else if (strcmp(choice2, "2") == 0)
	{
		for (int i = 0; i < p_count; i++)
		{
			for (int j = p_count - 1; j >= i + 1; j--)
			{
				if (PlayerData[j - 1].math < PlayerData[j].math)
				{
					S temp2;
					temp2 = PlayerData[j];
					PlayerData[j] = PlayerData[j - 1];
					PlayerData[j - 1] = temp2;
				}
			}
		}
	}

	else if (strcmp(choice2, "3") == 0)
	{
		for (int i = 0; i < p_count; i++)
		{
			for (int j = p_count - 1; j >= i + 1; j--)
			{
				if (PlayerData[j - 1].english < PlayerData[j].english)
				{
					S temp2;
					temp2 = PlayerData[j];
					PlayerData[j] = PlayerData[j - 1];
					PlayerData[j - 1] = temp2;
				}
			}
		}
	}

	else if (strcmp(choice2, "4") == 0)
	{
		for (int i = 0; i < p_count; i++)
		{
			for (int j = p_count - 1; j >= i + 1; j--)
			{
				if (PlayerData[j - 1].total < PlayerData[j].total)
				{
					S temp2;
					temp2 = PlayerData[j];
					PlayerData[j] = PlayerData[j - 1];
					PlayerData[j - 1] = temp2;
				}
			}
		}
	}

	else if (strcmp(choice2, "5") == 0)
	{
		for (int i = 0; i < p_count; i++)
		{
			for (int j = p_count - 1; j >= i + 1; j--)
			{
				if (PlayerData[j - 1].average < PlayerData[j].average)
				{
					S temp2;
					temp2 = PlayerData[j];
					PlayerData[j] = PlayerData[j - 1];
					PlayerData[j - 1] = temp2;
				}
			}
		}
	}

	else
	{
		printf("错误的选择\n");
		return;
	}

	//打印排序结果
	printf("学号      姓名    性别     班级       语文成绩   数学成绩   英语成绩    总成绩    平均成绩\n");
	for (int i = 0; i < p_count; i++)
	{
		printf("%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
			PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
			PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
			PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);
	}

	//按学号重新排序（初始化）
	for (int i = 0; i < p_count; i++)
	{
		for (int j = p_count - 1; j >= i + 1; j--)
		{
			if (strcmp(PlayerData[j - 1].id, PlayerData[j].id) > 0)
			{
				S temp2;
				temp2 = PlayerData[j];
				PlayerData[j] = PlayerData[j - 1];
				PlayerData[j - 1] = temp2;
			}
		}
	}
}



void add_student()
{

	//添加测试学生
	/*{
		strcpy(PlayerData[p_count].id, "2026003");
		strcpy(PlayerData[p_count].name, "夏雪");
		strcpy(PlayerData[p_count].sex, "女");
		strcpy(PlayerData[p_count].class_name, "计科2604");
		PlayerData[p_count].chinese = 98;
		PlayerData[p_count].math = 99;
		PlayerData[p_count].english = 89;
		PlayerData[p_count].total = PlayerData[p_count].chinese + PlayerData[p_count].math + PlayerData[p_count].english;
		PlayerData[p_count].average = PlayerData[p_count].total / 3;
		p_count++;
	}*/


	if (p_count >= 1024 * 10)
	{
		printf("储存数量已达上限（10240）\n");
		return;
	}

	printf("请输入学生的学号、姓名、性别、班级、语文成绩、数学成绩、英语成绩\n");
	S student_info;
	
	//学号
	while (1)
	{
		int i = 0;
		printf("请输入学号\n");
		scanf("%s", student_info.id);
		for (i=0;i<p_count;i++)
		{
			if (strcmp(student_info.id, PlayerData[i].id) == 0)
				break;
		}
		if (i < p_count)
			printf("学号重复已存在，请重新输入\n");
		else
			break;
	}

	//姓名、性别、班级
	while (1)
	{
		printf("请输入姓名、性别、班级\n");
		scanf("%s %s %s",
			student_info.name,
			student_info.sex,
			student_info.class_name);
		if (strcmp(student_info.sex, "男") == 0 || strcmp(student_info.sex, "女") == 0)
			break;
		printf("性别错误\n");
	}

	//语文成绩、数学成绩、英语成绩
	while (1)
	{
		printf("请输入语文成绩、数学成绩、英语成绩\n");
		scanf("%f %f %f",
			&student_info.chinese,
			&student_info.math,
			&student_info.english);
		if (student_info.chinese < 0 || student_info.math < 0 || student_info.english < 0 ||
			student_info.chinese>100 || student_info.math>100 || student_info.english>100)
			printf("成绩范围错误\n");
		else
			break;
	}

	//总成绩、平均成绩	
	student_info.total = student_info.chinese + student_info.math + student_info.english;
	student_info.average = student_info.total / 3;

	PlayerData[p_count] = student_info;
	p_count++;

	printf("添加成功...\n");
}



void update_student_info()
{
	int id_location = -1;//记录要修改的学生的位置，默认不存在
	
	{
		//寻找要修改的学生
		printf("请输入要修改学生的学号\n");
		char id[20] = { 0 };
		scanf("%s", id);
		int i = 0;
		while (i < p_count)
		{
			if (strcmp(PlayerData[i].id, id) == 0)
			{

				//查询
				printf("已找到\n");
				printf("学号      姓名    性别     班级       语文成绩   数学成绩   英语成绩    总成绩    平均成绩\n");
				printf("%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
					PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
					PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
					PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);


				//确认修改
				printf("是否确认修改？\n输入数字：1.确认\t2.取消\n");
				char QueRen2[3] = { 0 };
				scanf("%2s", QueRen2);// %2s 表示最多读两个字符
				while (getchar() != '\n');//清除（本行）无关数据
				if (strcmp(QueRen2, "1") == 0)
				{
					id_location = i;
					break;
				}
				else
				{
					printf("已取消修改...\n");
					return;
				}
			}
			i++;
		}
		if (i == p_count) {
			printf("未找到学生...\n");
			return;
		}
	}

	//开始修改
	S student_info;

	//学号
	while (1)
	{
		int i = 0;
		printf("请输入学号\n");
		scanf("%s", student_info.id);
		for (i = 0; i < p_count; i++)
		{
			if (i == id_location)continue;//跳过对比自身
			if (strcmp(student_info.id, PlayerData[i].id) == 0)//对比是否有学号相同
				break;
		}
		if (i < p_count)
			printf("学号重复已存在，请重新输入\n");
		else
			break;
	}

	//姓名、性别、班级
	while (1)
	{
		printf("请输入姓名、性别、班级\n");
		scanf("%s %s %s",
			student_info.name,
			student_info.sex,
			student_info.class_name);
		if (strcmp(student_info.sex, "男") == 0 || strcmp(student_info.sex, "女") == 0)
			break;
		printf("性别错误\n");
	}

	//语文成绩、数学成绩、英语成绩
	while (1)
	{
		printf("请输入语文成绩、数学成绩、英语成绩\n");
		scanf("%f %f %f",
			&student_info.chinese,
			&student_info.math,
			&student_info.english);
		if (student_info.chinese < 0 || student_info.math < 0 || student_info.english < 0 ||
			student_info.chinese>100 || student_info.math>100 || student_info.english>100)
			printf("成绩范围错误\n");
		else
			break;
	}

	//总成绩、平均成绩	
	student_info.total = student_info.chinese + student_info.math + student_info.english;
	student_info.average = student_info.total / 3;

	if(id_location!=-1)PlayerData[id_location] = student_info;

	printf("添加成功...\n");
}



void deletd_student()
{
	//添加测试学生
	/*{
		strcpy(PlayerData[p_count].id, "2026003");
		strcpy(PlayerData[p_count].name, "夏雪");
		strcpy(PlayerData[p_count].sex, "女");
		strcpy(PlayerData[p_count].class_name, "计科2604");
		PlayerData[p_count].chinese = 98;
		PlayerData[p_count].math = 99;
		PlayerData[p_count].english = 89;
		PlayerData[p_count].total = PlayerData[p_count].chinese + PlayerData[p_count].math + PlayerData[p_count].english;
		PlayerData[p_count].average = PlayerData[p_count].total / 3;
		p_count++;
	}*/
	
	printf("请输入要删除的学生的学号\n");
	char id[20] = { 0 };
	scanf("%s", id);
	int i = 0;
	while (i<p_count)
	{
		if (strcmp(PlayerData[i].id,id)==0)
		{

			//查询
			printf("已找到\n\n");
			printf("学号      姓名    性别     班级       语文成绩   数学成绩   英语成绩    总成绩    平均成绩\n");
			printf("%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
				PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
				PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
				PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);


			//确认删除
			printf("\n是否确认删除？\n输入数字：1.确认\t2.取消\n");
			char QueRen[3] = { 0 };
			scanf("%2s", QueRen);// %2s 表示最多读两个字符
			while (getchar() != '\n');//清除（本行）无关数据
			if (strcmp(QueRen,"1") != 0)
			{
				printf("已取消删除...\n");
				return;
			}


			//删除
			PlayerData[i] = PlayerData[p_count - 1];
			//清空多余数据
			{
				strcpy(PlayerData[p_count-1].id, "");
				strcpy(PlayerData[p_count - 1].name, "");
				strcpy(PlayerData[p_count - 1].sex, "");
				strcpy(PlayerData[p_count - 1].class_name, "");
				PlayerData[p_count - 1].chinese = 0;
				PlayerData[p_count - 1].math = 0;
				PlayerData[p_count - 1].english = 0;
				PlayerData[p_count - 1].total = 0;
				PlayerData[p_count - 1].average = 0;
			}
			p_count--;
			printf("删除成功\n");
			break;
		}
		i++;
	}
	if (i == p_count)printf("未找到学生...\n");
}



void save()
{
	FILE* file2 = fopen("D:学生成绩管理系统（数据）.txt", "w");//w只写
	if (file2 == NULL) { printf("打开失败\n"); return; }//检查是否打开成功
	for (int i = 0; i < p_count; i++)
	{
		fprintf(file2, "%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
			PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
			PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
			PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);//循环写入
			//printf("学号      姓名    性别     班级       语文成绩   数学成绩   英语成绩    总成绩    平均成绩\n");
			//printf("%s  %s    %s    %s       %.1f       %.1f       %.1f       %.1f       %.1f\n",
			//PlayerData[i].id, PlayerData[i].name, PlayerData[i].sex,
			//PlayerData[i].class_name, PlayerData[i].chinese, PlayerData[i].math,
			//PlayerData[i].english, PlayerData[i].total, PlayerData[i].average);//打印写入结果
	}
	fclose(file2);
}