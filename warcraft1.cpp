#include<iostream>
#include<algorithm>
#include<iomanip>
using namespace std;
int hour;
string type_to_name[5]={"dragon","ninja","iceman","lion","wolf"};
class warrior{
	public:
		string color;
		static int rMonster[5];
		static int bMonster[5];//记录每种魔兽的数量
		int strength;
		int type;
		void born(){
			if(color=="red")
				cout<<" "<<color<<" "<<type_to_name[type]<<" "<<hour+1
			    	<<" born with strength "<<strength<<","<<rMonster[type]
			    	<<" "<<type_to_name[type]<<" in red headquarter"
			    	<<endl;
			else
				cout<<" "<<color<<" "<<type_to_name[type]<<" "<<hour+1
			    	<<" born with strength "<<strength<<","<<bMonster[type]
			    	<<" "<<type_to_name[type]<<" in blue headquarter"
			    	<<endl;
		}
		warrior(string color_,int type_,int strength_):
		color(color_),type(type_),strength(strength_){
			if(color=="red"){
				rMonster[type]++;
				}
			else {
				bMonster[type]++;
				}
		}
		
};
int warrior::rMonster[5]={};
int warrior::bMonster[5]={};
int main(){
	int n=0;
	int count=0;//记录回合数
	cin>>n;
	int M1,M2=0;
	int r[5]={2,3,4,1,0};
	int b[5]={3,0,1,2,4};//记录双方阵营生成魔兽的顺序
	int blood[5]={};//用来记录每种魔兽的血量
	while(n>0){
		hour=0;
		cout<<"Case:"<<++count<<endl;
		cin>>M1;M2=M1;//双方阵营的总血量
		for(int i=0;i<5;i++)
			cin>>blood[i];
		bool rstop=false;
		bool bstop=false;//判断是否结束生成魔兽
		int rpos=0,bpos=0;//记录生成到哪个魔兽了
		for(int i=0;i<5;i++){
			warrior::rMonster[i]=0;
			warrior::bMonster[i]=0;
		}//初始化双方每种魔兽的数量
		while(!rstop||!bstop){
			if(!rstop){
				int i;
				for(i=0;i<5;i++){
					if(M1>=blood[r[rpos]]){
						cout<<setw(3)<<setfill('0')<<hour;
						warrior a("red",r[rpos],blood[r[rpos]]);
						a.born();
						M1-=blood[r[rpos]];
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
					if(M2>=blood[b[bpos]]){
						cout<<setw(3)<<setfill('0')<<hour;
						warrior c("blue",b[bpos],blood[b[bpos]]);
						c.born();
						M2-=blood[b[bpos]];
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
