#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>

using std::cout;
using std::cin;
using std::getline;
using std::string;
using std::fstream;
using std::vector;


struct Task{
  int id;
  int op1_time;
  int op2_time;
  int rt;
  int get_id();
  int get_rt();
  int get_op_time(int);
  void set_op_time(int, int);
  void set_rt(int);
};
int Task::get_id(){
  return id;
}
int Task::get_rt(){
  return rt;
}
int Task::get_op_time(int i){
  if (i == 1){
    return op1_time;
  }
  if (i == 2){
    return op2_time;
  }
  else{
    return -1;
  }
}
void Task::set_rt(int i){
  rt = i;
}
void Task::set_op_time(int o, int t){
  if (o == 1){
    op1_time = t;
  }
  else if (o == 2){
    op2_time = t;
  }
  else{
    exit(1);
  }
}

class Task_t : private Task{
  bool punished;
  int punishment; //summary punishment time
  int op_stime; //start time
public:
  Task_t(int);
  bool if_punished();
  int punish_time();
  void punishit(int);
  void punish();
  int startt();
  int get_id();
  int get_rt();
  int get_punish();
  void set_op_stime(int);
};

Task_t::Task_t(int i){
  punished = false;
  punishment = 0;
  id = i;
}
int Task_t::get_id(){
  return id;
}
bool Task_t::if_punished(){
  return punished;
}
int Task_t::get_punish(){
  return punishment;
}
int Task_t::punish_time(){
  return punishment;
}

void Task_t::punishit(int p){
  punished = true;
  punishment = p;
}
void Task_t::punish(){
  punishment++;
}
int Task_t::get_rt(){
  return rt;
}
int Task_t::startt(){
  return op_stime;
}
void Task_t::set_op_stime(int k){
  op_stime = k;
}
class Maitenance{
  int id;
  int m_time; //start time
  int op_time; //duration
public:
  Maitenance(int, int, int);
  int get_mt();
  int get_opt();
  int get_id();
};

Maitenance::Maitenance(int i, int m_t, int stime){
  m_time = m_t;
  op_time = stime;
  id = i;
}

int Maitenance::get_mt(){
  return m_time;
}
int Maitenance::get_id(){
  return id;
}
int Maitenance::get_opt(){
  return op_time;
}
vector <Task> task_v;
vector <Maitenance> maitenance_v;
class Machine{
  int id;
  int startt;
  int stopt;
public:
  vector <Task_t> mtasks_v;
  void set_id(int);
  void set_start(int);
  void set_stop(int);
  bool add(int);
  int get_id();
  int get_srt();
  int get_sop();
  void addt(int, int);
};

void Machine::set_id(int i){
  id = i;
}
void Machine::set_start(int i){
  stopt = i;
}
void Machine::set_stop(int i){
  startt = i;
}
int Machine::get_id(){
  return id;
}
int Machine::get_srt(){
  return startt;
}
int Machine::get_sop(){
  return stopt;
}
bool Machine::add(int task_id){
  if (id == 1){ //machine 1
    Task_t new_task(task_v[task_id].get_id());
    for (vector<Maitenance>::size_type i = 0; i < maitenance_v.size() ; i++ ){
      if (stopt == maitenance_v[i].get_mt()){
        stopt += maitenance_v[i].get_opt();
        new_task.set_op_stime(stopt);     
      }
    }
    if (stopt < task_v[task_id].get_rt()){
      return false;
    }
    for(vector<Maitenance>::size_type i = 0; i < maitenance_v.size(); i++){
      if(stopt < maitenance_v[i].get_mt() &&
          (stopt + task_v[task_id].get_op_time(1))>maitenance_v[i].get_mt()){
        new_task.punishit(task_v[i].get_op_time(1));
        if(task_v[i].get_op_time(1) % 5 == 0){
          new_task.punish();
        }
        new_task.set_op_stime(stopt);
        stopt += maitenance_v[i].get_opt();
      }
    }
    mtasks_v.push_back(new_task);
    stopt += task_v[task_id].get_op_time(1)+new_task.get_punish();
  }
  else{ // machine 2
    Task_t new_task(task_v[task_id].get_id());
    new_task.set_op_stime(stopt);
    mtasks_v.push_back(new_task);
    stopt += task_v[task_id].get_op_time(2);
  }
  return true;

}

void Machine::addt(int t, int task_id){
  if (id == 2){
    Task_t new_task(task_v[task_id].get_id());
    new_task.set_op_stime(stopt);
    mtasks_v.push_back(new_task);
    stopt += t + task_v[task_id].get_op_time(2);
  }
}

class Order{
  vector<int> ord;
  int exec_t;
public: 
  Machine machine1;
  Machine machine2;
  void initialization(vector<int>);
};
void Order::initialization(vector<int> O){
  machine1.set_id(1);
  machine1.set_start(0);
  machine1.set_stop(0);
  machine2.set_id(2);
  int n, tmp;
  for (vector<int>::size_type i = 0; i < O.size(); i++){
    //Machine 1
    n = 1;
    while(!machine1.add(O[i])){
      tmp = O[i];
      O[i] = O[i + n];
      O[i + n] = tmp;
      n++;
    }
    // Machine 2
    if( i == 0 ){
      machine2.set_start(machine1.get_sop());
      machine2.set_stop(machine1.get_sop());
    }
    if(machine1.get_sop() <= machine2.get_sop()){
      machine2.add(O[i]);
    }
    else{
      machine2.addt(machine1.get_sop(), O[i]);
    }
  }

}

int main(int argc, char* argv[]){
  string inputFN, outputFN;
  fstream inputF, outputF;
  if (argc < 3){
    cout<<"Usage: "<<argv[0]<<" inputfile outputfile";
    return 1;
  }
  inputFN = string(argv[1]);
  outputFN = string(argv[2]);
  int e_number;
  inputF.open(inputFN);
  outputF.open(outputFN);
  if( inputF ){
    inputF >> e_number;
    string tmp = "";
    string tmp1, tmp2, tmp3;
    for(int i = 0; i < e_number; i++){
      Task t;
      t.id = i;
      inputF >> tmp;
      tmp = tmp.substr(0, tmp.length() -1);
      t.set_op_time(1, atoi(tmp.c_str()));

      inputF >> tmp >> tmp;
      tmp = tmp.substr(0, tmp.length()-1);
      t.set_op_time(2, atoi(tmp.c_str()));

      inputF >> tmp >>tmp >>tmp;
      tmp = tmp.substr(0, tmp.length()-1);
      t.set_rt(atoi(tmp.c_str()));

      task_v.push_back(t);
    }
    while (inputF >> tmp){
      inputF>>tmp1;
      inputF>>tmp2 >> tmp2;
      inputF>>tmp3 >>tmp3 >>tmp3;
      Maitenance m(atoi(tmp1.substr(0, tmp1.length()-1).c_str()),atoi(tmp2.substr(0, tmp2.length()-1).c_str()),atoi(tmp3.substr(0, tmp3.length()-1).c_str())) ;
      maitenance_v.push_back(m);
    }
    inputF.close();
  }
  else{
    cout<<"Got some error during opening the file\n";
    return 1;
  }
  
  for(vector<Task>::size_type i = 0; i < task_v.size(); i++){
    cout << task_v[i].get_id() <<";" << task_v[i].get_op_time(1) << ";" << task_v[i].get_op_time(2)<<";"<<task_v[i].get_rt()<<std::endl;
  }
  for(vector<Maitenance>::size_type i = 0; i < maitenance_v.size(); i++){
    cout<<maitenance_v[i].get_id() <<";" << maitenance_v[i].get_mt() << maitenance_v[i].get_opt()<<std::endl; 
  }

  //Scheduling
  cout<<"Scheduling:\n";
  vector <int> s;
  for(int i = 0; i < e_number; i++){
    s.push_back(i);
  }
  int m = 2000;
  int temp = 0;
  vector <Order> orders;
  for(int i = 0; i < 10; i++){
    random_shuffle(s.begin(), s.end());
    Order ord;
    ord.initialization(s);
    orders.push_back(ord);
    if(ord.machine2.get_sop() < m){
      m = ord.machine2.get_sop();
      temp = i;
    }
    cout<< "schedule " << i << std::endl <<"\t" << ord.machine2.get_sop() << std::endl;
  }
  cout << temp << " " << m << std::endl;

  return 0;
}
