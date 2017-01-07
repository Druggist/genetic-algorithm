#ifndef MAITENANCE_H
#define MAITENANCE_H

class Maitenance{
	private:
		int id;
		int start_t;
		int duration; 
	public:
		Maitenance(int);

		int get_id();
		int get_start_t();
		int get_duration();
		
		void set_start_t(int);
		void set_duration(int);
};

#endif // MAITENANCE_H
