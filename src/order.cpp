#include "order.h"

void Order::initialization(vector<int> O, vector<Task> task_v, vector<Maitenance> maitenance_v){
	machine1.set_id(1);
	machine1.set_start(0);
	machine1.set_stop(0);
	machine2.set_id(2);
	int n, tmp;
	for (vector<int>::size_type i = 0; i < O.size(); i++){
		//Machine 1
		n = 1;
		while(!machine1.add(O[i], task_v, maitenance_v)){
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
			machine2.add(O[i], task_v, maitenance_v);
		}else{
			machine2.addt(machine1.get_sop(), O[i], task_v);
		}
	}
}