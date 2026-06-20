#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Course{
    char name[30];
    float credit;
    float score;
    float gpa;
    char type;
};
typedef struct Course C;

//【0】主菜单
int menu(char *fname);
//【0-1】识别文件中的课程数
int calculating_courses_num(FILE *fp);
//【0-2】换算百分制-绩点
float calculating_level(float score);
//【0-3】用课程名找到课程信息
int find_by_name(C *course,int num,char *cname);
//【1】输入成绩
int input_scorses(char *fname);
//【2】修改成绩
int revise_scores(char *fname);
//【3】计算当前gpa
int calculating_gpa(char *fname);
//【4】计算当前均分
float calculating_scores(char *fname);
//【5】查询课程信息
int find_course_info(char *fname);
//【6】删除课程信息
int delete_course_info(char *fname);
//【7】查看所有课程信息
int view_all_courses(char *fname);
//【8】查看专业课信息
int view_major_courses(char *fname);
//【9】查看成绩排名
int view_score_ranking(char *fname);

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    char fname[50];
    printf("\n输入你要打开的课程信息文件名\n");
    scanf("%s",fname);
    menu(fname);

    
    return 0;
}

//【0】主菜单
int menu(char *fname)
{
    while(1)
    {
    printf("#####---------------欢迎使用GPA/均分计算器！---------------#####");
    printf("\n");
    printf("\n      [1]-输入成绩信息              [2]-修改课程信息          ");
    printf("\n      [3]-查询GPA                   [4]-查询均分              ");
    printf("\n      [5]-查询课程信息              [6]-删除课程信息           ");
    printf("\n      [7]-查看所有课程信息           [8]-查看专业课信息         ");
    printf("\n      [9]-查看成绩排名                                        ");
    printf("\n      [0]-刷新菜单                  [a/A]-退出程序            ");
    printf("\n");
    printf("\n#####----------------------------------------------------#####");

    char option;
        printf("\n请输入你要做的事项[0-A]\n");
        scanf(" %c",&option);

        switch (option)
        {
        case '1':
            input_scorses(fname);
            continue;

        case '2':
            revise_scores(fname);
            continue;

        case '3':
            calculating_gpa(fname);
            continue;

        case '4':
            calculating_scores(fname);
            continue;

        case '5':
            find_course_info(fname);
            continue;

        case '6':
            delete_course_info(fname);
            continue;

        case '7':
            view_all_courses(fname);
            continue;

        case '8':
            view_major_courses(fname);
            continue;

        case '9':
            view_score_ranking(fname);
            continue;

        case '0':
            continue;

        case 'A':
        case 'a':
            exit(0);

        default:
            printf("\n输入无效选项！");
            continue;
        }
    }

    return 0;
}

//【0-1】识别文件中的课程数
int calculating_courses_num(FILE *fp)
{
    if(fp == NULL)
    {
        return 0;
    }
    rewind(fp); //指针返回文件开头
    int num=0;
    C temp;
    while(fread(&temp,sizeof(C),1,fp) == 1)
    {
        num++;
    }
    return num;
}

//【0-1-2】识别文件中专业课数
int calculating_major_courses_num(FILE *fp)
{
    if(fp == NULL)
    {
        return 0;
    }
    rewind(fp); //指针返回文件开头
    int num=0;
    C temp;
    while(fread(&temp,sizeof(C),1,fp) == 1)
    {
        if(temp.type == 'Y' || temp.type == 'y')
        {
            num++;
        }
    }

    return num;
}

//【0-2】换算百分制-绩点
float calculating_level(float score)
{
    float level;

    if(score >= 90)
    {
        level = 4;
    }else if(score >= 87){
        level = 3.7;
    }else if(score >= 84){
        level = 3.3;
    }else if(score >= 80){
        level = 3.0;
    }else if(score >= 77){
        level = 2.7;
    }else if(score >= 74){
        level = 2.3;
    }else if(score >= 70){
        level = 2.0;
    }else if(score >= 67){
        level = 1.7;
    }else if(score >= 64){
        level = 1.3;
    }else if(score >= 60){
        level = 1.0;
    }else{
        level = 0;
    }

    return level;
}

//【0-3】用课程名找到课程信息
int find_by_name(C *course,int num,char *cname)
{
    int i;
    for(i=0;i<num;i++)
    {
        if(strcmp(cname,course[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

//【1】输入成绩
int input_scorses(char *fname)
{
    FILE *fp;
    int num = 0,num_major = 0;
    int i;
    char option;
    C *old_course = NULL,*temp = NULL,*new_course = NULL;

    fp = fopen(fname,"rb");
    num = calculating_courses_num(fp);
    num_major = calculating_major_courses_num(fp);

    if(num == 0)
    {
        printf("\n该文件中无课程信息，是否添加？（Y/N）");
    }else{
        old_course = malloc(sizeof(C)*num);
        if(old_course == NULL)
            {
                printf("\n内存分配失败！");
                fclose(fp);
                return 0;
            }
        rewind(fp);
        fread(old_course,sizeof(C),num,fp); //将信息读入结构体中。
        fclose(fp);

        printf("\n该文件中有%d个课程的信息如下：",num);
        printf("\n课程名---类型___________学分-----成绩(百分制)-----绩点");
        for(i=0;i<num;i++)
        {
            printf("\n%s----%c____________%f------%f------%f",
                 old_course[i].name,old_course[i].type,old_course[i].credit,old_course[i].score,old_course[i].gpa);
        }
        printf("\n\n-----------------------------------------");
        printf("\n\n是否继续添加？：（Y/N）");
    }
    scanf(" %c",&option);

    int add_num=0;
    while(option == 'Y'||option == 'y')
    {
        char cname[30];
        printf("\n请输入课程名：");
        scanf(" %s",cname);

        //检查是否重复
        int repeat_index = 0;
        for(i=0;i<num;i++)
        {
            if(strcmp(cname,old_course[i].name) == 0)
            {
                printf("\n输入与原有课程重复！");
                repeat_index = 1;
                break;
            }
        }
        for(i=0;i<add_num;i++)
        {
            if(strcmp(cname,new_course[i].name) == 0)
            {
                printf("\n输入与本次录入课程重复！");
                repeat_index = 1;
                break;
            }
        }

        //重复后询问
        if(repeat_index)
        {
            printf("\n是否继续添加课程信息？：（Y/N）");
            scanf(" %c",&option);
        }

        //若未重复，扩展
        temp = realloc(new_course,sizeof(C)*(add_num+1));
        if(temp == NULL)
        {
            printf("\n内存分配失败！");
            free(new_course);
            free(old_course);
            fclose(fp);
            return 0;
        }
        new_course = temp;
        strncpy(new_course[add_num].name,cname,30);
        printf("\n请输入%s的学分、成绩（百分制）、类型（是否为专业课）（Y/N）：（空格分隔）",cname);
        scanf(" %f %f %c",&new_course[add_num].credit,&new_course[add_num].score,&new_course[add_num].type);
        new_course[add_num].gpa = calculating_level(new_course[add_num].score);

        add_num++;
        if(new_course[add_num-1].type == 'Y' || new_course[add_num-1].type == 'y')
        {
            num_major++;
        }

        printf("\n是否继续添加？：（Y/N）");
        scanf(" %c",&option);
    }

    //新添课程写入文件
    if(add_num > 0)
    {
        fp = fopen(fname,"ab");
        fseek(fp,0,SEEK_END);
        fwrite(new_course,sizeof(C)*add_num,1,fp);
        printf("\n本次添加过程共添加了%d个课程信息。",add_num);
    }else{
        printf("\n未添加任何课程。");
    }

    int tol,tol_major;
    tol = num + add_num;
    printf("\n文件中总共有%d个课程的信息。",tol);
    printf("\n其中专业课有%d个。",num_major);

    free(new_course);
    free(old_course);
    fclose(fp);

    return 0;
}

//【2】修改成绩
int revise_scores(char *fname)
{
    FILE *fp;
    int i;
    int num,d;
    C *course;
    char cname[30];

    printf("\n输入你想修改的课程名：");
    scanf(" %s",cname);
    
    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }
    num = calculating_courses_num(fp);
    if(num == 0)
    {
        printf("\n无课程信息。");
        fclose(fp);
        return 0;
    }

    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        free(course);
        fclose(fp);
        return 0;
    }

    rewind(fp);
    fread(course,sizeof(C)*num,1,fp);
    fclose(fp);

    d = find_by_name(course,num,cname);
    if(d == -1)
    {
        printf("\n未找到该课程！");
        return 0;
    }
    else
    {
        printf("\n-------原有课程信息：");
        printf("\n课程名：%s", course[d].name);
        printf("\n类型：%c", course[d].type);
        printf("\n学分：%f", course[d].credit);
        printf("\n成绩（百分制）：%f", course[d].score);
        printf("\n绩点：%f", course[d].gpa);
        printf("\n\n输入你要修改的部分：1-课程名，2-类型，3-学分，4-成绩（百分制）");
        int option;
        scanf(" %d",&option);
        switch (option)
        {        
            case 1:
                printf("\n输入修改后的课程名：");
                scanf(" %s",course[d].name);
                break;
            case 2:
                printf("\n输入修改后的类型（Y/N）：");
                scanf(" %c",&course[d].type);
                break;
            case 3:
                printf("\n输入修改后的学分：");
                scanf(" %f",&course[d].credit);
                break;
            case 4:
                printf("\n输入修改后的成绩（百分制）：");
                scanf(" %f",&course[d].score);
                course[d].gpa = calculating_level(course[d].score);
                break;
        }

    }

    fp = fopen(fname,"wb");
    fwrite(course,sizeof(C),num,fp);
    fclose(fp);
    free(course);

    return 0;
}

//【3】计算当前gpa
int calculating_gpa(char *fname)
{
    float gpa;
    int i;
    int num;
    FILE *fp;
    C *course;

    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }
    rewind(fp);
    num = calculating_courses_num(fp);
    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        return 0;
    }
    rewind(fp);
    fread(course,sizeof(C),num,fp);
    fclose(fp);

    float credit_tol = 0,sum_tol = 0;
    for(i=0;i<num;i++)
    {
        sum_tol += course[i].gpa * course[i].credit;
        credit_tol += course[i].credit; 
    }
    gpa = sum_tol / credit_tol;
    printf("\n当前GPA为：%f\n\n",gpa);

    free(course);
    return 0;
}

//【4】计算当前均分
float calculating_scores(char *fname)
{
    float av_score;
    int i;
    int num;
    FILE *fp;
    C *course;

    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }
    num = calculating_courses_num(fp);
    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        return 0;
    }
    rewind(fp);
    fread(course,sizeof(C),num,fp);
    fclose(fp);

    float credit_tol = 0,sum_tol = 0;
    for(i=0;i<num;i++)
    {
        sum_tol += course[i].score * course[i].credit;
        credit_tol += course[i].credit; 
    }
    av_score = sum_tol / credit_tol;
    printf("\n当前均分为：%f\n\n",av_score);

    free(course);
    return av_score;
}

//【5】查询课程信息
int find_course_info(char *fname)
{
    FILE *fp;
    int num;
    C *course;
    char cname[30];

    printf("\n输入你想查询的课程名：");
    scanf(" %s",cname); 

    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }
    rewind(fp);
    num = calculating_courses_num(fp);
    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        return 0;
    }
    rewind(fp);
    fread(course,sizeof(C),num,fp);
    fclose(fp);

    int d = find_by_name(course,num,cname);
    if(d == -1)
    {
        printf("\n未找到该课程！");
        return 0;
    }
    else
    {
        printf("\n-------课程信息：");
        printf("\n课程名：%s", course[d].name);
        printf("\n学分：%f", course[d].credit);
        printf("\n成绩：%f", course[d].score);
        printf("\n绩点：%f", course[d].gpa);
        printf("\n");
    }

    free(course);

    return 0;
}

//【6】删除课程信息
int delete_course_info(char *fname)
{
    FILE *fp;
    int num,i;
    C *course;
    char cname[30];

    printf("\n输入你想删除的课程名：");
    scanf(" %s",cname); 

    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }
    rewind(fp);
    num = calculating_courses_num(fp);
    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        return 0;
    }
    rewind(fp);
    fread(course,sizeof(C),num,fp);
    fclose(fp);

    int d = find_by_name(course,num,cname);
    if(d == -1)
    {
        printf("\n未找到该课程！");
        return 0;
    }
    
    for(i=d;i<num-1;i++)
    {
        course[i] = course[i+1];
    }
    
    fp = fopen(fname,"wb");
    fwrite(course,sizeof(C),num-1,fp);
    fclose(fp);
    
    free(course);

    printf("\n课程%s已删除。",cname);

    return 0;
}

//【7】查看所有课程信息
int view_all_courses(char *fname)
{
    FILE *fp;
    int num,i;
    C *course;

    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }
    rewind(fp);
    num = calculating_courses_num(fp);
    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        return 0;
    }
    rewind(fp);
    fread(course,sizeof(C),num,fp);
    fclose(fp);

    printf("\n课程名________________学分------成绩(百分制)-----绩点");
    for(i=0;i<num;i++)
    {
        printf("\n%s_______________%f------%f------%f",
             course[i].name,course[i].credit,course[i].score,course[i].gpa);
    }
    printf("\n\n");

    free(course);

    return 0;
}

//【8】查看专业课信息
int view_major_courses(char *fname)
{
    FILE *fp;
    int num,i;
    C *course;

    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }

    rewind(fp);
    num = calculating_courses_num(fp);
    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        return 0;
    }

    rewind(fp);
    fread(course,sizeof(C),num,fp);
    fclose(fp);

    printf("\n专业课信息如下\n");
    printf("\n课程名------学分------成绩(百分制)-----绩点");
    for(i=0;i<num;i++)
    {
        if(course[i].type == 'Y' || course[i].type == 'y')
        {
            printf("\n%s------%f------%f------%f",
                 course[i].name,course[i].credit,course[i].score,course[i].gpa);
        }
    }
    printf("\n\n");

    free(course);

    return 0;
}

//【9】查看成绩排名
int view_score_ranking(char *fname)
{
    FILE *fp;
    int i,j,num;
    C *course;

    fp = fopen(fname,"rb");
    if(fp == NULL)
    {
        printf("\n文件打开失败。");
        return 0;
    }
    rewind(fp);
    num = calculating_courses_num(fp);

    course = malloc(sizeof(C)*num);
    if(course == NULL)
    {
        printf("\n内存分配失败。");
        return 0;
    }
    rewind(fp);
    fread(course,sizeof(C),num,fp);
    fclose(fp);

    // 选择排序
    for(i=0; i<num; i++)
    {
        int max_index = i;
        for(j=i;j<num;j++)
        {
            if(course[max_index].score < course[j].score)
            {
                max_index = j;
            }
        }
        C temp = course[max_index];
        course[max_index] = course[i];
        course[i] = temp;
    }

    printf("\n成绩排名如下\n");
    printf("\n排名------课程名------学分------成绩(百分制)-----绩点");
    for(i=0; i<num; i++)
    {
        printf("\n%d------%s------%f------%f------%f", i+1, course[i].name, course[i].credit, course[i].score, course[i].gpa);
    }
    printf("\n\n-----------------------------------------\n\n");

    free(course);

    return 0;
}