#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<string>
#include<vector>  // dinamik dizi oluşturmak için kullanılır her türden nesne ve sınıfı tutar
 
using namespace std;

char tmp_map[50][64];
char map[50][64] = {

    "+#############################+",  
    "|                             |",  
    "|                             |",  
    "|## ########### ##   #########|",  
    "|   |                         |",  
    "| | |### |  |           |     |",  
    "| |      |  | |###  |   |  |  |",  
    "| | #####|  | |      ## |     |",  
    "| |           |###  |      |  |",  
    "| |##### ###         ##       |",  
    "|          ######  ####### ###|",  
    "|                             |",  
    "|# ### ####      ###   #######|",  
    "|                             |",  
    "|                             |",  
    "|                             |",  
    "|                             |",  
    "+#############################+"};   


 void HaritayiGoster()

 {

    for(int i=0;i<50;i++)

    {

        cout<<map[i]<<endl;

    }


 }

 void gotoxy( short x , short y )

 {

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);  
    COORD position = {x, y};  
  
    SetConsoleCursorPosition(hStdout, position);  

 }

 class entity // varlık sınıfı

 {

    public:

    entity(int x , int y )
    
    {

        this->x = x;
        this->y = y;

    }

    void hareket_x(int p)
    {

        if(map[y][x+p] == ' ')
        

            x += p;

        
    }

    void hareket_y(int p)
    {

        if(map[y+p][x] == ' ')
        

            y += p;

        
    }

    void hareket(int p , int q)

    {

        x += p;  
        y += q;

    }

    int get_x()
    {

        return x;

    }

    int get_y()
    {

        return y;

    }

    void ciz(char p)

    {

        map[x][y] = p;
        gotoxy(x,y);
        cout<<p;

    }

    private:

    int x;
    int y;

    };
    
    struct walk

    {
        short walk_count;
        short x;
        short y;
        short back;

    };

    struct target

    {
     
     short x;
     short y;

    };

    vector<target>walk_queue;  // yürüme işlemini yapıyor queue vector içinde tutuluyor
    vector<walk>BFSArray; // walk türünden elemanları saklamak icin kullanıyoruz breadth first search


   void AddArray( int x , int y , int wc , int back )

   {

    if (tmp_map[y][x] == ' ' || tmp_map[y][x] == '.')

    {

        tmp_map[y][x] = '#';
        walk tmp;
        tmp.x = x;
        tmp.y = y;
        tmp.walk_count = wc;
        tmp.back = back;
        BFSArray.push_back(tmp);
        
    }

   }

  void YoluBul(int sx , int sy , int x , int y)

  {

    memcpy(tmp_map,map,sizeof(map)); // map arrayini tmp_map e kopyalıyoruz
    BFSArray.clear(); // BFSArray i temizliyoruz

    walk tmp;
    tmp.x = sx;
    tmp.y = sy;
    tmp.walk_count = 0;
    tmp.back = -1;
    BFSArray.push_back(tmp);

    int i;
    i=0;

    while (i < BFSArray.size())

    {
        
        if(BFSArray[i].x == x && BFSArray[i].y == y)

        {

            walk_queue.clear();
            target tmp2;
            
            while (BFSArray[i].walk_count != 0)

            {

                tmp2.x = BFSArray[i].x;
                tmp2.y = BFSArray[i].y;
                walk_queue.push_back(tmp2);

                i = BFSArray[i].back;
                
            }

            break;
            
            
        }

        AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);  
        AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);  
        AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);  
        AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);  
  
        i++;

    }

    BFSArray.clear();


  }

   int main()

   {

    bool running = true;
    int x = 15;
    int y = 16;
    int old_x;
    int old_y;

    int ex = 1;
    int ey = 1;

    int points = 0;

    cout<<"Talimatlar Kahramani hareket ettirmek icin ok tuslarini kullanin "<<endl;
    cout<<"Puan Kazanmak Icin Yemleri Toplayin"<<endl;
    cout<<"Oyuna Devam Etmek Istiyorsaniz Yakalanmayin"<<endl;
    cout<<("H -> Hard N -> Normal E -> Easy Input : ");

    char diffi;
    int speedmod= 3;

    cin>>diffi;

    if (diffi == 'N')

    {

        speedmod = 2;
        
    }

    else if (diffi == 'H')

    {

        speedmod = 1;
        
        
    }

    system("cls");
    HaritayiGoster();

    gotoxy(x,y);
    cout<<"H";

    int cerceve;
    cerceve = 0;

    YoluBul( ex , ey , x , y );

    while(running)

    {

        gotoxy(x , y );
        cout<<" ";

        old_x = x;
        old_y = y;

        if (GetAsyncKeyState(VK_UP))

        {

            if (map[y-1][x] == '.')

            {

                y--;
                points++;
                
            }

            else if (map[y - 1][x] == ' ')  
                y--; 
            
        }

        if(GetAsyncKeyState(VK_DOWN))

        {

            if (map[y+1][x] == '.')

            {

                y++;
                points++;
                
            }

            else if (map[y + 1][x] == ' ')  
                y++; 
            
        }

        if(GetAsyncKeyState(VK_LEFT))

        {

            if (map[y][x-1] == '.')

            {

                x--;
                points++;
                
            }

            else if (map[y][x - 1] == ' ')  
                x--; 
            
        }

        if(GetAsyncKeyState(VK_RIGHT))

        {

            if (map[y][x+1] == '.')

            {

                x++;
                points++;
                
            }

            else if (map[y][x + 1] == ' ')  
                x++; 
            
        }

        if(old_x != x || old_y != y)

        {

            YoluBul( ex , ey , x , y );

        }

        gotoxy(x,y);
        cout<<"H";

        map[ey][ex] = '.';
        gotoxy(ex,ey);
        cout<<".";

        if (cerceve % speedmod == 0 && walk_queue.size() != 0)

        {

            ex = walk_queue[walk_queue.size() - 1].x;
            ey = walk_queue[walk_queue.size() - 1].y;
            walk_queue.pop_back();
            
            
        }

        gotoxy(ex,ey);
        cout<<"E";

        if(ex == x && ey == y )

        {

            break;

        }

        
        
        gotoxy(64,50);
        gotoxy(64,1);
        cout << points;  
        Sleep(100);  
        cerceve++;  
    }  
  
    system("cls");  
    system("color 4");
    printf("Kaybettiniz Skorunuz : %i",points);
    cin.get();  
    cin.get();  
    cin.get();  
    cin.get();  
    cin.get();  
    cin.get();  
    cin.get();  
    cin.get();  
  
    return 0;

}  













   
    
    
        
      


