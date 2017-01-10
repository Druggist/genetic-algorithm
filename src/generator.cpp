#include "generator.h"

int main(int argc, char * argv[]){
   int quantity, max_time, n, m;
   string dir = "";
  if (argc < 6){
    std::cout << "Usage:\n" << argv[0] << "<number_of_instances> <number_of_tasks> <max_time> <start_count> <output_directory> " << endl;
    exit(0);
  }
  if (argc == 5) {
    m = atoi(argv[5]);
    dir = "../data";
  }else{
    m = atoi(argv[5]);
    dir = argv[6];
  }
  string filename = "";
  max_time = atoi(argv[3]);
  quantity = atoi(argv[1]);
  n = atoi(argv[2]);
  for (int i = 0; i < quantity; i++){
  	Instance I;
  	I.generate_instance(n, max_time ,i, false);
  	filename = dir + "/file_" + std::to_string(m) + ".txt";
  	I.dump_instance(filename);
    m++;
  }
  //Instance I;
  //I.read_instance("file_0.txt");
  return 0;
}
