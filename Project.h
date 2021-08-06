int count=0;
int saved=1;

typedef struct
{
    int day;
    int month;
    int year;
} Date;
typedef struct
{
    char first_name[20];
    char last_name[20];
    char address[100];
    char email[50];
    char phone_num[20];
    Date bdate;
} Contact;

Contact c[100];



void Validatename(char *s)
{
    int i;
    scanf("%s",s);
    for(i=0; i<strlen(s); i++)
    {
        if(isalpha(s[i])==0)
        {
            printf("Invalid entry\nPlease try again: ");
            Validatename(s);
        }
    }


}

void Mailvalidation(char *string)
{
    int i,check=0;
    printf("Enter The email: ");
    scanf("%[^\n]",string);
    getchar();
    if(isalpha(string[0])==0) //starting with special character
    {
        printf("Invalid E-mail please try again\n");
        Mailvalidation(string);
    }
    for(i=0; i<strlen(string); i++) //no spaces
        if(string[i]==' ')
        {
            printf("Invalid E-mail please try again\n");
            Mailvalidation(string);
        }
    for(i=0; i<strlen(string); i++) //only 1 @
        if(string[i]=='@')
            check++;
    if(check!=1)
    {
        printf("Invalid E-mail please try again\n");
        Mailvalidation(string);
    }
    check=0;
    for(i=0; i<strlen(string); i++)
    {
        if(((string[i]>='a' && string[i]<='z') || (string[i]>='A' && string[i]<='Z')) || (string[i] >='0' && string[i]<='9') ) //no 2 consecutive special character
            check=0;
        else
            check++;

        if(check==2)
            break;

    }
    if(check==2)
    {
        printf("Invalid E-mail please try again\n");
        Mailvalidation(string);
    }
    check=0;
    for(i=0; i<strlen(string); i++) // should be at least 1 '.' in the email
    {
        if(string[i]=='.')
        {
            check++;
            break;
        }
    }
    if(check==0)
    {
        printf("Invalid E-mail please try again\n");
        Mailvalidation(string);
    }
    else
    {
        check=1;
        char *token;
        char copy[50];// not to change the main string
        strcpy(copy,string);
        token=strtok(copy,".");
        while(token!=NULL)
        {
            if(strcasecmp(token,"com")==0 || strcasecmp(token,"net")==0 || strcasecmp(token,"org")==0)
                check++;
            token=strtok(NULL,".");

        }
        if(check!=2) //only one of the them
        {
            printf("Invalid E-mail please try again\n");
            Mailvalidation(string);
        }

    }
}
int ValidateDate(int d,int m,int y)
{

    int valid=1;
    if(y>2020||y<0)
        valid=0;
    if(m>12||m<1)
        valid=0;
    if(m==1||m==3||m==5||m==7||m==8||m==10||m==12)
    {
        if(d>31||d<1)
            valid=0;
    }
    if(m==4||m==6||m==9||m==11)
    {
        if(d>30||d<1)
            valid=0;
    }
    if(m==2)
    {
        if((y%4==0&&y%100!=0)||(y%4==0&&y%100==0&&y%400==0))
        {
            if(d>29||d<1)
                valid=0;
        }
        else if(d>28||d<1)
            valid=0;
    }

    return valid;





}
void  PhoneValidation(char*c)
{
    int i;
    char temp;
    printf("Enter Phone Number: ");
    scanf("%s",c);
    if(CheckDigits(c)==0)
    {
        printf("Invalid Number please Try Again \n");
        PhoneValidation(c);
    }
    else
    {
        if(strlen(c)==10 && c[2]=='-')
            return;
        else if(strlen(c)==9)
        {
            for(i=9; i>1; i--)
            {

                c[i+1]=c[i];
                if(i==2)
                    c[2]='-';
            }

        }

        else
        {
            printf("Invalid Number please Try Again \n");
            PhoneValidation(c);
        }
    }
}
void load()
{
    FILE *f=fopen("contacts.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%d-%d-%d\n",&c[count].first_name,&c[count].last_name,&c[count].address,&c[count].email,&c[count].phone_num,&c[count].bdate.day,&c[count].bdate.month,&c[count].bdate.year);
        count++;
    }
    fclose(f);
}
void Add_Contact()
{
    Contact temp_c;
    int d,m,y;
    printf("Enter First Name: ");
    Validatename(temp_c.first_name);
    printf("Enter Last Name: ");
    Validatename(temp_c.last_name);
    getchar();
    printf("Enter The Address: ");
    scanf("%[^\n]%*c",&temp_c.address);
    Mailvalidation(temp_c.email);
    PhoneValidation(temp_c.phone_num);
    printf("Enter Your Birth date in the format dd-mm-yyyy: ");
    scanf("%d-%d-%d",&d,&m,&y);
    do
    {


        if(ValidateDate(d,m,y))
        {
            temp_c.bdate.day=d;
            temp_c.bdate.month=m;
            temp_c.bdate.year=y;
            break;
        }
        else
        {
            printf("Invalid date please enter a correct date:");
            scanf("%d-%d-%d",&d,&m,&y);
        }
    }
    while(1);
    c[count++]=temp_c;
    saved=0;
}
void Search()
{
    int i,flag;
    char string[20];
    char string2[20];
    char string3[50];
    char string4[50];
    int d,m,y;
    int check[4]= {1,1,1,1};
    printf("Enter the fields you know and write skip to skip one field:\n");
    printf("Enter The Last Name: ");
    scanf("%s",string);
    if(strcasecmp(string,"skip")==0)
        check[0]=0;
    printf("Enter the first name: ");
    scanf("%s",string2);
    if(strcasecmp(string2,"skip")==0)
        check[1]=0;
    getchar();
    printf("Enter the address: ");
    scanf("%[^\n]%*c",string3);
    if(strcasecmp(string3,"skip")==0)
        check[2]=0;
    printf("Enter the email: ");
    scanf("%s",string4);
    if(strcasecmp(string4,"skip")==0)
        check[3]=0;



    int sum=0;
    int flag2=0;

    for(i=0; i<4; i++)
    {
        sum+=check[i];

    }
    if(sum==0)
    {
        printf("please enter information about your contact\n");
        Search();
    }

    for(i=0; i<count; i++)
    {
        flag=0;
        if(check[0]!=0)
        {

            if(strcasecmp(string,c[i].last_name)==0)
                flag++;

        }
        if(check[1]!=0)
        {
            if(strcasecmp(string2,c[i].first_name)==0)
                flag++;

        }
        if(check[2]!=0)
        {
            if(strcasecmp(string3,c[i].address)==0)
                flag++;

        }
        if(check[3]!=0)
        {
            if(strcasecmp(string4,c[i].email)==0)
                flag++;

        }
        if(flag==sum)
        {
            Display(i);
            flag2++;
        }
        else
            continue;


    }
    if(flag2==0)
        printf("\ncontact not found\n\n");



}
void Display(int index)
{
    printf("%s %s, %s, %s, %s, %d-%d-%d\n",c[index].first_name,c[index].last_name,c[index].address,c[index].email,c[index].phone_num,c[index].bdate.day,c[index].bdate.month,c[index].bdate.year);
}

void Save()
{
    FILE *f=fopen("contacts.txt","w");
    int index=0;
    for(index=0; index<count; index++)
    {
        fprintf(f,"%s,%s,%s,%s,%s,%d-%d-%d\n",c[index].first_name,c[index].last_name,c[index].address,c[index].email,c[index].phone_num,c[index].bdate.day,c[index].bdate.month,c[index].bdate.year);
    }
    fclose(f);
}
void Delete()
{
    char s1[20],s2[20];
    printf("Enter the First Name of the contact you want to delete: ");
    scanf("%s",s1);
    printf("Enter the Last Name of the contact you want to delete: ");
    scanf("%s",s2);
    int i,j=0;
    for(i=0; i<count; i++)
    {
        if(strcasecmp(s1,c[i].first_name)==0&&strcasecmp(s2,c[i].last_name)==0)
        {

            while(i<count)
            {
                c[i]=c[i+1];
                i++;
            }
            count--;
            j=1;
        }
    }
    if(j==0)
        printf("\nContact not found");
    saved=0;
}
void Modify()
{
    char string[20];
    printf("Enter The Last Name : ");
    scanf("%s",string);
    int flag=0;
    int found[count];
    int i,choice,j=0;
    int d,m,y;
    for(i=0; i<count; i++)
    {


        if(strcasecmp(string,c[i].last_name)==0)
        {
            found[j]=i;
            j++;
            flag=1;

        }
    }
    if(j==1){
            printf("\nThe contact you want to edit is:\n\n");
        Display(found[0]);
        do
            {
                printf("\nEnter the number corresponding to the field you want to modify for this contact:\n\n1-First name\n2-Last name\n3-Address\n4-Email\n5-Phone number\n6-Birthdate\n\nPress 7 to exit\n");

                scanf("%d",&choice);

                switch(choice)
                {
                case 1:
                    Validatename(c[found[0]].first_name);
                    break;
                case 2:

                    Validatename(c[found[0]].last_name);
                    break;
                case 3:
                    getchar();
                    Mailvalidation(c[found[0]].address);
                    break;
                case 4:

                    scanf("%s",&c[found[0]].email);
                    break;
                case 5:

                    PhoneValidation(c[found[0]].phone_num);
                    break;
                case 6:
                    printf("Enter Your Birth date in the format dd-mm-yyyy: ");
                    scanf("%d-%d-%d",&d,&m,&y);
                    do
                    {


                        if(ValidateDate(d,m,y))
                        {
                            c[found[0]].bdate.day=d;
                            c[found[0]].bdate.month=m;
                            c[found[0]].bdate.year=y;

                            break;
                        }
                        else
                        {
                            printf("Invalid date please enter a correct date:");
                            scanf("%d-%d-%d",&d,&m,&y);
                        }
                    }
                    while(1);
                    break;
                case 7:
                    printf("Your contacts has been saved as:\n\n");
                    Display(found[0]);
                    printf("\n");
                    break;

                default:
                    printf("Please enter a valid number: \n");



                }
            }
            while(choice!=7);
            saved=0;


    }
    else{
    if(flag==0)
        printf("\nContact not found\n");
    else
    {
        printf("\n");
        for(i=0; i<j; i++)
        {
            Display(found[i]);
        }
        char s2[20];
        printf("\nEnter first name of the contact you want to modify: ");
        scanf("%s",s2);
        for(i=0; i<j; i++)
        {


            if(strcasecmp(s2,c[found[i]].first_name)==0)
            {


                flag=2;
                break;
            }


        }
        if (flag!=2)
            printf("Entry not found\n");
        else
        {


            do
            {
                printf("\nEnter the number corresponding to the field you want to modify for this contact:\n\n1-First name\n2-Last name\n3-Address\n4-Email\n5-Phone number\n6-Birthdate\n\nPress 7 to exit\n");

                scanf("%d",&choice);

                switch(choice)
                {
                case 1:
                    Validatename(c[found[i]].first_name);
                    break;
                case 2:

                    Validatename(c[found[i]].last_name);
                    break;
                case 3:
                    getchar();
                    Mailvalidation(c[found[i]].address);
                    break;
                case 4:

                    scanf("%s",&c[found[i]].email);
                    break;
                case 5:

                    PhoneValidation(c[found[i]].phone_num);
                    break;
                case 6:
                    printf("Enter Your Birth date in the format dd-mm-yyyy: ");
                    scanf("%d-%d-%d",&d,&m,&y);
                    do
                    {


                        if(ValidateDate(d,m,y))
                        {
                            c[found[i]].bdate.day=d;
                            c[found[i]].bdate.month=m;
                            c[found[i]].bdate.year=y;

                            break;
                        }
                        else
                        {
                            printf("Invalid date please enter a correct date:");
                            scanf("%d-%d-%d",&d,&m,&y);
                        }
                    }
                    while(1);
                    break;
                case 7:
                    printf("Your contacts has been saved as:\n\n");
                    Display(found[i]);
                    printf("\n");
                    break;

                default:
                    printf("Please enter a valid number: \n");



                }
            }
            while(choice!=7);
            saved=0;

        }
    }
    }
}
void swap(int i,int j)
{
    Contact temp;
    temp=c[i];
    c[i]=c[j];
    c[j]=temp;


}
void sortByDate()
{
    int i,j;
    for(j=0; j<count-2; j++)
    {
        for(i=0; i<count-1; i++)
        {
            if(c[i].bdate.year>c[i+1].bdate.year)
                swap(i,i+1);

            if(c[i].bdate.year==c[i+1].bdate.year&&c[i].bdate.month>c[i+1].bdate.month)
                swap(i,i+1);
            if(c[i].bdate.year==c[i+1].bdate.year&&c[i].bdate.month==c[i+1].bdate.month&&c[i].bdate.day>c[i].bdate.day)
                swap(i,i+1);



        }
    }

}
int check(char*c)
{
    int i;
    if(c[2]=='-')
    {
        for(i=0; i<strlen(c); i++)
            if(isdigit(c[i])==0 && i!=2)
                return 0;

    }
    else if(c[2]!='-')
    {
        for(i=0; i<strlen(c); i++)
            if(isdigit(c[i])==0)
                return 0;
    }
    else
        return 1;

}

void sortByLname(count_1)
{

    int i;
    for(i=0; i<count_1; i++)
    {
        if(strcasecmp(c[i].last_name,c[i+1].last_name)==1)
        {
            swap(i,i+1);

        }
        else if(strcasecmp(c[i].last_name,c[i+1].last_name)==0)
        {
            if(strcasecmp(c[i].first_name,c[i+1].first_name)==1)
            {
                swap(i,i+1);


            }
        }
        sortByLname(count_1-1);

    }
}
void sort()
{
    int choice;
    int i;
    printf("Choose the method of sorting:\n1-Sort by last name\n2-Sort by birthdate\n");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        sortByLname(count-1);
        break;
    case 2:
        sortByDate();
        break;
    default:
        printf("please enter a valid number\n");
        sort();
    }
    for(i=0; i<count; i++)

        Display(i);


}

void Exit_program()
{
    char m;
    if(saved==0)
    {
        printf("You haven't saved the changes you have made\nWould you like to save?\n(Type Y for YES and N for NO)\n");
        scanf(" %c",&m);
        if(m=='y'||m=='Y')
            Save();
        else if(m=='n'||m=='N')
            exit(0);
        else
            Exit_program();
    }

}
int CheckDigits(char*c)
{

    int i;
    int flag=1;
    if(c[2]=='-')
    {
        for(i=0; i<strlen(c); i++)
            if(isdigit(c[i])==0 && i!=2)
            {
                flag=0;
                break;
            }

    }
    else if(c[2]!='-')
    {
        for(i=0; i<strlen(c); i++)
            if(isdigit(c[i])==0)
            {
                flag=0;
                break;
            }

    }
    return flag;
}
