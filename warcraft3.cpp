#include<iostream>
#include<algorithm>
#include<iomanip>
#include<vector>
using namespace std;
int M,N,K,T;//分别为司令部初始生命元、城市数量、忠诚度、分钟
int hour;//用来记录时间
int total_blood[5]={};//用来记录每种魔兽的血量
int attack[5]={};//记录每种魔兽的攻击力
string type_to_name[5]={"dragon","ninja","iceman","lion","wolf"};
int rorder[5]={2,3,4,1,0};//记录双方阵营生成魔兽的顺序
int border[5]={3,0,1,2,4};
class redCenter;
class Weapon{
    public:
        int type;
        int used;
        Weapon(int i=0,int j=0):type(i),used(j){}
};
int weapon_hurt(int w,int force){
    if(w==0)return force*2/10;
    if(w==1)return force*4/10;
    return force*3/10;
}
int bomb_self_hurt(int force){
    return (int(force*4/10))/2;
}
class warrior{
    public:
        int type;
        int number;
        int force;
        int element;
        int loyalty;
        vector<Weapon> weapons;
        warrior(int i,int j=0):number(i),loyalty(j){}
        void sort_weapon_for_fight(){
            stable_sort(weapons.begin(), weapons.end(), [](const Weapon& a, const Weapon& b) {
            if (a.type != b.type) return a.type < b.type;
            if (a.type == 2) return a.used > b.used; // arrow: 用过的排前面
            return false; });
        }
        void sort_weapon_for_take(){
            stable_sort(weapons.begin(), weapons.end(), [](const Weapon& a, const Weapon& b) {
            if (a.type != b.type) return a.type < b.type;
            if (a.type == 2) return a.used < b.used; // arrow: 用过的排前面
            return false; });
        }
        int weapon_count() {
            return (int)weapons.size();
        }
        bool has_weapon() {
            return !weapons.empty();
        }
        int count_weapon_type(int t){
            int cnt=0;
            for(auto &w:weapons){
                if(w.type==t)cnt++;
            }
            return cnt;
        }
};
class dragon:public warrior{
    public:
        dragon(int i):warrior(i){
            type=0;
            force=attack[0];
            element=total_blood[0];
            weapons.push_back(Weapon(number%3,0));
        }
};
class ninja:public warrior{
    public:
        
        ninja(int i):warrior(i){
            type=1;
            force=attack[1];
            element=total_blood[1];
            weapons.push_back(Weapon(number%3,0));
            weapons.push_back(Weapon((number+1)%3,0));
        }
};
class iceman:public warrior{
    public:
        iceman(int i):warrior(i){
            type=2;
            force=attack[2];
            element=total_blood[2];
            weapons.push_back(Weapon(number%3,0));
        }
};
class lion:public warrior{
    public:
        lion(int i,int j):warrior(i,j){
            type=3;
            force=attack[3];
            element=total_blood[3];
            weapons.push_back(Weapon(number%3,0));
        }

};
class wolf:public warrior{
    public:
        wolf(int i):warrior(i){
            type=4;
            force=attack[4];
            element=total_blood[4];
        }
};
class redCenter{
    public:
        int source;
        int pos;
        int TotalMonster;
        warrior* p;
        warrior* tmp;
        bool occupied;
        redCenter(int i){
            source=i;
            pos=0;
            TotalMonster=0;
            occupied=false;
            p=NULL;
            tmp=NULL;
        }
        void make_monster(){
            for(int i=0;i<5;i++){
                if(source<total_blood[rorder[pos]]){
                    break;
                }
                else{
                    source-=total_blood[rorder[pos]];
                    TotalMonster++;
                    switch(rorder[pos]){
                        case 0:p=new dragon(TotalMonster);break;
                        case 1:p=new ninja(TotalMonster);break;
                        case 2:p=new iceman(TotalMonster);break;
                        case 3:p=new lion(TotalMonster,source);break;
                        case 4:p=new wolf(TotalMonster);break;
                    }
                    
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":00 ";
                    cout<<"red "<<type_to_name[p->type]<<" "<<TotalMonster<<" born"<<endl;
                    if(rorder[pos]==3)
                        cout<<"Its loyalty is "<<p->loyalty<<endl;
                    pos=(pos+1)%5;
                    break;
                }
            }
        }
        void report(){
            cout<<setw(3)<<setfill('0')<<hour;
            cout<<":50 ";
            cout<<source<<" elements in red headquarter"<<endl;
        }

};
class blueCenter{
    public:
        int source;
        int pos;
        int TotalMonster;
        bool occupied;
        warrior* p;
        warrior* tmp;
        blueCenter(int i){
            source=i;
            pos=0;
            TotalMonster=0;
            occupied=false;
            p=NULL;
            tmp=NULL;
        }
        void make_monster(){
            for(int i=0;i<5;i++){
                if(source<total_blood[border[pos]]){
                    break;
                }
                else{
                    source-=total_blood[border[pos]];
                    TotalMonster++;
                    switch(border[pos]){
                        case 0:p=new dragon(TotalMonster);break;
                        case 1:p=new ninja(TotalMonster);break;
                        case 2:p=new iceman(TotalMonster);break;
                        case 3:p=new lion(TotalMonster,source);break;
                        case 4:p=new wolf(TotalMonster);break;
                    }
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":00 ";
                    cout<<"blue "<<type_to_name[p->type]<<" "<<TotalMonster<<" born"<<endl;
                    if(border[pos]==3)
                        cout<<"Its loyalty is "<<p->loyalty<<endl;
                    pos=(pos+1)%5;
                
                    break;
                }
            }
        }
        void report(){
            cout<<setw(3)<<setfill('0')<<hour;
            cout<<":50 ";
            cout<<source<<" elements in blue headquarter"<<endl;
        }
};
int g=1;
class City{
    public:
        warrior* p1;
        warrior* p2;
        warrior* tmp1;
        warrior* tmp2;
        int number;
        City(){
            p1=NULL;
            p2=NULL;
            tmp1=NULL;
            tmp2=NULL;
            number=g;
            g++;
        }
        void cheer(){
            if(p1&&p1->type==0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":40 ";
                cout<<"red "<<type_to_name[p1->type]<<" "<<p1->number
                    <<" yelled in city "<<number<<endl;
            }
            if(p2&&p2->type==0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":40 ";
                cout<<"blue "<<type_to_name[p2->type]<<" "<<p2->number
                    <<" yelled in city "<<number<<endl;
            }
        }
        void rob(){
            if(!p1||!p2)return;
            p2->sort_weapon_for_take();
            p1->sort_weapon_for_take();
            int c1=0,c2=0,c3=0;
            if(p1->type==4&&p2->type!=4){
                if(p2->count_weapon_type(0)>0){
                    
                    while(p1->weapon_count()<10&&p2->count_weapon_type(0)>0){
                        c1++;
                        p1->weapons.push_back(Weapon(0,0));
                        p2->weapons.erase(p2->weapons.begin());
                        
                    }
                    
                }
                else if(p2->count_weapon_type(1)>0){
                    
                    while(p1->weapon_count()<10&&p2->count_weapon_type(1)>0){
                        c2++;
                        p1->weapons.push_back(Weapon(1,0));
                        p2->weapons.erase(p2->weapons.begin());
                    }
                    
                }
                else if(p2->count_weapon_type(2)>0){
                    
                    while(p1->weapon_count()<10&&p2->count_weapon_type(2)>0){
                        c3++;
                        p1->weapons.push_back(Weapon(2,p2->weapons[0].used));
                        p2->weapons.erase(p2->weapons.begin());
                    }
                    
                }
                if(c1+c2+c3!=0){
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":35 ";
                    if(c1!=0)
                    cout<<"red wolf "<<p1->number<<" took "<<c1<<" sword from blue "
                        <<type_to_name[p2->type]<<" "<<p2->number<<" in city "<<number<<endl;
                    if(c2!=0)
                    cout<<"red wolf "<<p1->number<<" took "<<c2<<" bomb from blue "
                        <<type_to_name[p2->type]<<" "<<p2->number<<" in city "<<number<<endl;
                    if(c3!=0)
                    cout<<"red wolf "<<p1->number<<" took "<<c3<<" arrow from blue "
                        <<type_to_name[p2->type]<<" "<<p2->number<<" in city "<<number<<endl;
                }
            }
            else if(p2->type==4&&p1->type!=4){
                if(p1->count_weapon_type(0)>0){
                    
                    while(p2->weapon_count()<10&&p1->count_weapon_type(0)>0){
                        c1++;
                        p2->weapons.push_back(Weapon(0,0));
                        p1->weapons.erase(p1->weapons.begin());
                        
                    }
                    
                }
                else if(p1->count_weapon_type(1)>0){

                    while(p2->weapon_count()<10&&p1->count_weapon_type(1)>0){
                        c2++;
                        p2->weapons.push_back(Weapon(1,0));
                        p1->weapons.erase(p1->weapons.begin());
                    }
                    
                }
                else if(p1->count_weapon_type(2)>0){
                    
                    while(p2->weapon_count()<10&&p1->count_weapon_type(2)>0){
                        c3++;
                        p2->weapons.push_back(Weapon(2,p1->weapons[0].used));
                        p1->weapons.erase(p1->weapons.begin());
                    }
                    
                }
                if(c1+c2+c3!=0){
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":35 ";
                    if(c1!=0)
                    cout<<"blue wolf "<<p2->number<<" took "<<c1<<" sword from red "
                        <<type_to_name[p1->type]<<" "<<p1->number<<" in city "<<number<<endl;
                    if(c2!=0)
                    cout<<"blue wolf "<<p2->number<<" took "<<c2<<" bomb from red "
                        <<type_to_name[p1->type]<<" "<<p1->number<<" in city "<<number<<endl;
                    if(c3!=0)
                    cout<<"blue wolf "<<p2->number<<" took "<<c3<<" arrow from red "
                        <<type_to_name[p1->type]<<" "<<p1->number<<" in city "<<number<<endl;
                }
            }
        }
        void take(warrior* winner,warrior* loser){
            loser->sort_weapon_for_take();
            winner->sort_weapon_for_take();
            if(loser->count_weapon_type(0)>0){
                    
                    while(winner->weapon_count()<10&&loser->count_weapon_type(0)>0){
                    
                        winner->weapons.push_back(Weapon(0,0));
                        loser->weapons.erase(loser->weapons.begin());
                        
                    }

                }
                if(loser->count_weapon_type(1)>0){

                    while(winner->weapon_count()<10&&loser->count_weapon_type(1)>0){
                        
                        winner->weapons.push_back(Weapon(1,0));
                        loser->weapons.erase(loser->weapons.begin());
                    }
                }
                if(loser->count_weapon_type(2)>0){
                    
                    while(winner->weapon_count()<10&&loser->count_weapon_type(2)>0){
                        
                        winner->weapons.push_back(Weapon(2,loser->weapons[0].used));
                        loser->weapons.erase(loser->weapons.begin());
                    }
            
                }

        }
        void fight(){
            if(!p1||!p2) return;
            p1->sort_weapon_for_fight();
            p2->sort_weapon_for_fight();
            int i=-5;
            int rpos=0;
            int bpos=0;
            //注意奇偶对攻击顺序的影响,注意处死，注意ninja的bomb特性
            while(p1&&p2){
                if(!p1->has_weapon()&&!p2->has_weapon()){
                    i=0;
                    break;
                }
                if(p1->count_weapon_type(0)*weapon_hurt(0,p1->force)+p1->count_weapon_type(1)*weapon_hurt(1,p1->force)+p1->count_weapon_type(2)*weapon_hurt(2,p1->force)==0
                && p2->count_weapon_type(0)*weapon_hurt(0,p2->force)+p2->count_weapon_type(1)*weapon_hurt(1,p2->force)+p2->count_weapon_type(2)*weapon_hurt(2,p2->force)==0)
                {
                    for(int k=0;k<p1->weapons.size();k++){
                        if(p1->weapons[k].type==0)continue;
                        else{
                            p1->weapons.erase(p1->weapons.begin()+k);
                            k--;
                        }
                    }
                    for(int k=0;k<p2->weapons.size();k++){
                        if(p2->weapons[k].type==0)continue;
                        else{
                            p2->weapons.erase(p2->weapons.begin()+k);
                            k--;
                        }
                    }
                    i=0;
                    break;
                }
                if(!p1->has_weapon()){
                    p1->element-=weapon_hurt(p2->weapons[bpos].type,p2->force);

                    if(p2->weapons[bpos].type==1){
                        if(p2->type!=1)p2->element-=bomb_self_hurt(p2->force);
                        p2->weapons.erase(p2->weapons.begin()+bpos);
                    }
                    else if(p2->weapons[bpos].type==2){
                        if(p2->weapons[bpos].used==0){
                            p2->weapons[bpos].used++;
                            bpos++;
                        }
                        else p2->weapons.erase(p2->weapons.begin()+bpos);
                    }
                    else bpos++;
                    if(p2->weapons.empty()) bpos = 0;
                    else bpos%=p2->weapons.size();
                    if(p2->element<=0||p1->element<=0) break;
                    continue;
                }
                if(!p2->has_weapon()){
                    p2->element-=weapon_hurt(p1->weapons[rpos].type,p1->force);

                    if(p1->weapons[rpos].type==1){
                        if(p1->type!=1)p1->element-=bomb_self_hurt(p1->force);
                        p1->weapons.erase(p1->weapons.begin()+rpos);
                    }
                    else if(p1->weapons[rpos].type==2){
                        if(p1->weapons[rpos].used==0){
                            p1->weapons[rpos].used++;
                            rpos++;
                        }
                        else p1->weapons.erase(p1->weapons.begin()+rpos);
                    }
                    else rpos++;
                    if(p1->weapons.empty()) rpos = 0;
                    else rpos%=p1->weapons.size();
                    if(p2->element<=0||p1->element<=0) break;
                    continue;
                }
                if(number%2==1){
                    p2->element-=weapon_hurt(p1->weapons[rpos].type,p1->force);

                    if(p1->weapons[rpos].type==1){
                        if(p1->type!=1)p1->element-=bomb_self_hurt(p1->force);
                        p1->weapons.erase(p1->weapons.begin()+rpos);
                    }
                    else if(p1->weapons[rpos].type==2){
                        if(p1->weapons[rpos].used==0){
                            p1->weapons[rpos].used++;
                            rpos++;
                        }
                        else p1->weapons.erase(p1->weapons.begin()+rpos);
                    }
                    else rpos++;
                    if(p1->weapons.empty()) rpos = 0;
                    else rpos%=p1->weapons.size();
                    if(p2->element<=0||p1->element<=0) break;
                    
        
                    

                    p1->element-=weapon_hurt(p2->weapons[bpos].type,p2->force);

                    if(p2->weapons[bpos].type==1){
                        if(p2->type!=1)p2->element-=bomb_self_hurt(p2->force);
                        p2->weapons.erase(p2->weapons.begin()+bpos);
                        
                    }
                    else if(p2->weapons[bpos].type==2){
                        if(p2->weapons[bpos].used==0){
                            p2->weapons[bpos].used++;
                            bpos++;
                        }
                        else p2->weapons.erase(p2->weapons.begin()+bpos);
                    }
                    else bpos++;
                    if(p2->weapons.empty()) bpos = 0;
                    else bpos%=p2->weapons.size();
                    if(p2->element<=0||p1->element<=0) break;
                }
                else{
                    p1->element-=weapon_hurt(p2->weapons[bpos].type,p2->force);

                    if(p2->weapons[bpos].type==1){
                        if(p2->type!=1)p2->element-=bomb_self_hurt(p2->force);
                        p2->weapons.erase(p2->weapons.begin()+bpos);
                    }
                    else if(p2->weapons[bpos].type==2){
                        if(p2->weapons[bpos].used==0){
                            p2->weapons[bpos].used++;
                            bpos++;
                        }
                        else p2->weapons.erase(p2->weapons.begin()+bpos);
                    }
                    else bpos++;
                    if(p2->weapons.empty()) bpos = 0;
                    else bpos%=p2->weapons.size();
                    if(p2->element<=0||p1->element<=0) break;


                    p2->element-=weapon_hurt(p1->weapons[rpos].type,p1->force);

                    if(p1->weapons[rpos].type==1){
                        if(p1->type!=1)p1->element-=bomb_self_hurt(p1->force);
                        p1->weapons.erase(p1->weapons.begin()+rpos);
                    }
                    else if(p1->weapons[rpos].type==2){
                        if(p1->weapons[rpos].used==0){
                            p1->weapons[rpos].used++;
                            rpos++;
                        }
                        else p1->weapons.erase(p1->weapons.begin()+rpos);
                    }
                    else rpos++;
                    if(p1->weapons.empty()) rpos = 0;
                    else rpos%=p1->weapons.size();
                    if(p2->element<=0||p1->element<=0) break;
                }
            }
            if(i==0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":40 ";
                cout<<"both red "<<type_to_name[p1->type]<<" "<<p1->number
                    <<" and blue "<<type_to_name[p2->type]<<" "<<p2->number
                    <<" were alive in city "<<number<<endl;
            }
            //以下两种情况注意武器分配
            else if(p1->element<=0&&p2->element>0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":40 ";
                cout<<"blue "<<type_to_name[p2->type]<<" "<<p2->number<<" killed red "
                    <<type_to_name[p1->type]<<" "<<p1->number<<" in city "<<number
                    <<" remaining "<<p2->element<<" elements"<<endl;
                take(p2,p1);
                p1=NULL;
            }
            else if(p2->element<=0&&p1->element>0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":40 ";
                cout<<"red "<<type_to_name[p1->type]<<" "<<p1->number<<" killed blue "
                    <<type_to_name[p2->type]<<" "<<p2->number<<" in city "<<number
                    <<" remaining "<<p1->element<<" elements"<<endl;
                take(p1,p2);
                p2=NULL;
            }
            else if(p2->element>0&&p1->element>0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":40 ";
                cout<<"both red "<<type_to_name[p1->type]<<" "<<p1->number<<" and blue "
                    <<type_to_name[p2->type]<<" "<<p2->number<<" were alive in city "<<number<<endl;
            }
            else{
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":40 ";
                cout<<"both red "<<type_to_name[p1->type]<<" "<<p1->number<<" and blue "
                    <<type_to_name[p2->type]<<" "<<p2->number<<" died in city "<<number<<endl;
                p1=NULL;
                p2=NULL;
            }
            cheer();
        }
        void report(){
            if(p1){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":55 ";
                int sword_cnt = p1->count_weapon_type(0);
                int bomb_cnt = p1->count_weapon_type(1);
                int arrow_cnt = p1->count_weapon_type(2);

                cout<<"red "<<type_to_name[p1->type]<<" "<<p1->number
                    <<" has "<<sword_cnt<<" sword "<<bomb_cnt<<" bomb "
                    <<arrow_cnt<<" arrow and "<<p1->element<<" elements"<<endl;
            }
            if(p2){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":55 ";
                int sword_cnt = p2->count_weapon_type(0);
                int bomb_cnt = p2->count_weapon_type(1);
                int arrow_cnt = p2->count_weapon_type(2);

                cout<<"blue "<<type_to_name[p2->type]<<" "<<p2->number
                    <<" has "<<sword_cnt<<" sword "<<bomb_cnt<<" bomb "
                    <<arrow_cnt<<" arrow and "<<p2->element<<" elements"<<endl;
            }

            
            
        }
    
};
int main(){
    int count=0;
    int n;
    cin>>n;
    while(n>0){
        cin>>M>>N>>K>>T;
        g=1;
        City city[N];
        for(int i=0;i<5;i++)
            cin>>total_blood[i];
        for(int i=0;i<5;i++)
            cin>>attack[i];
        redCenter rh(M);
        blueCenter bh(M);
        cout<<"Case "<<++count<<":"<<endl;
        n--;
        while(!rh.occupied&&!bh.occupied){
            //1.武士降生111
            if(hour*60>T)break;
            rh.make_monster();
            bh.make_monster();
            
            //2.lion逃跑111
            if(hour*60+5>T)break;
            if(rh.p&&rh.p->type==3&&rh.p->loyalty<=0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":05 ";
                cout<<"red lion "<<rh.p->number<<" ran away"<<endl;
                rh.p=NULL;
            }
            for(int i=0;i<N;i++){
                if(city[i].p1&&city[i].p1->type==3&&city[i].p1->loyalty<=0){
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":05 ";
                    cout<<"red lion "<<city[i].p1->number<<" ran away"<<endl;
                    city[i].p1=NULL;
                }
                if(city[i].p2&&city[i].p2->type==3&&city[i].p2->loyalty<=0){
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":05 ";
                    cout<<"blue lion "<<city[i].p2->number<<" ran away"<<endl;
                    city[i].p2=NULL;
                }
            }
            if(bh.p&&bh.p->type==3&&bh.p->loyalty<=0){
                cout<<setw(3)<<setfill('0')<<hour;
                cout<<":05 ";
                cout<<"blue lion "<<bh.p->number<<" ran away"<<endl;
                bh.p=NULL;
            }
            

            //3.武士前进，注意抵达司令部情况、司令部被占领情况111
            if(hour*60+10>T)break;
            if(N>=3){
                if(city[0].p2){
                    rh.tmp=city[0].p2;
                    city[0].p2=NULL;
                    rh.occupied=true;
                    if(rh.tmp->type==2)
                        rh.tmp->element-=int(rh.tmp->element/10);
                    if(rh.tmp->type==3)
                        rh.tmp->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[rh.tmp->type]<<" "<<rh.tmp->number
                        <<" reached red headquarter with "<<rh.tmp->element<<" elements "
                        <<"and force "<<rh.tmp->force<<endl;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red headquarter was taken"<<endl;
                }
                if(rh.p){
                    city[0].tmp1=rh.p;
                    rh.p=NULL;
                    if(city[0].tmp1->type==2)
                        city[0].tmp1->element-=int(city[0].tmp1->element/10);
                    if(city[0].tmp1->type==3)
                        city[0].tmp1->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[city[0].tmp1->type]<<" "<<city[0].tmp1->number
                        <<" marched to city 1 with "<<city[0].tmp1->element<<" elements and force "<<city[0].tmp1->force
                        <<endl;
                }
                if(city[1].p2){
                    city[0].tmp2=city[1].p2;
                    city[1].p2=NULL;
                    if(city[0].tmp2->type==2)
                        city[0].tmp2->element-=int(city[0].tmp2->element/10);
                    if(city[0].tmp2->type==3)
                        city[0].tmp2->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[city[0].tmp2->type]<<" "<<city[0].tmp2->number
                        <<" marched to city 1 with "<<city[0].tmp2->element<<" elements and force "<<city[0].tmp2->force
                        <<endl;
                }
                
                for(int i=1;i<N-1;i++){
                    if(city[i-1].p1){
                        city[i].tmp1=city[i-1].p1;
                        city[i-1].p1=NULL;
                        if(city[i].tmp1->type==2)
                            city[i].tmp1->element-=int(city[i].tmp1->element/10);
                        if(city[i].tmp1->type==3)
                            city[i].tmp1->loyalty-=K;
                        cout<<setw(3)<<setfill('0')<<hour;
                        cout<<":10 ";
                        cout<<"red "<<type_to_name[city[i].tmp1->type]<<" "<<city[i].tmp1->number
                        <<" marched to city "<<i+1<<" with "<<city[i].tmp1->element<<" elements and force "<<city[i].tmp1->force
                        <<endl;
                    }
                    if(city[i+1].p2){
                        city[i].tmp2=city[i+1].p2;
                        city[i+1].p2=NULL;
                        if(city[i].tmp2->type==2)
                            city[i].tmp2->element-=int(city[i].tmp2->element/10);
                        if(city[i].tmp2->type==3)
                            city[i].tmp2->loyalty-=K;
                        cout<<setw(3)<<setfill('0')<<hour;
                        cout<<":10 ";
                        cout<<"blue "<<type_to_name[city[i].tmp2->type]<<" "<<city[i].tmp2->number
                        <<" marched to city "<<i+1<<" with "<<city[i].tmp2->element<<" elements and force "<<city[i].tmp2->force
                        <<endl;
                    }
                }
                if(city[N-2].p1){
                    city[N-1].tmp1=city[N-2].p1;
                    city[N-2].p1=NULL;
                    if(city[N-1].tmp1->type==2)
                        city[N-1].tmp1->element-=int(city[N-1].tmp1->element/10);
                    if(city[N-1].tmp1->type==3)
                        city[N-1].tmp1->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[city[N-1].tmp1->type]<<" "<<city[N-1].tmp1->number
                        <<" marched to city "<<N<<" with "<<city[N-1].tmp1->element<<" elements and force "<<city[N-1].tmp1->force
                        <<endl;
                }
                if(bh.p){
                    city[N-1].tmp2=bh.p;
                    bh.p=NULL;
                    if(city[N-1].tmp2->type==2)
                        city[N-1].tmp2->element-=int(city[N-1].tmp2->element/10);
                    if(city[N-1].tmp2->type==3)
                        city[N-1].tmp2->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[city[N-1].tmp2->type]<<" "<<city[N-1].tmp2->number
                        <<" marched to city "<<N<<" with "<<city[N-1].tmp2->element<<" elements and force "<<city[N-1].tmp2->force
                        <<endl;
                }
                if(city[N-1].p1){
                    bh.tmp=city[N-1].p1;
                    city[N-1].p1=NULL;
                    bh.occupied=true;
                    if(bh.tmp->type==2)
                        bh.tmp->element-=int(bh.tmp->element/10);
                    if(bh.tmp->type==3)
                        bh.tmp->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[bh.tmp->type]<<" "<<bh.tmp->number
                        <<" reached blue headquarter with "<<bh.tmp->element<<" elements "
                        <<"and force "<<bh.tmp->force<<endl;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue headquarter was taken"<<endl;
                }
            }
            else if(N==2){
                if(city[0].p2){
                    rh.tmp=city[0].p2;
                    city[0].p2=NULL;
                    rh.occupied=true;
                    if(rh.tmp->type==2)
                        rh.tmp->element-=int(rh.tmp->element/10);
                    if(rh.tmp->type==3)
                        rh.tmp->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[rh.tmp->type]<<" "<<rh.tmp->number
                        <<" reached red headquarter with "<<rh.tmp->element<<" elements "
                        <<"and force "<<rh.tmp->force<<endl;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red headquarter was taken"<<endl;
                }
                if(rh.p){
                    city[0].tmp1=rh.p;
                    rh.p=NULL;
                    if(city[0].tmp1->type==2)
                        city[0].tmp1->element-=int(city[0].tmp1->element/10);
                    if(city[0].tmp1->type==3)
                        city[0].tmp1->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[city[0].tmp1->type]<<" "<<city[0].tmp1->number
                        <<" marched to city 1 with "<<city[0].tmp1->element<<" elements and force "<<city[0].tmp1->force
                        <<endl;
                }
                if(city[1].p2){
                    city[0].tmp2=city[1].p2;
                    city[1].p2=NULL;
                    if(city[0].tmp2->type==2)
                        city[0].tmp2->element-=int(city[0].tmp2->element/10);
                    if(city[0].tmp2->type==3)
                        city[0].tmp2->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[city[0].tmp2->type]<<" "<<city[0].tmp2->number
                        <<" marched to city 1 with "<<city[0].tmp2->element<<" elements and force "<<city[0].tmp2->force
                        <<endl;
                }
                if(city[N-2].p1){
                    city[N-1].tmp1=city[N-2].p1;
                    city[N-2].p1=NULL;
                    if(city[N-1].tmp1->type==2)
                        city[N-1].tmp1->element-=int(city[N-1].tmp1->element/10);
                    if(city[N-1].tmp1->type==3)
                        city[N-1].tmp1->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[city[N-1].tmp1->type]<<" "<<city[N-1].tmp1->number
                        <<" marched to city "<<N<<" with "<<city[N-1].tmp1->element<<" elements and force "<<city[N-1].tmp1->force
                        <<endl;
                }
                if(bh.p){
                    city[N-1].tmp2=bh.p;
                    bh.p=NULL;
                    if(city[N-1].tmp2->type==2)
                        city[N-1].tmp2->element-=int(city[N-1].tmp2->element/10);
                    if(city[N-1].tmp2->type==3)
                        city[N-1].tmp2->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[city[N-1].tmp2->type]<<" "<<city[N-1].tmp2->number
                        <<" marched to city "<<N<<" with "<<city[N-1].tmp2->element<<" elements and force "<<city[N-1].tmp2->force
                        <<endl;
                }
                if(city[N-1].p1){
                    bh.tmp=city[N-1].p1;
                    city[N-1].p1=NULL;
                    bh.occupied=true;
                    if(bh.tmp->type==2)
                        bh.tmp->element-=int(bh.tmp->element/10);
                    if(bh.tmp->type==3)
                        bh.tmp->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[bh.tmp->type]<<" "<<bh.tmp->number
                        <<" reached blue headquarter with "<<bh.tmp->element<<" elements "
                        <<"and force "<<bh.tmp->force<<endl;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue headquarter was taken"<<endl;
                }
                
            }
            else{
                if(city[0].p2){
                    rh.tmp=city[0].p2;
                    city[0].p2=NULL;
                    rh.occupied=true;
                    if(rh.tmp->type==2)
                        rh.tmp->element-=int(rh.tmp->element/10);
                    if(rh.tmp->type==3)
                        rh.tmp->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[rh.tmp->type]<<" "<<rh.tmp->number
                        <<" reached red headquarter with "<<rh.tmp->element<<" elements "
                        <<"and force "<<rh.tmp->force<<endl;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red headquarter was taken"<<endl;
                }
                if(rh.p){
                    city[0].tmp1=rh.p;
                    rh.p=NULL;
                    if(city[0].tmp1->type==2)
                        city[0].tmp1->element-=int(city[0].tmp1->element/10);
                    if(city[0].tmp1->type==3)
                        city[0].tmp1->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[city[0].tmp1->type]<<" "<<city[0].tmp1->number
                        <<" marched to city 1 with "<<city[0].tmp1->element<<" elements and force "<<city[0].tmp1->force
                        <<endl;
                }
                if(bh.p){
                    city[N-1].tmp2=bh.p;
                    bh.p=NULL;
                    if(city[N-1].tmp2->type==2)
                        city[N-1].tmp2->element-=int(city[N-1].tmp2->element/10);
                    if(city[N-1].tmp2->type==3)
                        city[N-1].tmp2->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue "<<type_to_name[city[N-1].tmp2->type]<<" "<<city[N-1].tmp2->number
                        <<" marched to city "<<N<<" with "<<city[N-1].tmp2->element<<" elements and force "<<city[N-1].tmp2->force
                        <<endl;
                }
                if(city[N-1].p1){
                    bh.tmp=city[N-1].p1;
                    city[N-1].p1=NULL;
                    bh.occupied=true;
                    if(bh.tmp->type==2)
                        bh.tmp->element-=int(bh.tmp->element/10);
                    if(bh.tmp->type==3)
                        bh.tmp->loyalty-=K;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"red "<<type_to_name[bh.tmp->type]<<" "<<bh.tmp->number
                        <<" reached blue headquarter with "<<bh.tmp->element<<" elements "
                        <<"and force "<<bh.tmp->force<<endl;
                    cout<<setw(3)<<setfill('0')<<hour;
                    cout<<":10 ";
                    cout<<"blue headquarter was taken"<<endl;
                }
            }
            if(rh.occupied||bh.occupied)break;
            rh.p=rh.tmp;
            rh.tmp=NULL;
            bh.p=bh.tmp;
            bh.tmp=NULL;
            for(int i=0;i<N;i++){
                if(city[i].tmp1){
                    city[i].p1=city[i].tmp1;
                    city[i].tmp1=NULL;
                }
                if(city[i].tmp2){
                    city[i].p2=city[i].tmp2;
                    city[i].tmp2=NULL;
                }
            }
            //4.wolf抢武器111
            if(hour*60+35>T)break;
            for(int i=0;i<N;i++){
                city[i].rob();
                    
            }
            //5.战斗并报告战斗情况,注意dragon在战斗结束后没阵亡会欢呼
            if(hour*60+40>T)break;
            for(int i=0;i<N;i++){
                city[i].fight();
            }
            
                
            //6.司令部报告生命元111
            if(hour*60+50>T)break;
            rh.report();
            bh.report();
 
            //7.武士报告情况111
            if(hour*60+55>T)break;
            for(int i=0;i<N;i++){
                city[i].report();
            }
            hour++;
        }
        hour=0;
        for(int i=0;i<5;i++)
            total_blood[i]=0;
        for(int i=0;i<5;i++)
            attack[i]=0;
    }
    
}
