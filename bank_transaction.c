#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct banking
{
  long int account;
  char name[20];
  float balance;
}s;

FILE *fp;
void createaccount();
void display();
void credit();
void debit();
void deletion();

void main()
{
   int choice;
   fp=fopen("bank.dat","wb+");
   while(1)
   {
      printf("\n 1create account");
      printf("\n 2dispaly);
      printf("\n 3credit ammount");
      printf("\n 4debit ammount);
      printf("\n 5deletion");
      printf("\n enter ur choice");
      scanf("%d",&choice);
      switch(choice)
      {
         case 1:
            createaccount();
            break;
         case 2:
            display();
            break;
         case 3:
            credit();
            break;
         case 4:
             debit();
             break;
         case 5:
             deletion();
             break;
         default:
            exit(0);
      }
}


void createaccount()
{
   fseek(fp,0,SEEK_END);
   printf("\n Enter ac no name and deposit");
   scanf("%d%s%f",&s.account,s.name,&s.balance);
   fwrite(&s,sizeof(s),1,fp);
}

void display()
{
   fseek(fp,0,SEEK_SET);
   while(fread(&s,sizeof(s),1,fp)!=NULL)
   {
       printf("\n acc no:%ld",s.account);
       printf("\n name:%s",s.name);
       printf("\n balance:%f",s.balance);
   }
}

void credit()
{
    int amount,f=0;
    long int account_no;
    fseek(fp,0,SEEK_SET);
    printf("\n enter account number");
    scanf("%ld",&account_number);
    while(fread(&s,sizeof(s),1,fp)!=NULL)
    {
       if(account_number==s.account)
       {
           printf("\n enter amount to credit");
           scanf("%d",&amount);
           s.balance+=amount;
           fseek(fp,sizeof(s),SEEK_CUR);
           fwrite(&s,sizeof(s),1,fp);
           f=1;
           break;
       }
    }
    if(f==0)
       printf("\n record not found");
    else 
       printf("\n amount credited");
}

void debit()
{
    int amount,f=0;
    long int account_no;
    fseek(fp,0,SEEK_SET);
    printf("\n enter account number");
    scanf("%ld",&account_number);
    while(fread(&s,sizeof(s),1,fp)!=NULL)
    {
       if(account_number==s.account)
       {
           printf("\n enter amount to credit");
           scanf("%d",&amount);
           s.balance-=amount;
           fseek(fp,sizeof(s),SEEK_CUR);
           fwrite(&s,sizeof(s),1,fp);
           f=1;
           break;
       }
    }
    if(f==0)
       printf("\n record not found");
    else 
       printf("\n amount credited");
}

void deletion()
{
   FILE *fp1;
   long int account_number,f=0;
   fp1=fopen("duplicate.dat","wb");
   fseek(fp,0,SEEK_SET);
   printf("\n enter account_number");
   scanf("%ld",&account_number);
   while(fread(&s,sizeof(s),1,fp)!=NULL)
   {
      if(s.account!=account_number)
          fwrite(&s,sizeof(s),1,fp1);
      else
          f=1;
   }
   fclose(fp1);
   fclose(fp);
   rename("duplicate.dat","bank.dat");
   if(f==1)
       printf("record deleted");
   else
       printf("record not found");
   fp=fopen("bank.dat","rb+");
}