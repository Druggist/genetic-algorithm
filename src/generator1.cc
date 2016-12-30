#include "generator1.h"

void Instance::generate_instance(int quantity, int max_time, bool verbose){
  srand(time(NULL));
  int t1_1, t1_2, rt, mt, opt;
  Task t;
  for (int i = 0; i < quantity; i++){
    t1_1 = rand() % max_time+1;
    t1_2 = rand() % max_time+1;
    if ( i < quantity/2 ){
      rt = 0;
    }
    else{
      rt = rand() % ((max_time*(quantity/4))+1);
    }
    t.set_op_time(1, t1_1);
    t.set_op_time(2, t1_2);
    t.set_rt(rt);
    task_v.push_back(t);
    //debug only:
    if (verbose == true){
     std::cout << t1_1 << ";" << t1_2 << ";" << 1 << ";" << 2 << ";" << rt << endl;
    }
  }
  Maitenance m;
  for (int i = 0; i < quantity/5; i++){
    mt = rand() % (max_time /2 ) + 1;
    opt = mt + max_time * i;
    m.set_mt(mt);
    m.set_opt(opt);
    m.set_id(i);
    maitenance_v.push_back(m);
  }
}

void Instance::dump_instance(string filename){
  fstream file;
  file.open(filename.c_str());
  if (file.good() == true){
    file << "****" << id << "****/n";
    file << tasks_number << endl;
    for(vector<int>::size_type i = 0; i < task_v.size(); i++){
      file << task_v[i].get_op_time(1) << ";" << task_v[i].get_op_time(2) << ";" << "1" <<";" << "2" << ";" << task_v[i].get_rt() << ";" << endl;
    }
    for (vector<int>::size_type i = 0; i < maitenance_v.size(); i++){
      file << maitenance_v[i].get_id() << ";" << maitenance_v[i].get_opt() << ";" << maitenance_v[i].get_mt() << ";" << endl;
    }
  }
  else{
    cerr<<"Cannot open and write to instance file!\n";
    exit(-1);
  }
}

void Instance::read_instance(string filename){
  fstream file;
  string s;
  int quantity, tmp;
  Task t;
  Maitenance m;
  file.open(filename.c_str());
  if(file.good() == true){
    getline(file, s);
    getline(file, s);
      quantity = atoi(s.c_str());
      for (int i = 0; i < quantity; i++){
        getline(file, s, ';');
        tmp = atoi(s.c_str());
        t.set_op_time(1, tmp);
        getline(file, s, ';');
        tmp = atoi(s.c_str());
        t.set_op_time(2,tmp);
        getline(file, s, ';'); //ignoring two lines
        getline(file, s, ';');
        getline(file, s, ';');
        tmp = atoi(s.c_str());
        t.set_rt(tmp);
        task_v.push_back(t);
      }
    
    while(!file.eof()){
      getline(file, s, ';');
      tmp = atoi(s.c_str());
      m.set_id(tmp);
      getline(file, s, ';'); // ignoring machine number
      getline(file, s, ';');
      tmp = atoi(s.c_str());
      m.set_opt(tmp);
      getline(file, s, ';');
      tmp = atoi(s.c_str());
      m.set_mt(tmp);
    }

  }
  else{
    cerr <<"Cannot open and read instance file!\n";
    exit(-1);
  }
}

void Instance::clear_task_v(){
  task_v.clear();
}

void Instance::clear_maitenance_v(){
  maitenance_v.clear();
}
