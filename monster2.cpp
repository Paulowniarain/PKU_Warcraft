#include<iostream>
#include<algorithm>
#include<iomanip>
#define red 0
#define blue 1
using namespace std;
int hour;
int source[2];
string color_to_word[2]={"red","blue"};
int strength[5]={};//用来记录每种魔兽的血量
string type_to_name[5]={"dragon","ninja","iceman","lion","wolf"};
string weapon_to_name[3]={"sword","bomb","arrow"};
class monster{
	public:
		int color;
        int type;
		static int TotalMonster[2][5];//记录每种魔兽的数量
		monster(int color_,int type_):
		color(color_),type(type_){
				TotalMonster[color][type]++;
                source[color]-=strength[type];
                cout<<" "<<color_to_word[color]<<" "<<type_to_name[type]<<" "<<hour+1
			    	<<" born with strength "<<strength[type]<<","<<TotalMonster[color][type]
			    	<<" "<<type_to_name[type]<<" in "<<color_to_word[color]<<" headquarter"
			    	<<endl;
		}
		
};
int monster::TotalMonster[2][5]={};
class dragon:public monster{
    public:
        int weapon;
        float morale;
        dragon(int color_):monster(color_,0){
            weapon=(hour+1)%3;
            morale=(float)source[color]/strength[0];
            cout<<"It has a "<<weapon_to_name[weapon]<<",and it's morale is "<<setprecision(2)<<fixed<<morale<<endl;

        }
};
class ninja:public monster{
    public:
        int weapon1;
        int weapon2;
        ninja(int color_):monster(color_,1){
            weapon1=(hour+1)%3;
            weapon2=(hour+2)%3;
            cout<<"It has a "<<weapon_to_name[weapon1]<<" and a "<<weapon_to_name[weapon2]<<endl;
		
        }
};
class iceman:public monster{
    public:
        int weapon;
        iceman(int color_):monster(color_,2){
            weapon=(hour+1)%3;
            cout<<"It has a "<<weapon_to_name[weapon]<<endl;
        }
};
class lion:public monster{
    public:
        int loyalty;
        lion(int color_):monster(color_,3){
            loyalty=source[color];
            cout<<"It's loyalty is "<<loyalty<<endl;
		}
};
class wolf:public monster{
    public:
        wolf(int color_):monster(color_,4){}
};
int main(){
	int n=0;
	int count=0;//记录回合数
	cin>>n;
	int r[5]={2,3,4,1,0};
	int b[5]={3,0,1,2,4};//记录双方阵营生成魔兽的顺序
	while(n>0){
		hour=0;
		cout<<"Case:"<<++count<<endl;
		cin>>source[0];source[1]=source[0];//双方阵营的总血量
		for(int i=0;i<5;i++)
			cin>>strength[i];
		bool rstop=false;
		bool bstop=false;//判断是否结束生成魔兽
		int rpos=0,bpos=0;//记录生成到哪个魔兽了
		for(int i=0;i<2;i++){
            for(int j=0;j<5;j++)
			monster::TotalMonster[i][j]=0;
		}//初始化双方每种魔兽的数量
		while(!rstop||!bstop){
			if(!rstop){
				int i;
				for(i=0;i<5;i++){
					if(source[0]>=strength[r[rpos]]){
						cout<<setw(3)<<setfill('0')<<hour;
						switch(r[rpos]){
                            case 0:{dragon a(0);break;}
                            case 1:{ninja a(0);break;}
                            case 2:{iceman a(0);break;}
                            case 3:{lion a(0);break;}
                            case 4:{wolf a(0);break;}
                        }
						rpos=(rpos+1)%5;
						break;
					}
					else
						rpos=(rpos+1)%5;
				}
				if(i==5){
					cout<<setw(3)<<setfill('0')<<hour;
					cout<<" red headquarter stops making warriors"<<endl;
					rstop=true;
				}
			}
			if(!bstop){
				int j;
				for(j=0;j<5;j++){
					if(source[1]>=strength[b[bpos]]){
						cout<<setw(3)<<setfill('0')<<hour;
						switch(b[bpos]){
                            case 0:{dragon a(1);break;}
                            case 1:{ninja a(1);break;}
                            case 2:{iceman a(1);break;}
                            case 3:{lion a(1);break;}
                            case 4:{wolf a(1);break;}
                        }
                        bpos=(bpos+1)%5;
						break;
					}
					else
						bpos=(bpos+1)%5;
				}
				if(j==5){
					cout<<setw(3)<<setfill('0')<<hour;
					cout<<" blue headquarter stops making warriors"<<endl;	
					bstop=true;
				}
			}
			hour++;
		}
		n--;
	}
	return 0;
}