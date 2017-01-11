#include "instance.h"

/*void Instance::set_id(int i){
	id = i;
}

void Instance::set_task_number(int t){
	tasks_number = t;
}*/

Instance::Instance(){
	srand(time(NULL));
}

void Instance::generate_instance(int quantity, int max_time, int identifier, bool verbose){
	clear_all();
	this->id = identifier;
	this->tasks_number = quantity;
	int t1_1, t1_2, rt, mt, opt;
	for (int i = 0; i < quantity; i++){
		Task t(task_v.size());
		t1_1 = rand() % max_time+1;
		t1_2 = rand() % max_time+1;
		if ( i < quantity/2 ){
			rt = 0;
		}else{
			rt = rand() % ((max_time*(quantity/4))+1);
		}
		t.set_op_t(1, t1_1);
		t.set_op_t(2, t1_2);
		t.set_ready_t(rt);
		task_v.push_back(t);
		//debug only:
		if (verbose == true){
		 std::cout << t1_1 << ";" << t1_2 << ";" << 1 << ";" << 2 << ";" << rt <<';'<< endl;
		}
	}
	if (verbose == true){
		std::cout << "---------------------------------------------------------------------------\n";
	}
	for (int i = 0; i < quantity/5; i++){
		Maitenance m(i);
		mt = rand() % (max_time /2 ) + 1;
		opt = mt + max_time * i;
		m.set_start_t(mt);
		m.set_duration(opt);
		if (verbose == true){
			std::cout << i << ';' << 1 << ';' << opt << ';' << mt << ';' << endl;
		}
		maitenance_v.push_back(m);
	}
}

void Instance::dump_instance(string filename){
	ofstream file(filename.c_str());
	//file.open(filename.c_str());
	if (file.good() == true){
		file << "****" << id << "****\n";
		file << tasks_number << endl;
		for(vector<int>::size_type i = 0; i < task_v.size(); i++){
			file << task_v[i].get_op_t(1) << ";" << task_v[i].get_op_t(2) << ";" << "1" <<";" << "2" << ";" << task_v[i].get_ready_t() << ";" << endl;
		}
		for (vector<int>::size_type i = 0; i < maitenance_v.size(); i++){
			file << maitenance_v[i].get_id() <<';' << 1 << ";" << maitenance_v[i].get_start_t() << ";" << maitenance_v[i].get_duration() << ";" <<  endl;
		}
	}
	else{
		cerr<<"Cannot open and write to instance file!\n";
		exit(-1);
	}
	file.close();
	clear_all();
}

void Instance::read_instance(string filename){
	string s;
	int quantity, tmp;
	fstream file;
	file.open(filename.c_str());
	if(file.good() == true){
		getline(file, s); //ignoring one line
		getline(file, s);
			quantity = atoi(s.c_str());
			std::cout << quantity << endl;
			for (int i = 0; i < quantity; i++){
				Task t(i);
				getline(file, s, ';');
				tmp = atoi(s.c_str());
				t.set_op_t(1, tmp);
				getline(file, s, ';');
				tmp = atoi(s.c_str());
				t.set_op_t(2,tmp);
				getline(file, s, ';'); //ignoring two lines
				getline(file, s, ';');
				getline(file, s, ';');
				tmp = atoi(s.c_str());
				t.set_ready_t(tmp);
				task_v.push_back(t);
				//std::cout << t.get_op_time(1) << ";" << t.get_op_time(2) << ";" << "1" <<";" << "2" << ";" << t.get_rt() << ";" << endl;
			}

		for(int i = 0; i < quantity/5; i++){
			getline(file, s, ';');
			tmp = atoi(s.c_str());
			Maitenance m(tmp);
			getline(file, s, ';'); // ignoring machine number
			getline(file, s, ';');
			tmp = atoi(s.c_str());
			m.set_duration(tmp);
			getline(file, s, ';');
			tmp = atoi(s.c_str());
			m.set_start_t(tmp);
			maitenance_v.push_back(m);
			//std::cout <<  m.get_id() << ";" << m.get_opt() << ";" << m.get_mt() << ";" << endl;
		}

	}
	else{
		cerr <<"Cannot open and read instance file!\n";
		exit(-1);
	}
	file.close();
}

void Instance::clear_task_v(){
	task_v.clear();
}

void Instance::clear_maitenance_v(){
	maitenance_v.clear();
}

void Instance::clear_all(){
	clear_task_v();
	clear_maitenance_v();
}

vector<Task> Instance::get_tasks(){
	return this->task_v;
}

vector<Maitenance> Instance::get_maitenances(){
	return this->maitenance_v;
}

