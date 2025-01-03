#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread> //�Ω󩵿�
#include <chrono> //�Ω���w�ɶ�

using namespace std;


class Character //���⪺�U���ƭ� 
{
 protected:
 static const int EXP_LV=100; //����ɯũһݪ��ͩR�� 
 string name; //����W�� 
 int hp; //�����q 
 int level; //���ⵥ�� 
 int exp; //����g��� 
 int power; //��������O 
 int defense; //���⨾�m�O
 int knowledge; //���⪾�ѭ� 
 int luck; //���⩯�B�� 
 int skillChoice=0; //�ޯ��� 

 void levelUp(int hInc, int pInc, int dInc, int kInc, int lInc); //����ɯŨ�� 

public:
 Character(string n, int lv, int h, int po, int de, int kn, int lu); //����غc��� 
 virtual void print(); //���L����T�� ������� 
 virtual void beatMonster(int exp) = 0; //�������ѩǪ���o�g��� ������� 
 virtual void setHP(int) = 0; //�����q��� ������� 
 virtual int getHP() = 0; //��������q ������� 
 virtual int getAttack() = 0; //�����������O ������� 
 virtual int getDefense() = 0; //������⨾�m�O ������� 
 virtual void skill() = 0; //����ޯ� ������� 
 virtual void applyskill(int a) = 0; //���Χޯ�ĪG ������� 
 string getName(); //�������W�� 
};

Character::Character(string n, int lv, int h, int po, int de, int kn, int lu) //��l�� 
    : name(n), level(lv), exp(pow(lv - 1, 2) * EXP_LV), hp(h), power(po), defense(de), knowledge(kn), luck(lu) {}

string Character::getName() 
{
 return this->name; //�Ǧ^����W�� 
}

void Character::levelUp(int hInc, int pInc, int dInc, int kInc, int lInc) //����ɯŨ�� 
{
 this->level++; //���ⵥ�Ŵ��� 
 this->hp+=hInc; //�W�[�����q 
 this->power+=pInc; //�W�[��������O 
 this->defense+=dInc; //�W�[���⨾�m�O  
 this->knowledge+=kInc; //�W�[���⪾�ѭ� 
 this->luck+=lInc; //�W�[���⩯�B�� 
}

void Character::print() 
{
 cout<<this->name <<": Lv"<<this->level; //���L����W�١B����
 cout<<"-HP"<<max(0,this->hp)<<"-Pow"<<this->power<<"-Def"<<this->defense<<"-Kno"<<this->knowledge<<"-Luck"<<this->luck<<"\n"; //���L�����q�B�����O�B���m�O�B���ѭȡB���B��
}


class Monster : public Character //�Ǫ����O
{
 public:
 bool monsterAct; // �O���Ǫ��O�_����
 Monster(int h, int po, int kn) : Character("", 0, h, po, 0, kn, 0) { monsterAct = true; } //��l�ƩǪ� 
 void print() { cout << "Monster "; Character::print(); } //���L�Ǫ��T�� 
 int getHP() { return hp; } //����Ǫ���q 
 void setHP(int hp) { this->hp = hp; } //�]�w�Ǫ���q 
 int getAttack() { return power; } //����Ǫ����m�O 
 int getDefense() { return 0; } //�Ǫ��S�����m�O
 void beatMonster(int exp) {} //�B�z�Ǫ����Ѩƥ� 
 void skill() {}; //�B�z�Ǫ��ޯ� 
 void applyskill(int skillChoice) {}; //�Ǫ����Χޯ�ĪG 
};

class Tank : public Character //�Z�J���O
{
 private:
 static const int HP_LV=100; //�w�q�ɯŮɦ�q�W�q  
 static const int PO_LV=8; //�w�q�ɯŮɧ����O�W�q  
 static const int DE_LV=12; //�w�q�ɯŮɨ��m�O�W�q  
 static const int KN_LV=5; //�w�q�ɯŮɪ��ѭȼW�q  
 static const int LU_LV=5; //�w�q�ɯŮɩ��B�ȼW�q  
 Monster* targetMonster;

 public:
 void setTargetMonster(Monster* monster) 
 {
  targetMonster=monster;
 }
 Tank(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * DE_LV, lv * KN_LV, lv * LU_LV), targetMonster(NULL) {}
 void print() { cout << "Tank "; Character::print(); } //���L�Z�J����T�� 
 int getHP() { return hp; } //����Z�J��q 
 void setHP(int hp) { this->hp = hp; } //�]�w�Z�J��q 
 int getAttack() { return power; } //����Z�J�����O 
 int getDefense() { return defense; } //����Z�J���m�O 
 void beatMonster(int exp) //���ѩǪ�����g��Ȩ禡 
 {
  this->exp+=exp; //�W�[�g��� 
  while(this->exp >= pow(this->level, 2) * EXP_LV) //�P�_�O�_�i�H�ɯ� 
   this->levelUp(HP_LV, PO_LV, DE_LV, KN_LV, LU_LV); //�ɯŨ��� 
 }
 
 void randomCout() //�w�q�T���C��
 {
  vector<string> messages= 
  { 
   "AAAAAA�紵�@���G �紵�@���T!",
   "RRR�Ѫ���_��!",
   "�����}���o!",
   "�A�ݨ�ڥ��l�F�紵�����|�Ȫ��� �ٴ��b����~�L��",
  };
  srand(static_cast<unsigned int>(time(0))); // �]�w�H���ؤl
  int randomIndex = rand() % messages.size(); // �q�T���C���H�����
  cout<<messages[randomIndex]<<endl;
 }
 
 void skill() //��ܧޯ�禡 
 {
  cout<<"��ܧޯ�: 1.����(1.2���ˮ`) 2.���ɦۨ����m�O(+50)\n";
  cin>>skillChoice; //��J��ܪ��ޯ� 
  applyskill(skillChoice); //�I�s�ޯ�禡 
 }
 void applyskill(int choice) //�ޯ�禡 
 {
  switch(choice) 
  {
   case 1:
   	{
   	 cout<<"!!�ϥX����!!\n";
     targetMonster->setHP(targetMonster->getHP() - (1.2 * targetMonster->getAttack())); // ��ؼЩǪ��y���ˮ` 
     randomCout(); //��X�H���r�� 
     this_thread::sleep_for(chrono::seconds(2)); //����2��
     break;
    }
   case 2:
    cout<<"!!���ɨ��m�O!!\n";
    defense += 50; //�W�[���m�O 
    break;
    }
 }
};

class Warrior : public Character //�Ԥh���O
{
 private:
 static const int HP_LV=100; //�w�q�ɯŮɦ�q�W�q
 static const int PO_LV=10; //�w�q�ɯŮɧ����O�W�q
 static const int DE_LV=9; //�w�q�ɯŮɨ��m�O�W�q
 static const int KN_LV=5; //�w�q�ɯŮɪ��ѭȼW�q
 static const int LU_LV=5; //�w�q�ɯŮɩ��B�ȼW�q
 Monster* targetMonster;

 public:
 void setTargetMonster(Monster* monster) 
 {
  targetMonster=monster;
 }
 Warrior(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * DE_LV, lv * KN_LV, lv * LU_LV) {} //��l�ƾԤh����
 void print() { cout << "Warrior "; Character::print(); } //���L�Ԥh����T�� 
 int getHP() { return hp; } //����Ԥh��q 
 void setHP(int hp) { this->hp = hp; } //�]�w�Ԥh��q 
 int getAttack() { return power; } //����Ԥh�����O 
 int getDefense() { return defense; } //����Ԥh���m�O  
 void beatMonster(int exp) //���ѩǪ�����g��Ȩ禡
 {
  this->exp+=exp; //�W�[�g��� 
  while(this->exp >= pow(this->level, 2) * EXP_LV) //�P�_�O�_�i�H�ɯ� 
  this->levelUp(HP_LV, PO_LV, DE_LV, KN_LV, LU_LV); //�ɯŨ��� 
 }
 
 void randomCout() // �w�q�T���C��
 {
  vector<string> messages= 
  { 
   "�o����쩳����{�{����������",
   "�ٴ��U�ӰڦB��!",
   "!AAA�L�ӺO!",
   "!�ӯ���!", 
  };
  srand(static_cast<unsigned int>(time(0))); // �]�w�H���ؤl
  int randomIndex = rand() % messages.size(); // �q�T���C���H�����
  cout<<messages[randomIndex]<<endl;
 }
 
 void skill() //��ܧޯ�禡 
 {
  cout<<"��ܧޯ�: 1.��������(2���ˮ`) 2.���ɦۨ������O(+50)\n";
  cin>>skillChoice; //��J��ܪ��ޯ�  
  applyskill(skillChoice); //�I�s�ޯ�禡 
 }
 void applyskill(int choice) //�ޯ�禡
 {
  switch(choice) 
  {
   case 1:
    cout<<"!!��������!!\n";
    targetMonster->setHP(targetMonster->getHP() - (2 * targetMonster->getAttack())); //��ؼЩǪ��y���ˮ`
	randomCout(); //��X�H���r�� 
	this_thread::sleep_for(chrono::seconds(2)); //����2�� 
    break;
   case 2:
    cout<<"!!���ɧ����O!!\n";
    power+=50; //�W�[�����O 
    break;
   }
 }
};

class Wizard : public Character //�k�v���O 
{
 private:
 static const int HP_LV = 80; //�w�q�ɯŮɦ�q�W�q 
 static const int PO_LV = 4;  //�w�q�ɯŮɧ����O�W�q 
 static const int DE_LV = 5; //�w�q�ɯŮɨ��m�O�W�q
 static const int KN_LV = 15; //�w�q�ɯŮɪ��ѭȼW�q 
 static const int LU_LV = 7; //�w�q�ɯŮɩ��B�ȼW�q 
 Monster* targetMonster;
 
 public:
 void setTargetMonster(Monster* monster) 
 {
  targetMonster=monster;
 }
 Wizard(string n, int lv = 1) : Character(n, lv, lv * HP_LV, lv * PO_LV, lv * DE_LV, lv * KN_LV, lv * LU_LV) {} //��l�ƪk�v���� 
 void print() { cout << "Wizard "; Character::print(); } //���L�k�v����T�� 
 int getHP() { return hp; } //����k�v��q 
 void setHP(int hp) { this->hp = hp; } //�]�w�k�v��q 
 int getAttack() { return knowledge; } //����k�v���ѭ�(�@�������O) 
 int getDefense() { return defense; } //����k�v���m�O 
 void beatMonster(int exp) //���ѩǪ�����g��Ȩ禡 
 {
  this->exp+=exp; //�W�[�g���  
  while(this->exp >= pow(this->level, 2) * EXP_LV) //�P�_�O�_�i�H�ɯ�
   this->levelUp(HP_LV, PO_LV, DE_LV, KN_LV, LU_LV); //�ɯŨ��� 
 }
 
 void randomCout() // �w�q�T���C��
 {
  vector<string> messages= 
  { 
   "�ڪ��r�S������~",
   "�ư_��!",
   "���򤣤W�ڪ��t�קa����", 
  };
  srand(static_cast<unsigned int>(time(0))); //�]�w�H���ؤl
  int randomIndex = rand() % messages.size(); //�q�T���C���H�����
  cout << messages[randomIndex] << endl;
 }
 
 void skill() //��ܧޯ�禡 
 {
  cout<<"��ܧޯ�: 1.���ɦۨ������O(�����O*1.2) 2.��q�k�N(2.5���ˮ`)\n";
  cin>>skillChoice; //��J��ܪ��ޯ� 
  applyskill(skillChoice); //�I�s�ޯ�禡 
 }
 void applyskill(int choice) //�ޯ�禡 
 {
  switch(choice) 
  {
   case 1:
    cout<<"!!���ɦۨ������O!!\n";
    knowledge=static_cast<int>(knowledge * 1.2); //�W�[�k�v���ѭ�(�����O) 
    break;
   case 2:
    cout<<"!!��q�k�N!!\n";
    targetMonster->setHP(targetMonster->getHP() - (2.5 * targetMonster->getAttack())); //��ؼЩǪ��y���ˮ` 
    randomCout(); //��X�H���r�� 
    this_thread::sleep_for(chrono::seconds(2)); //����2��
    break;
   }
 }
};

class Team //�������O 
{
 protected:
 vector<Character*> members; //����� 

 public:
 ~Team();
 void addTank(string name, int lv); //�Q�[�Z�J���� 
 void addWarrior(string name, int lv); //�Q�[�Ԥh����  
 void addWizard(string name, int lv); //�Q�[�k�v���� 
 void memberBeatMonster(string name, int exp); //�������ѩǪ��禡 
 void print(); //���L������T�� 
 vector<Character*> getMembers() { return members; } //�������� 
 void combat(Monster* m); //�԰���� 
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
  members.push_back(new Tank(name, lv)); //�Q�[�Z�J����춤�� 
 } 
 else 
 {
  cout<<"�ζ��w�g���F\n";
 }
}

void Team::addWarrior(string name, int lv) 
{
 if(members.size()<4) 
 {
  members.push_back(new Warrior(name, lv)); //�Q�[�Ԥh����춤��
 } 
 else 
 {
  cout<<"�ζ��w�g���F\n";
 }
}

void Team::addWizard(string name, int lv) 
{
 if(members.size()<4) 
 {
  members.push_back(new Wizard(name, lv)); //�Q�[�k�v����춤�� 
 } 
 else 
 {
  cout<<"�ζ��w�g���F\n";
 }
}

void Team::print() 
{
 for(size_t i = 0; i < members.size(); ++i) 
 {
  members[i]->print();
 }
}


class Game //�C���޿� 
{
 private:
 Team team;
 Monster* currentMonster;

 Monster* selectMonster() 
 {
  cout<< "��ܭn�𥴪��ؼ�:\n";
  cout<<"1. �r��(LV25)\n";
  cout<<"2. �����L��(LV50)\n";
  cout<<"3. �j�N���Y���H(LV75)\n";
  cout<<"4. ���s(LV150 ~��ĳ�h�H~)\n";
  int choice;
  cin>>choice;

  switch (choice) 
  {
   case 1: 
    return new Monster(2500, 400, 25); //��ܶr��
   case 2: 
    return new Monster(6000, 700, 50); //��ܭ����L�� 
   case 3: 
    return new Monster(10000, 1000, 75); //��ܥj�N���Y���H 
   case 4:
   	return new Monster(30000, 2000, 150); //��ܥ��s 
   default:
    cout<<"��ܵL�ġA�w�]��ܶr��\n";
    return new Monster(2500, 400, 25); //�w�]��ܶr�� 
   }
  }
  
  void WINrandomCout() // �w�q�T���C��
  { 
   vector<string> messages= 
   {
    "���߱z��o���y breakfast�Y�칡!",
    "���߱z��o���y �W�ҲզY�칡!",
    "���߱z��o���y ���Ѥj�ܨ칡!",
   };
   srand(static_cast<unsigned int>(time(0))); // �]�w�H���ؤl
   int randomIndex = rand() % messages.size(); // �q�T���C���H�����
   cout<<messages[randomIndex]<<endl;
  } 
  
  void LOSErandomCout() // �w�q�T���C��
  { 
   vector<string> messages= 
   {
    "������ ���������ڵo�j�����F!!!!!!",
    "�o�O�@�Ӥ����������ɰ��ٯ����H�� �L��襴�ڧڦ��h�� �ڤ@�B���S���h�� �٧A�̵��P�O���P���� �٤��O �ڤ@�B���S���h �M��P�ڿ�� �Q�ڥ���y��媺Ĺ ���S���޿�ڤ��O�� �ڧ�L����Q��� �o�˺�ڿ��L���� �ڤ@�B���S���h���ڳo�˺�ڿ�� �A�̵��P���P���� �n�� �ڭn�^�a�F��",
   };
   srand(static_cast<unsigned int>(time(0))); // �]�w�H���ؤl
   int randomIndex = rand() % messages.size(); // �q�T���C���H�����
   cout<<messages[randomIndex]<<endl;
  } 
  
  void battle() //�԰��禡 
  {
   int round=1; //�^�X�� 
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
   	
    cout<<"�� "<<round<<" �^�X\n";
    this_thread::sleep_for(chrono::seconds(1)); //����0��
    if(round%5!=0)
    {
     for(size_t i=0; i<team.getMembers().size(); i++) 
     {
      Character* member=team.getMembers()[i];
      if(member->getHP()>0) 
      {
       int damage=member->getAttack();
       currentMonster->setHP(max(0, currentMonster->getHP() - damage));
       cout<<member->getName()<< " ��Ǫ��y�� " << damage << " �ˮ`\n";
      }
     }
    }
    
    if(currentMonster->getHP() <= 0) 
    {  
     cout<<"�ӧQ�I\n";
     WINrandomCout();
     this_thread::sleep_for(chrono::seconds(2)); //����2��
     currentMonster->print(); //���L�Ǫ���� 
     team.print(); //���L�������� 
     break;
    }

    if(round % 5 == 0) //�C5�^�X�ϥΧޯ�
	{
	 cout<<"�ޯ�R�৹���C�w�i�H�ϥΧޯ�A�аݭn�ϥζ�?(1.�O 2.�_=>�ϥδ���)\n";
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
     else if(use==2) //���洶�� 
     {
      for(int i=0; i<team.getMembers().size(); i++) 
	  {
       Character* member=team.getMembers()[i];
       if(member->getHP()>0)
	   {
        int damage=member->getAttack();
        currentMonster->setHP(max(0, currentMonster->getHP() - damage));
        cout<<member->getName() << " ��Ǫ��y�� " << damage << " �ˮ`\n";
       }
      } 
	 }
	 else 
	 {
      cout<<"��ܵL�ġA�ҥH�ϥΧޯ�!";
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
       cout<<"�Ǫ��� "<<member->getName()<<" �y�� "<<damage<<" �ˮ`\n";
       
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
     cout<<"���ѡI (�������F)...\n";
     LOSErandomCout();
     this_thread::sleep_for(chrono::seconds(2)); //����2��
     currentMonster->print(); //���L�Ǫ���� 
     break;
    }

    cout<<"<�Ǫ���q> "<<currentMonster->getHP()<<" <���⪬�A>\n";
    team.print(); //���L�������� 

    round++; //�i�J�U�@�^�X 
   }
  }

 public:
 void start() 
 {
  cout<< "�w��Ө�RPG�C����(*�X���X*)��\n";
  cout<<"!!!!!!!!!!!!!!!!!!!!!!\n!!!�ζ��̦h�|�H�C��!!!\n!!!!!!!!!!!!!!!!!!!!!!\n";
  while(team.getMembers().size() < 4) //������֩�4�Ӯɴ`�� 
  {
   cout<<"��J����W�r: (�Y���K�[����h��0)";
   string name;
   cin>>name;
   if(name=="0")
   {
    break;
   }
            
   cout<<"��ܨ���:\n1. �Z�J\n2. �Ԥh\n3. �k�v\n";
   int choice;
   cin>>choice;
   cout<<"��J����: ";
   int level;
   cin>>level;

   switch(choice) 
   {
    case 1: team.addTank(name, level); break; //�Q�[�Z�J���� 
    case 2: team.addWarrior(name, level); break; //�Q�[�Ԥh���� 
    case 3: team.addWizard(name, level); break; //�Q�[�k�v���� 
    default:
     cout<<"��ܵL�ġA�w�]���Ԥh\n";
     team.addWarrior(name, level); //�w�]�Q�[�Ԥh���� 
     break;
   }
  }
  while(true) //�D�C���`�� 
  {
   currentMonster=selectMonster(); //��ܩǪ� 
   battle(); //�i��԰� 
   

   cout<<"�O�_�}�l�U�@���԰��H(1.�O 2.�_): ";
   int choice;
   cin>>choice;
   if(choice != 1) 
   {
    cout<<"�C�������I(�� 3��)\n";
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
