#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct kbQuiz
{
    char question[500];
    char option1[100];
    char option2[100];
    char option3[100];
    char option4[100];
    char correct[100];
};
struct kbQuiz Quizadd(char q[500], char crt[100], char op1[100], char op2[100], char op3[100], char op4[100]);

int lifelines(struct kbQuiz *data, int option, int *fty_fty, int *dbldb, int *errorCount);
void findCorrect(struct kbQuiz *record);
int main()
{
    char 
        ch[100], 
        file_name[]={"kbc.txt"},
        qizdata[6][500];

    struct kbQuiz kbs[7];
    int quizez = 0,option,errorCount=2,result=0,fty_fty = 1, dbldb = 1;
    FILE *fp;


    // data related to quizez save in file and we dynamiclly reading data inside structure

    fp = fopen(file_name,"r");
    if( fp == NULL )
        {
        printf("\nCan not open the file.");
            exit(0);
    }
    while( quizez !=7){
        for (int i = 0; i < 7; i++)
        {
            fgets(qizdata[i], 500, fp);
            qizdata[i][strlen(qizdata[i]) - 1] = '\0';
            if (i==7)
                continue;
            // printf("\n%s",qizdata[i]);
        }
        kbs[quizez] = Quizadd(qizdata[0],qizdata[1],qizdata[2],qizdata[3],qizdata[4],qizdata[5]);
        quizez++;
    }
    fclose(fp);


    // from here we start main code for play quiz game
    printf("Rady to play Quiz\n");
    for (int i = 0; i < 7; i++)
    {
        printf("\nQ%d %s",i+1,kbs[i].question);

        if (fty_fty == 1 && dbldb == 1)
            printf("\n  Two life line :- \n  50-50 = option 5  & double-dib = option 6\n");
        else if (dbldb == 1)
            printf("\n  One remaining life line double-dib = option 6\n");
        else if ( fty_fty == 1)
            printf("\n  One remaining life line 50-50 = option 5\n");
        else 
            printf("\n  No life line\n");
        
        printf("\n  A. %s",kbs[i].option1);
        printf("\tB. %s",kbs[i].option2);
        printf("\n  C. %s",kbs[i].option3);
        printf("\tD. %s\n",kbs[i].option4);
        printf("\n  Your option 1 2 3 4  : ");
        while (1)
        {
            scanf("%d", &option);
            if (option<=0||option>6){

                printf("\n  No option %d\nEnter valid option : ", option);
                errorCount--;
            }

            result = lifelines( &kbs[i] ,option,&fty_fty,&dbldb,&errorCount);
            if (result==6)
            {
                int count = 1;
                while (1)
                {
                    scanf("%d", &option);
                    if (option<=0||option>4 && errorCount > 0){
                        printf("\n  No option %d, Enter valid option : ", option);
                        printf("\n  Dont repeat = %d mistake remaining",--errorCount);
                        printf("\n  Enter again :  ");
                        continue;
                    }
                    else if (option<=0||option>4)
                    {
                        result = 0;
                        break;
                    }
                    
                    result = lifelines( &kbs[i] ,option,&fty_fty,&dbldb,&errorCount);
                    if (result==1 || count == 0)break;
                    count--;
                    printf("\n  Enter second :  ");
                }
            }
            else if (result==5)
            {
                findCorrect(&kbs[i]);
                while (1)
                {   
                    scanf("%d", &option);
                    if (option<=0||option>4 && errorCount > 0){
                        printf("\n  No option %d, Enter valid option : ", option);
                        printf("\n  Dont repeat = %d mistake remaining",--errorCount);
                        printf("\n  Enter again :  ");
                        continue;
                    }
                    if (option <= 0 || option > 4)
                    {
                        result = 0;
                        printf("\n  worked ");
                        break;
                    }
                    result = lifelines( &kbs[i] ,option,&fty_fty,&dbldb,&errorCount);
                    break;
                }
            }

            if (result==1)
            {
                printf("\n\n  Correct Option move to another one \n");
                if (errorCount == 0 && (dbldb == 1 || fty_fty == 1) )
                {
                    ++errorCount;
                }   
                // printf("\n  You%d,%d,%d\n",  errorCount,dbldb ,fty_fty);    
                break;
            }
            else if(result == -1 ){
                printf("\n  Select again :  ");
                // i--;
            }
            else if(result == 0 )
            {
                printf("\n######################################################");
                printf("\n#################   You Lose #########################");
                printf("\n######################################################");
                exit(0);
            } 
        }
    }

    printf("\n######################################################");
    printf("\n##################  Congrats #########################");
    printf("\n######################################################");

    return 0;
}

int lifelines(struct kbQuiz *data ,int option, int *fty_fty,int *dbldb,int *errorCount){
    int ans = -1;
    if (option == 6 && *errorCount != 0)
    {
        if (*dbldb != 1){
            *errorCount -= 1;
            ans= -1;
            printf("\n  You dont have life line double-dib \n  Dont repeat = %d mistake remaining",*errorCount);
        }
        else
        {
            printf("\n  Your option 1 2 3 4 :-");
            printf("\n  Enter two options : ");
            *dbldb-=1;
            ans= 6;
        }
        
    }
    else if (option == 5 && *errorCount != 0)
    {
        if(*fty_fty != 1){
            *errorCount -= 1;
            ans= -1;
            printf("\n  You dont have life line 50-50\n  Dont repeat = %d mistake remaining",*errorCount);
        }
        else
        {
            *fty_fty -= 1;
            ans= 5;
        } 
    }
    else if (option == 1)
    {
        ans = !strcmp(data->option1 , data->correct) ? 1 : 0;
    }
    else if (option == 2)
    {
        ans = !strcmp(data->option2 , data->correct) ? 1 : 0;
    }else if (option == 3)
    {
        ans = !strcmp(data->option3 , data->correct) ? 1 : 0;
    }else if (option == 4)
    {
        ans = !strcmp(data->option4 , data->correct) ? 1 : 0;
    }

    
    if (*errorCount == 0 && ans != 1)    {
        // printf("\n  You Our out%d\n",ans);
        return 0;
    }
    
    // printf("\n%d %s %s\n", ans,data->correct,data->option2);
    return ans;
}

void findCorrect(struct kbQuiz *data){

    if (!strcmp(data->option1 , data->correct) || !strcmp(data->option2 , data->correct))
    {
        printf("\n  A. %s",data->option1);
        printf("\tB. %s",data->option2);
        printf("\n  C. %s","Not this one");
        printf("\tD. %s","Not this one");
    }
    else if (!strcmp(data->option4 , data->correct) || !strcmp(data->option3 , data->correct))
    {
        printf("\n  A. %s","Not this one");
        printf("\tB. %s","Not this one");
        printf("\n  C. %s",data->option3);
        printf("\tD. %s",data->option4);
    }

    printf("\n  Your option 1 2 3 4  : ");
}
struct kbQuiz Quizadd(char q[500], char crt[100], char op1[100],char op2[100],char op3[100],char op4[100])
{

    struct kbQuiz record;
    strcpy(record.question, q);
    strcpy(record.option1, op1);
    strcpy(record.option2, op2);
    strcpy(record.option3, op3);
    strcpy(record.option4, op4);
    strcpy(record.correct , crt);
    return record;
}













    // Quizadd(        
    //     "In 1994, who became the winner of the first-ever Filmfare R D Burman Award for New Music Talent?"
    //     ,"A. R. Rahman"
    //     ,"Udit Narayan"
    //     ,"A. R. Rahman"
    //     ,"Lata Mangeshkar"
    //     ,"Raj Burman"
    // );


