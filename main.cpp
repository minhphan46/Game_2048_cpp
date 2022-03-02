#include <bits/stdc++.h>
#include "windows.h"
#include <time.h>
using namespace std;
// ham color
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void dich_chuyen( int a[100], int n, int &diem){
    for ( int i= 0; i < n; i++){
        if(a[i] == 0){
          for( int j = i; j < n; j++){
            if( a[j] != 0 ){
                // đổi chỗ
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
                break;
                }
            }
        }
    }
    for ( int i= 0; i < n-1; i++){
        if(a[i] != 0 && a[i] == a[i+1]){
            a[i] *= 2;
            diem += a[i];
            for( int j = i+1; j < n-1; j++){
                a[j] = a[j+1];
            }
            a[n-1] = 0;
        }
    }
}
void xu_ly( int a[][100], char huong, int n, int &diem){
    if( huong == 'w' || huong == 'ư'){
        for( int j = 0; j < n; j++){
            int b[n];
            for( int i = 0; i < n; i++){
                b[i] = a[i][j];
            }
            dich_chuyen(b,n, diem);
            for( int i = 0; i < n; i++){
                a[i][j] = b[i];
            }
        }
    }
    else if( huong == 's'){
        for( int j = 0; j < n; j++){
            int b[n];
            for( int i = 0; i < n; i++){
                b[n-1-i] = a[i][j];
            }
            dich_chuyen(b,n, diem);
            for( int i = 0; i < n; i++){
                a[i][j] = b[n-1-i];
            }
        }
    }
    else if( huong == 'a'){
        for( int i = 0;i < n; i++){
            int b[n];
            for( int j = 0; j < n; j++){
                b[j] = a[i][j];
            }
            dich_chuyen(b,n, diem);
            for( int j = 0; j < n; j++){
                a[i][j] = b[j];
            }
        }
    }
    else if( huong == 'd'){
        for( int i = 0; i < n; i++){
            int b[n];
            for( int j = 0; j < n; j++){
                b[n-1-j] = a[i][j];
            }
            dich_chuyen(b,n, diem);
            for( int j = 0; j < n; j++){
                a[i][j] = b[n-1-j];
            }
        }
    }
}
bool kt_con_trong( int a[][100], int n){
    // kiem tra so o 0 lon hon hoac bang 4 thi tra ve 1
    int dem = 0;
    for( int i = 0; i < n; i++){
        for( int j = 0; j < n; j++){
            if( a[i][j] == 0) dem ++;
        }
    }
    if( dem >= 1) return true;
    else return false;
}
bool kt_trung( int a[][100],int n, int x, int y)
{
    if( a[x][y] != 0) return true;
    else return false;
}
void spon(int a[][100], int n)
{
    int x, y;
    do{
        x = rand()%(n-1-0+1)+0;
        y = rand()%(n-1-0+1)+0;
    }while (kt_trung(a,n,x,y) == true);
    // spon ra so lon nhat
    int maxn = 1;
    for( int i = 0; i < n; i++){
        for( int j = 0; j < n; j++){
            if( a[i][j] != 0) maxn = max( a[i][j], maxn);
        }
    }
//============spon so================================
    int chi_so;
    int gia_tri[]={ 2, 4, 8, 16, 32, 64, 128, 256, 512};
    for( int k = 0; k < 10; k ++){
        if( maxn == gia_tri[k]) {chi_so = rand()%(k-1-0+1)+0; break;}
    }
    a[x][y] = gia_tri[chi_so];
}
//================in ra man hinh===========================
int do_dai( int a){
    int do_dai = 0;
    if( a == 0) return 1;
    while(a> 0){
        do_dai++;
        a /= 10;
    }
    return do_dai;
}
int max_len_strlen(int a[][100], int n)
{
    int maxl = 0;
    for( int i =0; i < n; i++){
        for( int j = 0; j < n; j++){
            int dai = do_dai(a[i][j]);
            maxl = max( maxl, dai);
        }
    }
    return maxl;
}
void xuat( int a[][100], int n, int diem){
     int maxl = max_len_strlen(a, n);
        cout<<"\n\n\n\n";
        cout << "                                                   level "<<n<<endl;
        cout << "                                                   score: "<<diem;
        cout <<"\n\n";
        //=============================================================
        for( int i = 0; i < n ; i++){
        cout << "                                                   |";
        for( int j = 0; j < n; j++){
            if( a[i][j] == 0) SetColor(0);
            if( a[i][j] == 2) SetColor(1);
            if( a[i][j] == 4) SetColor(2);
            if( a[i][j] == 8) SetColor(3);
            if( a[i][j] == 16) SetColor(4);
            if( a[i][j] == 32) SetColor(5);
            if( a[i][j] == 64) SetColor(6);
            if( a[i][j] == 128) SetColor(15);
            if( a[i][j] == 256) SetColor(9);
            if( a[i][j] == 512) SetColor(13);
            if( a[i][j] == 1024) SetColor(11);
            if( a[i][j] == 2048) SetColor(12);

            //===================================================
            for (int k = 0; k < maxl - do_dai(a[i][j]); k++)
            {
                cout<<" ";
            }
            //=====ve khung======================================
            if( j == n-1) { cout<<a[i][j]; SetColor(7); cout<<"|";}
            else cout<<a[i][j]<<" ";
            //===================================================
            SetColor(7);
            }
            cout << endl;
        }
        //=============================================================
        for( int i =0; i < n; i++){
        for( int j = 0; j < n; j++){
            if( a[i][j] == 2048) {cout<<"\n                                                   YOU WIN"; return;}
        }
    }
}
bool kt_sai( int a[][100] , int n)
{
    for( int i =0; i < n; i++){
        for( int j = 0; j < n; j++){
            if( a[i][j] == a[i-1][j]) return true;
            if( a[i][j] == a[i+1][j]) return true;
            if( a[i][j] == a[i][j-1]) return true;
            if( a[i][j] == a[i][j+1]) return true;
        }
    }
    return false;
}
bool kt_khac( int a[][100], int c[][100], int n){
    for( int i =0; i < n; i++){
        for( int j = 0; j < n; j++){
            if( a[i][j] != c[i][j]) return false;
        }
    }
    return true;
}
int main()
{
    int a[100][100], n;
    int diem = 0;
    srand((int)time(0));
    SetColor(11);
    cout<<"\n\n                                                  GAME 2048\n"<<endl;
    SetColor(7);
    cout<<"                                                   control:"<<endl;
    cout<<"                                                   w: up"<<endl;
    cout<<"                                                   s: down"<<endl;
    cout<<"                                                   d: left"<<endl;
    cout<<"                                                   a: right\n";
    cout<<"\n                                            nhap n ( 2 <= n <= 10): ";
    cin >> n;
    if( n < 2 || n > 10){
        cout <<"\nNhap lai n : ";
        cin >> n;
    }
    system("cls");
    //====================================================
    // spon luc dau
    int dem =0; int chi_so1;
    int gia_tri1[]={0, 0 ,0, 2, 2, 2, 4,4};
    for( int i = 0; i < n; i++){
        for( int j = 0; j < n; j++){
            if( dem >= n*n/2) a[i][j] = 0;
            else{
                chi_so1 = rand()%(7-0+1)+0;
                a[i][j] = gia_tri1[chi_so1];
                if(a[i][j] != 0) dem++;
            }
    }
    }
    //====================================================
    int c[100][100];
    xuat( a, n, diem);
    while ( true){
        char huong;
        cin >> huong;
        if(( huong != 'w' && huong != 'ư'&&huong != 's' && huong != 'a'&& huong != 'd')) cin >> huong;
        system("cls");
        for( int i = 0; i < n; i++){
        for( int j = 0; j < n; j++){
            c[i][j] = a[i][j];
        }
        }
        xu_ly( a, huong,n, diem);
        if( kt_con_trong(a,n) == true && kt_khac(c, a,n) == false){
            spon(a,n);
        }
        xuat( a, n, diem);
        if( kt_con_trong(a, n) == false && kt_sai(a, n) == false)
        {
            cout <<"\n                                    YOU LOSE";
            break;
        }

    }
    return 0;
}



