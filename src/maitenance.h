#ifndef MAITENANCE_H
#define MAITENANCE_H

class Maitenance{
	private:
		int id;
		int m_time; //start time
		int op_time; //duration
	public:
		Maitenance(int, int, int);
		int get_mt();
		int get_opt();
		int get_id();
};

#endif // MAITENANCE_H