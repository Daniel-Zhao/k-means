#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct
{
    double first;//06年世界杯
    double second;//10年世界杯
    double third;//07年亚洲杯
    char country[15];
    char type;
} data;
data data0[15];//保留元数据
data data1[15];

void datashuru()
{
    int i = 0;
    printf("输入数据:\n");
    for(i = 0; i < 15; i++)
    {
        scanf("%lf %lf %lf %s",&data0[i].first,&data0[i].second,
              &data0[i].third,data0[i].country);
        fflush(stdin);
    }
}
void dataggh()
{
    int i = 0;
    double max[3];
    double min[3];
    max[0] = 0; //06年找最大
    max[1] = 0; //10年找最大
    max[2] = 0; //07年找最大
    min[0] = 60;//06年找最小
    min[1] = 60;//10年找最小
    min[2] = 60;//07年找最小
    for(i = 0; i < 15; i++)
    {
        if(max[0] < data0[i].first)
        {
            max[0] = data0[i].first;
        }
        if(max[1] < data0[i].second)
        {

            max[1] = data0[i].second;
        }
        if(max[2] < data0[i].third)
        {
            max[2] = data0[i].third;
        }
        if(min[0] > data0[i].first)
        {
            min[0] = data0[i].first;
        }
        if(min[1] > data0[i].second)
        {
            min[1] = data0[i].second;
        }
        if(min[2] > data0[i].third)
        {
            min[2] = data0[i].third;
        }
    }
    for(i = 0; i < 3; i++)
    {
        printf("max = %lf min = %lf\n",max[i],min[i]);
    }
    /*for(i = 0; i < 15; i++)
    {
        printf("%lf %lf %lf %s\n",data0[i].first,
               data0[i].second, data0[i].third,data0[i].country);
    }*/
    printf("规格化数据为：\n");
    for(i = 0; i < 15; i++)
    {
        data0[i].first = (data0[i].first - min[0]) / (max[0] - min[0]);
        data0[i].second = (data0[i].second - min[1]) / (max[1] - min[1]);
        data0[i].third = (data0[i].third - min[2]) / (max[2] - min[2]);
        printf("data0：%s %lf %lf %lf\n", data0[i].country,
               data0[i].first, data0[i].second, data0[i].third);
        data1[i].first = data0[i].first;
        data1[i].second = data0[i].second;
        data1[i].third = data0[i].third;
        //data1[i].country = data0[i].country;
        strcpy(data1[i].country, data0[i].country);
        printf("data1：%s %lf %lf %lf\n", data1[i].country,
               data1[i].first, data1[i].second, data1[i].third);
    }
    printf("\n");
}
//初始化三簇
void cuchoose()
{
    data cua, cub, cuc;
    cua.first = data0[1].first;//日本
    cua.second = data0[1].second;
    cua.third = data0[1].third;
    cua.type = 'A';
    cub.first = data0[12].first;//巴林
    cub.second = data0[12].second;
    cub.third = data0[12].third;
    cub.type = 'B';
    cuc.first = data0[9].first;//泰国
    cuc.second = data0[9].second;
    cuc.third = data0[9].third;
    cuc.type = 'C';
    printf("簇A:%lf %lf %lf\n",cua.first, cua.second, cua.third);
    printf("簇B:%lf %lf %lf\n",cub.first, cub.second, cub.third);
    printf("簇C:%lf %lf %lf\n\n",cuc.first, cuc.second, cuc.third);
}

void kmeans()
{
    int index[15] = {-1}, index2[15] = {-1};
    int mark = 0;
    int i;
    for(i = 0; i < 15; i++)
    {
        data0[i].first = sqrt(pow((data0[i].first-data0[1].first),2)+
                              pow((data0[i].second-data0[1].second),2)+
                              pow((data0[i].third-data0[1].third),2));
        data0[i].second = sqrt(pow((data0[i].first-data0[12].first),2)+
                               pow((data0[i].second-data0[12].second),2)+
                               pow((data0[i].third-data0[12].third),2));
        data0[i].third = sqrt(pow((data0[i].first-data0[9].first),2)+
                              pow((data0[i].second-data0[9].second),2)+
                              pow((data0[i].third-data0[9].third),2));
        printf("%lf %lf %lf\n", data0[i].first,
               data0[i].second, data0[i].third);
    }
    printf("\n");
    while(!mark)//用mark标记，index和index2数组比较，如果相同，跳出循环，即聚类结果相同
    {
        int i;
        double datax1=0, datay1=0, dataz1=0;//新中心点A
        double datax2=0, datay2=0, dataz2=0;//新中心点B
        double datax3=0, datay3=0, dataz3=0;//新中心点C
        double x=0, y=0, z=0;
        for(i = 0; i < 15; i++)//分到对应的簇
        {
            if(data0[i].first<data0[i].second &&
               data0[i].first<data0[i].third)//标记A
            {
                data0[i].type = 'A';
                datax1 += data1[i].first;
                datay1 += data1[i].second;
                dataz1 += data1[i].third;
                x++;
                index[i] = 1;
            }
            else if(data0[i].second<data0[i].first &&
                    data0[i].second<data0[i].third)//标记B
            {
                data0[i].type = 'B';
                datax2 += data1[i].first;
                datay2 += data1[i].second;
                dataz2 += data1[i].third;
                y++;
                index[i] = 2;
            }
            else if(data0[i].third<data0[i].first &&
                    data0[i].third<data0[i].second)//标记C
            {
                data0[i].type = 'C';
                datax3 += data1[i].first;
                datay3 += data1[i].second;
                dataz3 += data1[i].third;
                z++;
                index[i] = 3;
            }
        }
        datax1 /= x;
        datay1 /= x;
        dataz1 /= x;
        datax2 /= y;
        datay2 /= y;
        dataz2 /= y;
        datax3 /= z;
        datay3 /= z;
        dataz3 /= z;
        printf("新的中心点:\n");
        printf("%lf %lf %lf\n",datax1,datay1,dataz1);
        printf("%lf %lf %lf\n",datax2,datay2,dataz2);
        printf("%lf %lf %lf\n",datax3,datay3,dataz3);
        printf("\nA簇国家有\n");
        for(i = 0; i < 15; i++)//输出A簇的国家
        {
            if(data0[i].type == 'A')
            {
                printf("%s ", data0[i].country);
            }
        }
        printf("\n");
        printf("\nB簇国家有\n");
        for(i = 0; i < 15; i++)//输出B簇的国家
        {
            if(data0[i].type == 'B')
            {
                printf("%s ", data0[i].country);
            }
        }
        printf("\n");
        printf("\nC簇国家有\n");
        for(i = 0; i < 15; i++)//输出C簇的国家
        {
            if(data0[i].type == 'C')
            {
                printf("%s ", data0[i].country);
            }
        }
        printf("\n\n");//只是为了好看点点
        for(i = 0; i < 15; i++)//如果index和index2不相同，
                               //则i到不了15，mark!=1
        {
            if(index[i] != index2[i])
            {
                break;
            }
        }
        if(i == 15)//mark==1即可跳出while循环
        {
            mark=1;
        }
        for(i = 0; i < 15; i++)
        {
            index2[i] = index[i];
        }
        printf("新的相异度:\n");
        for(i = 0; i < 15; i++)//继第一次聚类之后再聚类的相异度
        {
            data0[i].first = sqrt(pow((data1[i].first-datax1),2)+
                                  pow((data1[i].second-datay1),2)+
                                  pow((data1[i].third-dataz1),2));
            data0[i].second = sqrt(pow((data1[i].first-datax2),2)+
                                   pow((data1[i].second-datay2),2)+
                                   pow((data1[i].third-dataz2),2));
            data0[i].third = sqrt(pow((data1[i].first-datax3),2)+
                                  pow((data1[i].second-datay3),2)+
                                  pow((data1[i].third-dataz3),2));
            printf("%lf %lf %lf\n", data0[i].first,
                   data0[i].second, data0[i].third);
        }
        printf("\n");
    }
}
int main()
{
    datashuru();
    dataggh();
    cuchoose();
    printf("选择日本，巴林，泰国作为初始簇中心\n");
    kmeans();
    return 0;
}
