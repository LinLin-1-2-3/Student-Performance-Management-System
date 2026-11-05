#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct student
{
    char id[20];            //学号
    char name[50];          //姓名
    char sex[8];            //性别，用中文男女表示
    char class_name[20];    //班级
    float chinese;          //语文成绩
    float math;             //数学成绩
    float english;          //英语成绩
    float total;            //总成绩
    float average;          //平均成绩
} S;

/* 随机数据池 */
static const char* surnames[] = {
    "王","李","张","刘","陈","杨","黄","赵","吴","周",
    "徐","孙","马","朱","胡","郭","何","高","林","罗",
    "郑","梁","谢","宋","唐","许","韩","冯","邓","曹"
};

static const char* given_names[] = {
    "伟","芳","娜","秀英","敏","静","丽","强","磊","军",
    "洋","勇","艳","杰","娟","涛","明","超","秀兰","霞",
    "平","刚","桂英","玉兰","萍","红","玉华","琳","倩","雪梅",
    "晨阳","子涵","欣怡","浩然","雨轩","梓涵","一诺","思远","佳怡","俊杰"
};

static const char* classes[] = {
    "计科2401","计科2402","软工2401","软工2402",
    "网工2401","网工2402","人工智能2401","大数据2401"
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/* 生成 50.0 ~ 100.0 之间、保留一位小数的成绩 */
static float random_score(void)
{
    return 50.0f + (rand() % 501) / 10.0f;
}

int main(void)
{
    srand((unsigned)time(NULL));

    FILE* fp = fopen("students.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    const int N = 300;
    for (int i = 0; i < N; ++i) {
        S s;
        memset(&s, 0, sizeof(s));

        /* 学号：2024001 ~ 2024300 */
        snprintf(s.id, sizeof(s.id), "2024%03d", i + 1);

        /* 姓名：随机姓氏 + 随机名字 */
        const char* sn = surnames[rand() % ARRAY_SIZE(surnames)];
        const char* gn = given_names[rand() % ARRAY_SIZE(given_names)];
        snprintf(s.name, sizeof(s.name), "%s%s", sn, gn);

        /* 性别 */
        strcpy(s.sex, (rand() % 2 == 0) ? "男" : "女");

        /* 班级 */
        strcpy(s.class_name, classes[rand() % ARRAY_SIZE(classes)]);

        /* 三门成绩 */
        s.chinese = random_score();
        s.math = random_score();
        s.english = random_score();

        /* 总成绩和平均成绩 */
        s.total = s.chinese + s.math + s.english;
        s.average = s.total / 3.0f;

        /* 一行一个学生，字段之间用制表符分隔 */
        fprintf(fp, "%s\t%s\t%s\t%s\t%.1f\t%.1f\t%.1f\t%.1f\t%.2f\n",
            s.id, s.name, s.sex, s.class_name,
            s.chinese, s.math, s.english, s.total, s.average);

        /* 屏幕预览前 5 条 */
        if (i < 5) {
            printf("%s\t%s\t%s\t%s\t%.1f\t%.1f\t%.1f\t%.1f\t%.2f\n",
                s.id, s.name, s.sex, s.class_name,
                s.chinese, s.math, s.english, s.total, s.average);
        }
    }

    fclose(fp);
    printf("\n已生成 %d 个学生数据，保存到 students.txt\n", N);
    return 0;
}