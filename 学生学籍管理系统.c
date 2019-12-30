#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#define N 101    //最大学生数+1
#define M 6      //课程个数+1
#define maxn 21  //char数组最大长度

struct stuInfo    //学生信息
{
    char id[maxn];   //学号
    char name[maxn]; //姓名
    char sex[maxn];  //性别
    char dorm[maxn]; //宿舍号
    char tel[maxn];  //电话
}stu[N];

struct courseInfo   //课程信息
{
    char id[maxn];    //课程编号
    char name[maxn];  //课程名称
    int credit;       //学分
    int triGrade;     //平时成绩
    int examGrade;    //卷面成绩
    double totalGrade; //综合成绩(平时成绩+卷面成绩)
    int finalCredit;  //实际得到的学分(小于60为0，及格时等于credit)
};

struct stuGrade  //学生成绩信息
{
    char stuId[maxn];  //学号
    struct courseInfo course[M];   //五门课程信息
    double score;   //五门课程的总成绩
}grade[N];

void Menu();   //主菜单
void ShowStuInfo();    //打印学生信息
void AddStuInfo();     //新增学生信息
void FindStuInfo();    //查找学生信息
void ChangeStuInfo();  //修改学生信息
void DeleteStuInfo();  //删除学生信息
void ReadStuInfo();    //从students.txt文件读取学生信息
void SaveStuInfo();    //保存学生信息到students.txt文件
void InitStuInfo();    //初始化学生信息
void ShowGradeInfo();   //打印所有学生成绩信息
void FindGradeInfo();   //根据学号和姓名查找学生成绩信息
void ReadGradeInfo();   //从grade.txt文件读取学生成绩信息
void SaveGradeInfo();   //保存学生成绩信息到grade.txt文件
void Sort();            //对学生信息进行排序

//全局变量
int stuCnt = 0;   //学生人数

int main()
{
    InitStuInfo();
    while(1)
    {
        Menu();  //显示菜单
        char str[maxn];   //预防暴力输入
        gets(str);
        int num = atoi(str);
        while(num<0 || num >11)
        {
            printf("请输入一个有效选项：\n");
            gets(str);
            num = atoi(str);
        }
        switch(num)
        {
            case 0:
                printf("正在退出...");
                Sleep(2);
                return 0;
            case 1:
                AddStuInfo();
                break;
            case 2:
                FindStuInfo();
                break;
            case 3:
                ChangeStuInfo();
                break;
            case 4:
                DeleteStuInfo();
                break;
            case 5:
                ShowStuInfo();
                break;
            case 6:
                ReadStuInfo();
                ReadGradeInfo();
                break;
            case 7:
                SaveStuInfo();
                SaveGradeInfo();
                break;
            case 8:
                Sort();
                break;
            case 9:
                ShowGradeInfo();
                break;
            case 10:
                FindGradeInfo();
                break;
            case 11:
                Sort();
                break;
            default:
                break;
        }
        printf("\n");
    }
    return 0;
}

void Menu()   //主菜单
{
    printf("*************************************************\n");
    printf("*\t欢迎使用河北大学学生学籍管理系统V1.0\t*\n");
    printf("*************************************************\n");
    printf("*\t\t1.新增学生信息\t\t\t*\n");
    printf("*\t\t2.查找学生信息\t\t\t*\n");
    printf("*\t\t3.修改学生信息\t\t\t*\n");
    printf("*\t\t4.删除学生信息\t\t\t*\n");
    printf("*\t\t5.打印所有学生信息\t\t*\n");
    printf("*\t\t6.读取学生信息\t\t\t*\n");
    printf("*\t\t7.保存学生信息\t\t\t*\n");
    printf("*\t\t8.排序学生信息\t\t\t*\n");
    printf("*\t\t9.打印所有学生成绩信息\t\t*\n");
    printf("*\t\t10.查找学生成绩信息\t\t*\n");
    printf("*\t\t11.对学生信息进行排序\t\t*\n");
    printf("*\t\t0.退出系统\t\t\t*\n");
    printf("*************************************************\n");
    printf("请选择功能:");
}

void Sort()
{
    char str[maxn];
    int num = 0;
    while(num<1 || num>3)
    {
        printf("请选择排序方式：\n");
        printf("1.根据学生的学号进行升序排列\n");
        printf("2.根据学生姓名的字典序进行升序排列\n");
        printf("3.根据学生的总成绩进行升序排列\n");
        gets(str);
        num = atoi(str);
    }
    switch(num)
    {
        case 1:
            for(int i = 1; i < stuCnt; i++)
            {
                for(int j = i+1; j <= stuCnt; j++)
                {
                    if(stu[i].id < stu[j].id)
                    {
                        struct stuInfo temp1 = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp1;
                        struct stuGrade temp2 = grade[i];
                        grade[i] = grade[j];
                        grade[j] = temp2;
                    }
                }
            }
            break;
        case 2:
            for(int i = 1; i < stuCnt; i++)
            {
                for(int j = i+1; j <= stuCnt; j++)
                {
                    if(stu[i].name < stu[j].name)
                    {
                        struct stuInfo temp1 = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp1;
                        struct stuGrade temp2 = grade[i];
                        grade[i] = grade[j];
                        grade[j] = temp2;
                    }
                }
            }
            break;
        case 3:
            for(int i = 1; i < stuCnt; i++)
            {
                for(int j = i+1; j <= stuCnt; j++)
                {
                    if(grade[i].score < grade[j].score)
                    {
                        struct stuInfo temp1 = stu[i];
                        stu[i] = stu[j];
                        stu[j] = temp1;
                        struct stuGrade temp2 = grade[i];
                        grade[i] = grade[j];
                        grade[j] = temp2;
                    }
                }
            }
            break;
        default: break;
    }
}

void InitStuInfo()    //初始化学生信息
{
    for(int i = 0; i <= N; i++)    //初始化学生信息
    {
        strcpy(stu[i].id,"NULL");
        strcpy(stu[i].name,"NULL");
        strcpy(stu[i].sex,"NULL");
        strcpy(stu[i].dorm,"NULL");
        strcpy(stu[i].tel,"NULL");
        for(int j = 1; j <= M; j++)     //初始化学生课程信息
        {
            strcpy(grade[i].course[j].id,"NULL");
            strcpy(grade[i].course[j].name,"NULL");
            grade[i].course[j].credit = 0;
            grade[i].course[j].triGrade = 0;
            grade[i].course[j].examGrade = 0;
            grade[i].course[j].totalGrade = 0;
            grade[i].course[j].finalCredit = 0;
        }
        grade[i].score = 0;
        strcpy(grade[i].stuId,"NULL");
    }
}

void ShowStuInfo()    //打印学生信息
{
    if(stuCnt == 0)
    {
        printf("系统中暂无学生信息，请录入后再来打印查看");
    }
    else
    {
        printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t电话号码\t*\n");
        printf("*****************************************************************************************\n");
        for(int i = 1; i <= stuCnt; i++)
        {
            printf("*  %s  *\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            printf("*****************************************************************************************\n");
        }
    }
}

void AddStuInfo()    //新增学生信息
{
    printf("正在新增学生信息...\n");
    stuCnt++;
    printf("请输入该学生的学号:\n");
    scanf("%s",stu[stuCnt].id);
    strcpy(grade[stuCnt].stuId,stu[stuCnt].id);
    getchar();
    printf("请输入该学生的姓名:\n");
    scanf("%s",stu[stuCnt].name);
    getchar();
    printf("请输入该学生的性别:\n");
    scanf("%s",stu[stuCnt].sex);
    getchar();
    printf("请输入该学生的宿舍号:\n");
    scanf("%s",stu[stuCnt].dorm);
    getchar();
    printf("请输入该学生的电话号码:\n");
    scanf("%s",stu[stuCnt].tel);
    getchar();
    for(int j = 1; j < M; j++)
    {
        printf("请输入该学生第%d门课程编号:\n",j);
        scanf("%s",grade[stuCnt].course[j].id);
        getchar();
        printf("请输入该学生第%d门课程名称:\n",j);
        scanf("%s",grade[stuCnt].course[j].name);
        getchar();
        printf("请输入该学生第%d门课程对应学分:\n",j);
        scanf("%d",&grade[stuCnt].course[j].credit);
        getchar();
        printf("请输入该学生第%d门课程的平时成绩:\n",j);
        scanf("%d",&grade[stuCnt].course[j].triGrade);
        getchar();
        printf("请输入该学生第%d门课程的卷面成绩:\n",j);
        scanf("%d",&grade[stuCnt].course[j].examGrade);
        getchar();
        grade[stuCnt].course[j].totalGrade = 0.4*grade[stuCnt].course[j].triGrade + 0.6*grade[stuCnt].course[j].examGrade;   //综合总成绩
    }
    for(int j = 1; j < M; j++)   //计算学生总成绩和每门课程的实得学分
    {
        grade[stuCnt].course[j].finalCredit = grade[stuCnt].course[j].totalGrade < 60 ? 0 : grade[stuCnt].course[j].credit; //只有及格得到学分
        grade[stuCnt].score += grade[stuCnt].course[j].totalGrade;
    }
}

void FindStuInfo()    //查找学生信息
{
    char str[maxn];
    int num = 0;
    while(num<=0 || num>=5)
    {
        printf("请选择查询方式：\n");
        printf("1.根据学号查询\n");
        printf("2.根据姓名查询\n");
        printf("3.根据宿舍查询\n");
        printf("4.根据手机号查询\n");
        gets(str);
        num = atoi(str);  //选项
        switch(num)
        {
            case 1:
                printf("请输入需要查询的学号:\n");
                gets(str);
                break;
            case 2:
                printf("请输入需要查询的姓名:\n");
                gets(str);
                break;
            case 3:
                printf("请输入需要查询的宿舍:\n");
                gets(str);
                break;
            case 4:
                printf("请输入需要查询的手机号:\n");
                gets(str);
                break;
            default : break;
        }
    }
    int find = 0;   //0未找到,1找到了
    int fisrt = 1;  //判断是不是第一次,第一次需要展示表头
    for(int i = 1; i <= stuCnt; i++)
    {
        if(num==1 && strcmp(str,stu[i].id)==0)   //根据学号查询
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
        }
        else if(num==2 && strcmp(str,stu[i].name)==0)    //根据姓名查询
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
        }
        else if(num==3 && strcmp(str,stu[i].dorm)==0)    //根据宿舍号查询
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
        }
        else if(num==4 && strcmp(str,stu[i].tel)==0)    //根据手机号
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
        }
        else{ }
    }
    if(!find)   //未找到
    {
        printf("查找失败！系统中未找到该学生信息\n");
    }
}

void ChangeStuInfo()  //修改学生信息
{
    //这里就只以学号查找为例了，其它查询方式相似没必要写，写在FindStuInfo()中了
    char str[maxn];
    printf("请输入想修改信息的学生学号：\n");
    gets(str);
    int find = 0;
    int fisrt = 1;
    for(int i = 1; i <= stuCnt; i++)
    {
        if(strcmp(str,stu[i].id)==0)
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            printf("请输入修改后的学号：\n");
            gets(stu[i].id);
            printf("请输入修改后的姓名：\n");
            gets(stu[i].name);
            printf("请输入修改后的性别：\n");
            gets(stu[i].sex);
            printf("请输入修改后的宿舍号：\n");
            gets(stu[i].dorm);
            printf("请输入修改后的电话号码：\n");
            gets(stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
            printf("学生信息修改成功，请注意及时保存。\n\n");
        }
    }
    if(!find)   //未找到
    {
        printf("无法进行修改！系统中未找到该学生信息\n");
    }
}

void DeleteStuInfo()  //删除学生信息
{
    char str[maxn];
    int num = 0, flag = 1;
    while(flag)
    {
        printf("请选择删除方式：\n");
        printf("1.根据学号删除\n");
        printf("2.根据姓名删除\n");
        printf("3.根据宿舍删除\n");
        printf("4.根据手机号删除\n");
        gets(str);
        num = atoi(str);  //选项
        switch(num)
        {
            case 1:
                printf("请输入需要删除的学号:\n");
                gets(str);
                flag = 0;
                break;
            case 2:
                printf("请输入需要删除的姓名:\n");
                gets(str);
                flag = 0;
                break;
            case 3:
                printf("请输入需要删除的宿舍:\n");
                gets(str);
                flag = 0;
                break;
            case 4:
                printf("请输入需要删除的手机号:\n");
                gets(str);
                flag = 0;
                break;
            default : break;
        }
    }
    //遍历链表查找，找到之后进行信息的显示
    int find = 0;   //0未找到,1找到了
    int fisrt = 1;  //判断是不是第一次,第一次需要展示表头
    for(int i = 1; i <= stuCnt; i++)
    {
        if(num==1 && strcmp(str,stu[i].id)==0)   //根据学号删除
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
            //删除学生信息
            for(int j = i; j < stuCnt; j++)
            {
                strcmp(stu[j].id,stu[j+1].id);
                strcmp(stu[j].name,stu[j+1].name);
                strcmp(stu[j].sex,stu[j+1].sex);
                strcmp(stu[j].dorm,stu[j+1].dorm);
                strcmp(stu[j].tel,stu[j+1].tel);
                for(int k = 1; k <= M; k++)     //删除该学生课程信息
                {
                    strcpy(grade[j].course[k].id,grade[j+1].course[k].id);
                    strcpy(grade[j].course[k].name,grade[j+1].course[k].name);
                    grade[j].course[k].credit = grade[j+1].course[k].credit;
                    grade[j].course[k].triGrade = grade[j+1].course[k].triGrade;
                    grade[j].course[k].examGrade = grade[j+1].course[k].examGrade;
                    grade[j].course[k].totalGrade = grade[j+1].course[k].totalGrade;
                    grade[j].course[k].finalCredit = grade[j+1].course[k].finalCredit;
                }
            }
            grade[stuCnt].score = (i==stuCnt ? 0 : grade[stuCnt+1].score);
            (i==stuCnt ? strcpy(grade[stuCnt].stuId,"NULL") : strcpy(grade[stuCnt].stuId,grade[stuCnt+1].stuId));
            stuCnt--;
            printf("删除成功，请记得保存。\n");
        }
        else if(num==2 && strcmp(str,stu[i].name)==0)    //根据姓名删除
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
            //删除学生信息
            for(int j = i; j < stuCnt; j++)
            {
                strcmp(stu[j].id,stu[j+1].id);
                strcmp(stu[j].name,stu[j+1].name);
                strcmp(stu[j].sex,stu[j+1].sex);
                strcmp(stu[j].dorm,stu[j+1].dorm);
                strcmp(stu[j].tel,stu[j+1].tel);
                for(int k = 1; k <= M; k++)     //删除该学生课程信息
                {
                    strcpy(grade[j].course[k].id,grade[j+1].course[k].id);
                    strcpy(grade[j].course[k].name,grade[j+1].course[k].name);
                    grade[j].course[k].credit = grade[j+1].course[k].credit;
                    grade[j].course[k].triGrade = grade[j+1].course[k].triGrade;
                    grade[j].course[k].examGrade = grade[j+1].course[k].examGrade;
                    grade[j].course[k].totalGrade = grade[j+1].course[k].totalGrade;
                    grade[j].course[k].finalCredit = grade[j+1].course[k].finalCredit;
                }
            }
            grade[stuCnt].score = (i==stuCnt ? 0 : grade[stuCnt+1].score);
            (i==stuCnt ? strcpy(grade[stuCnt].stuId,"NULL") : strcpy(grade[stuCnt].stuId,grade[stuCnt+1].stuId));
            stuCnt--;
            printf("删除成功，请记得保存。\n");
        }
        else if(num==3 && strcmp(str,stu[i].dorm)==0)    //根据宿舍号删除
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
            //删除学生信息
            for(int j = i; j < stuCnt; j++)
            {
                strcmp(stu[j].id,stu[j+1].id);
                strcmp(stu[j].name,stu[j+1].name);
                strcmp(stu[j].sex,stu[j+1].sex);
                strcmp(stu[j].dorm,stu[j+1].dorm);
                strcmp(stu[j].tel,stu[j+1].tel);
                for(int k = 1; k <= M; k++)     //删除该学生课程信息
                {
                    strcpy(grade[j].course[k].id,grade[j+1].course[k].id);
                    strcpy(grade[j].course[k].name,grade[j+1].course[k].name);
                    grade[j].course[k].credit = grade[j+1].course[k].credit;
                    grade[j].course[k].triGrade = grade[j+1].course[k].triGrade;
                    grade[j].course[k].examGrade = grade[j+1].course[k].examGrade;
                    grade[j].course[k].totalGrade = grade[j+1].course[k].totalGrade;
                    grade[j].course[k].finalCredit = grade[j+1].course[k].finalCredit;
                }
            }
            grade[stuCnt].score = i==stuCnt ? 0 : grade[stuCnt+1].score;
            (i==stuCnt ? strcpy(grade[stuCnt].stuId,"NULL") : strcpy(grade[stuCnt].stuId,grade[stuCnt+1].stuId));
            stuCnt--;
            printf("删除成功，请记得保存。\n");
        }
        else if(num==4 && strcmp(str,stu[i].tel)==0)    //根据电话删除
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t学号\t*\t姓名\t*\t性别\t*\t宿舍\t*\t手机号\t*\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\t%s\t*\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
            find = 1;
            printf("*********************************************************************************\n");
            //删除学生信息
            for(int j = i; j < stuCnt; j++)
            {
                strcmp(stu[j].id,stu[j+1].id);
                strcmp(stu[j].name,stu[j+1].name);
                strcmp(stu[j].sex,stu[j+1].sex);
                strcmp(stu[j].dorm,stu[j+1].dorm);
                strcmp(stu[j].tel,stu[j+1].tel);
                for(int k = 1; k <= M; k++)     //删除该学生课程信息
                {
                    strcpy(grade[j].course[k].id,grade[j+1].course[k].id);
                    strcpy(grade[j].course[k].name,grade[j+1].course[k].name);
                    grade[j].course[k].credit = grade[j+1].course[k].credit;
                    grade[j].course[k].triGrade = grade[j+1].course[k].triGrade;
                    grade[j].course[k].examGrade = grade[j+1].course[k].examGrade;
                    grade[j].course[k].totalGrade = grade[j+1].course[k].totalGrade;
                    grade[j].course[k].finalCredit = grade[j+1].course[k].finalCredit;
                }
            }
            grade[stuCnt].score = i==stuCnt ? 0 : grade[stuCnt+1].score;
            (i==stuCnt ? strcpy(grade[stuCnt].stuId,"NULL") : strcpy(grade[stuCnt].stuId,grade[stuCnt+1].stuId));
            stuCnt--;
            printf("删除成功，请记得保存。\n");
        }
        else{ }
    }
    if(!find)   //未找到
    {
        printf("无法删除！系统中未找到该学生信息\n");
    }
}

void ReadStuInfo()    //读取学生信息
{
    FILE *pFile1 = fopen("D:\\students.txt","r+");   //文件指针
    if(pFile1 == NULL)
    {
        printf("打开students.txt失败\n");
        return;
    }
    printf("正在读取学生信息...\n");
    char str[maxn];  //获取字符串
    InitStuInfo();  //学生信息初始化
    int i = 0;
    stuCnt = 1;
    while(fscanf(pFile1,"%s",str) != EOF)   //读到文件尾为止
    {
        switch(i)
        {
            case 0: strcpy(stu[stuCnt].id,str);   break;
            case 1: strcpy(stu[stuCnt].name,str); break;
            case 2: strcpy(stu[stuCnt].sex,str);  break;
            case 3: strcpy(stu[stuCnt].dorm,str); break;
            case 4: strcpy(stu[stuCnt].tel,str);  break;
            default:
                stuCnt++;
                strcpy(stu[stuCnt].id,str);
                i = 0;
                break;
        }
        i++;
    }
    printf("成功读取学生信息\n");
    //ShowStuInfo();   //打印读取到的学生信息
}

void SaveStuInfo()   //保存学生信息
{
    FILE *pFile1 = fopen("D:\\students.txt","w+");   //文件指针
    if(pFile1 == NULL)
    {
        printf("文件students.txt打开失败\n");
        return;
    }
    for(int i = 1; i <= stuCnt; i++)
    {
        fprintf(pFile1,"%s\t%s\t%s\t%s\t%s\n",stu[i].id,stu[i].name,stu[i].sex,stu[i].dorm,stu[i].tel);
    }
    fclose(pFile1);  //关闭文件
    printf("学生信息保存成功\n");
}

void ShowGradeInfo()    //打印学生成绩信息
{
    if(stuCnt == 0)
    {
        printf("系统中暂无学生信息，请录入后再来打印查看");
    }
    else
    {
        printf("*\t课程编号\t*\t课程名称\t*\t学分\t*\t平时成绩\t*\t卷面成绩\t*\t综合总成绩\t*\t实际得到的学分\t*\t\n");
        printf("*****************************************************************************************************************************************************************\n");
        for(int i = 1; i <= stuCnt; i++)
        {
            printf("当前学生学号：%s 姓名：%s\n",grade[i].stuId,stu[i].name);
            for(int j = 1; j < M; j++)
            {
                printf("*\t%s\t\t*\t%s\t\t*\t%d\t*\t%d\t\t*\t%d\t\t*\t%f\t*\t%d\t\t*\n",grade[i].course[j].id,grade[i].course[j].name,grade[i].course[j].credit,grade[i].course[j].triGrade,grade[i].course[j].examGrade,grade[i].course[j].totalGrade,grade[i].course[j].finalCredit);
            }
            printf("该学生的总成绩为%.2f\n",grade[i].score);
            printf("*****************************************************************************************************************************************************************\n");
        }
    }
}

void FindGradeInfo()   //根据学号或姓名来查询学生的成绩单
{
    char str[maxn];
    int num = 0;
    while(num<=0 || num>=5)
    {
        printf("请选择查询成绩单的方式：\n");
        printf("1.根据学号查询\n");
        printf("2.根据姓名查询\n");
        gets(str);
        num = atoi(str);  //选项
        switch(num)
        {
            case 1:
                printf("请输入需要查询的学号:\n");
                gets(str);
                break;
            case 2:
                printf("请输入需要查询的姓名:\n");
                gets(str);
                break;
            default : break;
        }
    }
    int find = 0;   //0未找到,1找到了
    int fisrt = 1;  //判断是不是第一次,第一次需要展示表头
    for(int i = 1; i <= stuCnt; i++)
    {
        if(num==1 && strcmp(str,stu[i].id)==0)   //根据学号查询
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t课程编号\t*\t课程名称\t*\t学分\t*\t平时成绩\t*\t卷面成绩\t*\t综合总成绩\t*\t实际得到的学分\t*\t\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("当前学生学号：%s 姓名：%s\n",grade[stuCnt].stuId,stu[stuCnt].name);  //输出查询到的学生信息
            for(int j = 1; j < M; j++)
            {
                printf("*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\t%d\t*\t%.2f\t*\t%d\t*\n",grade[i].course[j].id,grade[i].course[j].name,grade[i].course[j].credit,grade[i].course[j].triGrade,grade[i].course[j].examGrade,grade[i].course[j].totalGrade,grade[i].course[j].finalCredit);
            }
            printf("该学生的总成绩为%.2f。\n",grade[stuCnt].score);
            find = 1;
            printf("*********************************************************************************\n");
        }
        else if(num==2 && strcmp(str,stu[i].name)==0)    //根据姓名查询
        {
            if(fisrt)
            {
                printf("*********************************************************************************\n");
                printf("*\t课程编号\t*\t课程名称\t*\t学分\t*\t平时成绩\t*\t卷面成绩\t*\t综合总成绩\t*\t实际得到的学分\t*\t\n");
                printf("*********************************************************************************\n");
                fisrt = 0;
            }
            printf("当前学生学号：%s 姓名：%s\n",grade[stuCnt].stuId,stu[stuCnt].name);  //输出查询到的学生信息
            for(int j = 1; j < M; j++)
            {
                printf("*\t%s\t*\t%s\t*\t%d\t*\t%d\t*\t%d\t*\t%.2f\t*\t%d\t*\n",grade[i].course[j].id,grade[i].course[j].name,grade[i].course[j].credit,grade[i].course[j].triGrade,grade[i].course[j].examGrade,grade[i].course[j].totalGrade,grade[i].course[j].finalCredit);
            }
            printf("该学生的总成绩为%.2f。\n",grade[stuCnt].score);
            find = 1;
            printf("*********************************************************************************\n");
        }
        else{}
    }
    if(!find)   //未找到
    {
        printf("系统中未找到该学生信息，无法对该学生成绩进行查询！\n");
    }
}

void ReadGradeInfo()   //从grade.txt文件读取学生成绩信息
{
    FILE *pFile2 = fopen("D:\\grade.txt","r+");
    if(pFile2 == NULL)
    {
        printf("文件grade.txt打开失败\n");
        return;
    }
    printf("正在读取学生成绩信息...\n");
    char str[maxn];  //获取字符串
    int cnt = 0;
    while(fscanf(pFile2,"%s",str) != EOF)   //读到文件尾为止
    {
        cnt++;
        strcpy(grade[cnt].stuId,str);
        fscanf(pFile2,"%lf",&grade[cnt].score);
        for(int i = 1; i < M; i++)
        {
            fscanf(pFile2,"%s",grade[cnt].course[i].id);
            fscanf(pFile2,"%s",grade[cnt].course[i].name);
            fscanf(pFile2,"%d",&grade[cnt].course[i].credit);
            fscanf(pFile2,"%d",&grade[cnt].course[i].triGrade);
            fscanf(pFile2,"%d",&grade[cnt].course[i].examGrade);
            fscanf(pFile2,"%lf",&grade[cnt].course[i].totalGrade);
            fscanf(pFile2,"%d",&grade[cnt].course[i].finalCredit);
        }
    }
    //ShowGradeInfo();   //显示所有学生信息
    printf("成功读取学生成绩信息\n");
}

void SaveGradeInfo()  //保存学生信息到grade.txt文件
{
    FILE *pFile2 = fopen("D:\\grade.txt","w+");   //文件指针
    if(pFile2 == NULL)
    {
        printf("文件grade.txt打开失败\n");
        return;
    }
    for(int i = 1; i <= stuCnt; i++)
    {
        fprintf(pFile2,"%s %.2f\n",grade[i].stuId,grade[i].score);
        //begin
        for(int j = 1; j < M; j++)
        {
            fprintf(pFile2,"%s\t",grade[i].course[j].id);
            fprintf(pFile2,"%s\t",grade[i].course[j].name);
            fprintf(pFile2,"%d\t",grade[i].course[j].credit);
            fprintf(pFile2,"%d\t",grade[i].course[j].triGrade);
            fprintf(pFile2,"%d\t",grade[i].course[j].examGrade);
            fprintf(pFile2,"%.2f\t",grade[i].course[j].totalGrade);
            fprintf(pFile2,"%d\n",grade[i].course[j].finalCredit);
       }
    }
    fclose(pFile2);  //关闭文件
    printf("学生成绩信息保存成功\n");
}
