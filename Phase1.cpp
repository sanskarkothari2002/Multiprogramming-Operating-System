#include<iostream>
#include<fstream>
using namespace std;
class OS
{
    char M[100][4],IR[4],R[4],buffer[40];
    int IC,SI;
    bool C;

    public:
	    void INIT(), LOAD(), STARTEXECUTION(), EXECUTEUSERPROGRAM(), MOS(), READ(), WRITE(), TERMINATE();
	    fstream Input, Output;
};

void OS::INIT()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j]='\0';
        }
    }
     IR[4]={'\0'};
     R[4]={'\0'};
     C=false;
}

void OS::LOAD()
{

    int x=0;
    do
    {
        for(int i=0;i<40;i++)
          {  buffer[i]='\0';     }

        Input.getline(buffer,41);

        if(buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            INIT();
        }
        else if(buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            STARTEXECUTION();
        }
        else if(buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            x=0;
            continue;
        }
        else
        {
            int b = 0;

            for(; x <100;x++)
            {
                for(int j=0;j<4;j++)
                {

                    M[x][j]=buffer[b];
                    b++;
                    cout<<"M["<<x<<"]"<<"["<<j<<"]: "<<M[x][j]<<endl;

                }
                if(b== 40||buffer[b] == ' ' ||buffer[b] == '\n')
                {
                    x++;
                    break;
               }

            }
        }

    }while(!Input.eof());

}

void OS::STARTEXECUTION()
{
	IC = 00;
    EXECUTEUSERPROGRAM();
}

void OS::EXECUTEUSERPROGRAM()
{
    while(true)
    {
        for(int i=0;i<4;i++)
        {
            IR[i] = M[IC][i];
        }
        IC++;

        int n = IR[2]-48;

        n = n*10+(IR[3]-48);

        if(IR[0]=='G' && IR[1]=='D')
        {
            SI = 1;
            MOS();
        }
        else if(IR[0]=='P' && IR[1]=='D')
        {
            SI = 2;
            MOS();
        }
        else if(IR [0]=='H')
        {
            SI = 3;
            MOS();
            break;
        }
        else if(IR[0]=='L' && IR[1]=='R')
        {
            for(int j=0;j<4;j++)
                R[j]=M[n][j];
        }
        else if(IR[0]=='S' && IR[1]=='R')
        {
            for(int j=0;j<4;j++)
                M[n][j]=R[j];

        }
        else if(IR[0]=='C' && IR[1]=='R')
        {
           for(int j=0;j<4;j++){
            if(M[n][j]==R[j]){
                C=true;
            }
            else{
                C=false;
                break;
            }
           }
        }
        else if(IR[0] =='B' && IR[1]=='T' && C==true)
        {
            IC=n;
        }
    }
}


void OS::MOS()
{

	    switch (SI)
	    {
		    case 1:
		           READ();
		           break;
		    case 2:
		            WRITE();
		            break;
		    case 3:
		            TERMINATE();
		            break;
	    }

}

void OS::READ()
{
    for(int i=0;i<40;i++)
           {buffer[i]='\0';}

        Input.getline(buffer,41);

        int b = 0;
        int n = IR[2]-48;
        n = n*10;

        for( int l=0;l<10;l++)
        {
            for(int j=0;j<4;j++)
            {
                M[n][j] = buffer[b];
                b++;
            }
            if(b == 40)
            {
                break;
            }
            n++;
        }

         SI = 0;
	}


void OS::WRITE()
  {
    for(int i=0;i<40;i++)
    {buffer[i]='\0';}


        int b = 0;
        int n = IR[2]-48;
        n = n*10;


        for( int l=0;l<10;l++)
        {
            for(int j=0;j<4;j++)
            {
                buffer[b]=M[n][j];
                Output<<buffer[b];

                b++;
            }
            if(b == 40)
            {
                break;
            }
            n++;
        }

        Output<<"\n";
     SI = 0;
 }


void OS::TERMINATE()
{
    Output<<"\n";
    Output<<"\n";
    SI = 0;
}

int main()
{
    OS os;
    os.Input.open("input.txt", ios::in);
    os.Output.open("output.txt", ios::out);
    os.LOAD();
    return 0;
}
