#ifndef MAITENANCE_H
#define MAITENANCE_H

class Maitenance{
	private:
		int id;
		int m_time; //start time
		int op_time; //duration
	public:
		int get_mt();
		int get_opt();
		int get_id();
        void set_id(int);
        void set_mt(int);
        void set_opt(int);
};

#endif // MAITENANCE_H
