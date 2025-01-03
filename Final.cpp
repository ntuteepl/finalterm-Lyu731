#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread> //用於延遲
#include <chrono> //用於指定時間

using namespace std;


class Character //角色的各項數值 
{
 protected:
 static const int EXP_LV=100; //角色升級所需的生命值 
 string name; //角色名稱 
 int hp; //角色血量 
 int level; //角色等級 
 int exp; //角色經驗值 
 int power; //角色攻擊力 
 int defense; //角色防禦力
 int knowledge; //角色知識值 
 int luck; //角色幸運值 
 int skillChoice=0; //技能選擇 

 void levelUp(int hInc, int pInc, int dInc, int kInc, int lInc); //角色升級函數 

public:
 Character(string n, int lv, int h, int po, int de, int kn, int lu); //角色建構函數 
 virtual void print(); //打印角色訊息 虛擬函數 
 virtual void beatMonster(int exp) = 0; //角色擊敗怪物獲得經驗值 虛擬函數 
 virtual void setHP(int) = 0; //角色血量函數 虛擬函數 
 virtual int getHP() = 0; //獲取角色血量 虛擬函數 
 virtual int getAttack() = 0; //獲取角色攻擊力 虛擬函數 
 virtual int getDefense() = 0; //獲取角色防禦力 虛擬函數 
 virtual void skill() = 0; //角色技能 虛擬函數 
 virtual void applyskill(int a) = 0; //應用技能效果 虛擬函數 
 string getName(); //獲取角色名稱 
};

Character::Character(string n, int lv, int h, int po, int de, int kn, int lu) //初始化 
    : name(n), level(lv), exp(pow(lv - 1, 2) * EXP_LV), hp(h), power(po), defense(de), knowledge(kn), luck(lu) {}

string Character::getName() 
{
 return this->name; //傳回角色名稱 
}

void Character::levelUp(int hInc, int pInc, int dInc, int kInc, int lInc) //角色升級函數 
{
 this->level++; //角色等級提升 
 this->hp+=hInc; //增加角色血量 
 this->power+=pInc; //增加角色攻擊力 
 this->defense+=dInc; //增加角色防禦力  
 this->knowledge+=kInc; //增加角色知識值 
 this->luck+=lInc; //增加角色幸運值 
}

void Character::print() 
{
 cout<<this->name <<": Lv"<<this->level; //打印角色名稱、等級
 cout<<"-HP"<<max(0,this->hp)<<"-Pow"<<this->power<<"-Def"<<this->defense<<"-Kno"<<this->knowledge<<"-Luck"<<this->luck<<"\n"; //打印角色血量、攻擊力、防禦力、知識值、幸運值
}


class Monster : public Character //怪物類別
{
 public:
 bool monsterAct; // 記錄怪物是否能行動
 Monster(int h, int po, int kn) : Character("", 0, h, po, 0, kn, 0) { monsterAct = true; } //初始化怪物 
 void print() { cout << "Monster "; Character::print(); } //打印怪物訊息 
 int getHP() { return hp; } //獲取怪物血量 
 void setHP(int hp) { this->hp = hp; } //設定怪物血量 
 int getAttack() { return power; } //獲取怪物防禦力 
 int getDefense() { return 0; } //怪物沒有防禦力
 void beatMonster(int exp) {} //處理怪物擊敗事件 
 void skill() {}; //處理怪物技能 
 void applyskill(int skillChoice) {}; //怪物應用技能效果 
};

class Tank : public Character //坦克類別
{
 private:
 static const int HP_LV=100; //定義升級時血量增量  
 static const int PO_LV=8; //定義升級時攻擊力增量  
 static const int DE_LV=12; //定義升級時防禦力增量  
 static const int KN_LV=5; //定義升級時知識值增量  
 static const int LU_LV=5; //定義升級時幸運值增量  
 Monster* targetMonster;

 public:
 void setTargetMonster(Monster* monster) 
 {
  targetMonster=monster;
 }
 Tank(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * DE_LV, lv * KN_LV, lv * LU_LV), targetMonster(NULL) {}
 void print() { cout << "Tank "; Character::print(); } //打印坦克角色訊息 
 int getHP() { return hp; } //獲取坦克血量 
 void setHP(int hp) { this->hp = hp; } //設定坦克血量 
 int getAttack() { return power; } //獲取坦克攻擊力 
 int getDefense() { return defense; } //獲取坦克防禦力 
 void beatMonster(int exp) //擊敗怪物獲取經驗值函式 
 {
  this->exp+=exp; //增加經驗值 
  while(this->exp >= pow(this->level, 2) * EXP_LV) //判斷是否可以升級 
   this->levelUp(HP_LV, PO_LV, DE_LV, KN_LV, LU_LV); //升級角色 
 }
 
 void randomCout() //定義訊息列表
 {
  vector<string> messages= 
  { 
   "AAAAAA瑞斯一打二 瑞斯一打三!",
   "RRR老爸剁起來!",
   "叔叔開剁囉!",
   "你看到我巨槌達瑞斯都不會怕的欸 還敢在那邊洗兵啊",
  };
  srand(static_cast<unsigned int>(time(0))); // 設定隨機種子
  int randomIndex = rand() % messages.size(); // 從訊息列表中隨機選擇
  cout<<messages[randomIndex]<<endl;
 }
 
 void skill() //選擇技能函式 
 {
  cout<<"選擇技能: 1.盾擊(1.2倍傷害) 2.提升自身防禦力(+50)\n";
  cin>>skillChoice; //輸入選擇的技能 
  applyskill(skillChoice); //呼叫技能函式 
 }
 void applyskill(int choice) //技能函式 
 {
  switch(choice) 
  {
   case 1:
   	{
   	 cout<<"!!使出盾擊!!\n";
     targetMonster->setHP(targetMonster->getHP() - (1.2 * targetMonster->getAttack())); // 對目標怪物造成傷害 
     randomCout(); //輸出隨機字元 
     this_thread::sleep_for(chrono::seconds(2)); //延遲2秒
     break;
    }
   case 2:
    cout<<"!!提升防禦力!!\n";
    defense += 50; //增加防禦力 
    break;
    }
 }
};

class Warrior : public Character //戰士類別
{
 private:
 static const int HP_LV=100; //定義升級時血量增量
 static const int PO_LV=10; //定義升級時攻擊力增量
 static const int DE_LV=9; //定義升級時防禦力增量
 static const int KN_LV=5; //定義升級時知識值增量
 static const int LU_LV=5; //定義升級時幸運值增量
 Monster* targetMonster;

 public:
 void setTargetMonster(Monster* monster) 
 {
  targetMonster=monster;
 }
 Warrior(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * DE_LV, lv * KN_LV, lv * LU_LV) {} //初始化戰士角色
 void print() { cout << "Warrior "; Character::print(); } //打印戰士角色訊息 
 int getHP() { return hp; } //獲取戰士血量 
 void setHP(int hp) { this->hp = hp; } //設定戰士血量 
 int getAttack() { return power; } //獲取戰士攻擊力 
 int getDefense() { return defense; } //獲取戰士防禦力  
 void beatMonster(int exp) //擊敗怪物獲取經驗值函式
 {
  this->exp+=exp; //增加經驗值 
  while(this->exp >= pow(this->level, 2) * EXP_LV) //判斷是否可以升級 
  this->levelUp(HP_LV, PO_LV, DE_LV, KN_LV, LU_LV); //升級角色 
 }
 
 void randomCout() // 定義訊息列表
 {
  vector<string> messages= 
  { 
   "這什麼到底什麼閃現齁齁齁齁齁",
   "還敢下來啊冰鳥!",
   "!AAA過來摟!",
   "!太神啦!", 
  };
  srand(static_cast<unsigned int>(time(0))); // 設定隨機種子
  int randomIndex = rand() % messages.size(); // 從訊息列表中隨機選擇
  cout<<messages[randomIndex]<<endl;
 }
 
 void skill() //選擇技能函式 
 {
  cout<<"選擇技能: 1.雙重斬擊(2倍傷害) 2.提升自身攻擊力(+50)\n";
  cin>>skillChoice; //輸入選擇的技能  
  applyskill(skillChoice); //呼叫技能函式 
 }
 void applyskill(int choice) //技能函式
 {
  switch(choice) 
  {
   case 1:
    cout<<"!!雙重斬擊!!\n";
    targetMonster->setHP(targetMonster->getHP() - (2 * targetMonster->getAttack())); //對目標怪物造成傷害
	randomCout(); //輸出隨機字元 
	this_thread::sleep_for(chrono::seconds(2)); //延遲2秒 
    break;
   case 2:
    cout<<"!!提升攻擊力!!\n";
    power+=50; //增加攻擊力 
    break;
   }
 }
};

class Wizard : public Character //法師類別 
{
 private:
 static const int HP_LV = 80; //定義升級時血量增量 
 static const int PO_LV = 4;  //定義升級時攻擊力增量 
 static const int DE_LV = 5; //定義升級時防禦力增量
 static const int KN_LV = 15; //定義升級時知識值增量 
 static const int LU_LV = 7; //定義升級時幸運值增量 
 Monster* targetMonster;
 
 public:
 void setTargetMonster(Monster* monster) 
 {
  targetMonster=monster;
 }
 Wizard(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * DE_LV, lv * KN_LV, lv * LU_LV) {} //初始化法師角色 
 void print() { cout << "Wizard "; Character::print(); } //打印法師角色訊息 
 int getHP() { return hp; } //獲取法師血量 
 void setHP(int hp) { this->hp = hp; } //設定法師血量 
 int getAttack() { return knowledge; } //獲取法師知識值(作為攻擊力) 
 int getDefense() { return defense; } //獲取法師防禦力 
 void beatMonster(int exp) //擊敗怪物獲取經驗值函式 
 {
  this->exp+=exp; //增加經驗值  
  while(this->exp >= pow(this->level, 2) * EXP_LV) //判斷是否可以升級
   this->levelUp(HP_LV, PO_LV, DE_LV, KN_LV, LU_LV); //升級角色 
 }
 
 void randomCout() // 定義訊息列表
 {
  vector<string> messages= 
  { 
   "我的毒沒有解藥~",
   "滑起來!",
   "阿跟不上我的速度吧阿嘎", 
  };
  srand(static_cast<unsigned int>(time(0))); //設定隨機種子
  int randomIndex = rand() % messages.size(); //從訊息列表中隨機選擇
  cout << messages[randomIndex] << endl;
 }
 
 void skill() //選擇技能函式 
 {
  cout<<"選擇技能: 1.提升自身攻擊力(攻擊力*1.2) 2.能量法術(2.5倍傷害)\n";
  cin>>skillChoice; //輸入選擇的技能 
  applyskill(skillChoice); //呼叫技能函式 
 }
 void applyskill(int choice) //技能函式 
 {
  switch(choice) 
  {
   case 1:
    cout<<"!!提升自身攻擊力!!\n";
    knowledge=static_cast<int>(knowledge * 1.2); //增加法師知識值(攻擊力) 
    break;
   case 2:
    cout<<"!!能量法術!!\n";
    targetMonster->setHP(targetMonster->getHP() - (2.5 * targetMonster->getAttack())); //對目標怪物造成傷害 
    randomCout(); //輸出隨機字元 
    this_thread::sleep_for(chrono::seconds(2)); //延遲2秒
    break;
   }
 }
};

class Team //隊伍類別 
{
 protected:
 vector<Character*> members; //隊伍成員 

 public:
 ~Team();
 void addTank(string name, int lv); //舔加坦克角色 
 void addWarrior(string name, int lv); //舔加戰士角色  
 void addWizard(string name, int lv); //舔加法師角色 
 void memberBeatMonster(string name, int exp); //成員擊敗怪物函式 
 void print(); //打印隊伍成員訊息 
 vector<Character*> getMembers() { return members; } //獲取隊伍成員 
 void combat(Monster* m); //戰鬥函數 
};

Team::~Team() {
  for(size_t i = 0; i < members.size(); ++i) 
  {
   delete members[i];
  }
}


void Team::addTank(string name, int lv) 
{
 if(members.size()<4) 
 {
  members.push_back(new Tank(name, lv)); //舔加坦克角色到隊伍 
 } 
 else 
 {
  cout<<"團隊已經滿了\n";
 }
}

void Team::addWarrior(string name, int lv) 
{
 if(members.size()<4) 
 {
  members.push_back(new Warrior(name, lv)); //舔加戰士角色到隊伍
 } 
 else 
 {
  cout<<"團隊已經滿了\n";
 }
}

void Team::addWizard(string name, int lv) 
{
 if(members.size()<4) 
 {
  members.push_back(new Wizard(name, lv)); //舔加法師角色到隊伍 
 } 
 else 
 {
  cout<<"團隊已經滿了\n";
 }
}

void Team::print() 
{
 for(size_t i = 0; i < members.size(); ++i) 
 {
  members[i]->print();
 }
}


class Game //遊戲邏輯 
{
 private:
 Team team;
 Monster* currentMonster;

 Monster* selectMonster() 
 {
  cout<< "選擇要攻打的目標:\n";
  cout<<"1. 鈔哥(LV25)\n";
  cout<<"2. 哥布林王(LV50)\n";
  cout<<"3. 古代石頭巨人(LV75)\n";
  cout<<"4. 巨龍(LV150 ~建議多人~)\n";
  int choice;
  cin>>choice;

  switch (choice) 
  {
   case 1: 
    return new Monster(2500, 400, 25); //選擇鈔哥
   case 2: 
    return new Monster(6000, 700, 50); //選擇哥布林王 
   case 3: 
    return new Monster(10000, 1000, 75); //選擇古代石頭巨人 
   case 4:
   	return new Monster(30000, 2000, 150); //選擇巨龍 
   default:
    cout<<"選擇無效，預設選擇鈔哥\n";
    return new Monster(2500, 400, 25); //預設選擇鈔哥 
   }
  }
  
  void WINrandomCout() // 定義訊息列表
  { 
   vector<string> messages= 
   {
    "恭喜您獲得獎勵 breakfast吃到飽!",
    "恭喜您獲得獎勵 超甲組吃到飽!",
    "恭喜您獲得獎勵 廖老大喝到飽!",
   };
   srand(static_cast<unsigned int>(time(0))); // 設定隨機種子
   int randomIndex = rand() % messages.size(); // 從訊息列表中隨機選擇
   cout<<messages[randomIndex]<<endl;
  } 
  
  void LOSErandomCout() // 定義訊息列表
  { 
   vector<string> messages= 
   {
    "為什麼 為什麼不幫我發大絕極靈!!!!!!",
    "這是一個不公平的比賽啊欸笑死人欸 他剛剛打我我有退嗎 我一步都沒有退欸 欸你們裁判是怎麼判的啊 欸不是 我一步都沒有退 然後判我輸喔 被我打到流鼻血的贏 有沒有邏輯啊不是啊 我把他打到噴鼻血 這樣算我輸喔他打我 我一步都沒有退ㄟ啊這樣算我輸喔 你們裁判怎麼判的啦 好啦 我要回家了啦",
   };
   srand(static_cast<unsigned int>(time(0))); // 設定隨機種子
   int randomIndex = rand() % messages.size(); // 從訊息列表中隨機選擇
   cout<<messages[randomIndex]<<endl;
  } 
  
  void battle() //戰鬥函式 
  {
   int round=1; //回合數 
   for(size_t i=0; i<team.getMembers().size(); i++) 
   {
    Character* member=team.getMembers()[i];
    Tank* tank=dynamic_cast<Tank*>(member);
    Warrior* warrior=dynamic_cast<Warrior*>(member);
    Wizard* wizard=dynamic_cast<Wizard*>(member);
    if(tank) tank->setTargetMonster(currentMonster);
    if(warrior) warrior->setTargetMonster(currentMonster);
    if(wizard) wizard->setTargetMonster(currentMonster);
   }
   while(true) 
   {
   	
    cout<<"第 "<<round<<" 回合\n";
    this_thread::sleep_for(chrono::seconds(1)); //延遲0秒
    if(round%5!=0)
    {
     for(size_t i=0; i<team.getMembers().size(); i++) 
     {
      Character* member=team.getMembers()[i];
      if(member->getHP()>0) 
      {
       int damage=member->getAttack();
       currentMonster->setHP(max(0, currentMonster->getHP() - damage));
       cout<<member->getName()<< " 對怪物造成 " << damage << " 傷害\n";
      }
     }
    }
    
    if(currentMonster->getHP() <= 0) 
    {  
     cout<<"勝利！\n";
     WINrandomCout();
     this_thread::sleep_for(chrono::seconds(2)); //延遲2秒
     currentMonster->print(); //打印怪物資料 
     team.print(); //打印隊伍成員資料 
     break;
    }

    if(round % 5 == 0) //每5回合使用技能
	{
	 cout<<"技能充能完畢。已可以使用技能，請問要使用嗎?(1.是 2.否=>使用普攻)\n";
     int use=0;
     cin>>use;
     if(use==1)
     {
      for(size_t i = 0; i < team.getMembers().size(); i++) 
	  {
       Character* member = team.getMembers()[i];
       if(member->getHP() > 0) 
	   {
        member->skill();
       }
      }
     } 
     else if(use==2) //執行普攻 
     {
      for(int i=0; i<team.getMembers().size(); i++) 
	  {
       Character* member=team.getMembers()[i];
       if(member->getHP()>0)
	   {
        int damage=member->getAttack();
        currentMonster->setHP(max(0, currentMonster->getHP() - damage));
        cout<<member->getName() << " 對怪物造成 " << damage << " 傷害\n";
       }
      } 
	 }
	 else 
	 {
      cout<<"選擇無效，所以使用技能!";
      for(int i=0; i<team.getMembers().size(); i++) 
	  {
       Character* member=team.getMembers()[i];
       if(member->getHP() > 0) 
	   {
        member->skill();
       }
      }
     }
    } 
    if(currentMonster->monsterAct) 
	{
     for(size_t i = 0; i < team.getMembers().size(); ++i) 
	 {
      Character* member = team.getMembers()[i];
      if(member->getHP() > 0) 
	  {
       int damage=max(0, currentMonster->getAttack() - member->getDefense());
       member->setHP(max(0, member->getHP() - damage));
       cout<<"怪物對 "<<member->getName()<<" 造成 "<<damage<<" 傷害\n";
       
      }
     }
    } 

    bool allDead=true;
    for (size_t i = 0; i < team.getMembers().size(); ++i) {
            Character* member = team.getMembers()[i];
            if (member->getHP() > 0) {
                allDead = false;
                break;
            }
        }
    if(allDead) 
	{
     cout<<"失敗！ (ˉ▽ˉ；)...\n";
     LOSErandomCout();
     this_thread::sleep_for(chrono::seconds(2)); //延遲2秒
     currentMonster->print(); //打印怪物資料 
     break;
    }

    cout<<"<怪物血量> "<<currentMonster->getHP()<<" <角色狀態>\n";
    team.print(); //打印隊伍成員資料 

    round++; //進入下一回合 
   }
  }

 public:
 void start() 
 {
  cout<< "歡迎來到RPG遊戲╰(*°▽°*)╯\n";
  cout<<"!!!!!!!!!!!!!!!!!!!!!!\n!!!團隊最多四人遊玩!!!\n!!!!!!!!!!!!!!!!!!!!!!\n";
  while(team.getMembers().size() < 4) //當隊伍成員少於4個時循環 
  {
   cout<<"輸入角色名字: (若不添加角色則填0)";
   string name;
   cin>>name;
   if(name=="0")
   {
    break;
   }
            
   cout<<"選擇角色:\n1. 坦克\n2. 戰士\n3. 法師\n";
   int choice;
   cin>>choice;
   cout<<"輸入等級: ";
   int level;
   cin>>level;

   switch(choice) 
   {
    case 1: team.addTank(name, level); break; //舔加坦克角色 
    case 2: team.addWarrior(name, level); break; //舔加戰士角色 
    case 3: team.addWizard(name, level); break; //舔加法師角色 
    default:
     cout<<"選擇無效，預設為戰士\n";
     team.addWarrior(name, level); //預設舔加戰士角色 
     break;
   }
  }
  while(true) //主遊戲循環 
  {
   currentMonster=selectMonster(); //選擇怪物 
   battle(); //進行戰鬥 
   

   cout<<"是否開始下一場戰鬥？(1.是 2.否): ";
   int choice;
   cin>>choice;
   if(choice != 1) 
   {
    cout<<"遊戲結束！(￣ 3￣)\n";
    break;
   }
  }
 }
};

int main() 
{
 Game game;
 game.start();
 return 0;
}
