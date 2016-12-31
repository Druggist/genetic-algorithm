#include "generator.h"

int main(){
  string filename = "file.txt";
  int n = 30;
  Instance I;
  I.generate_instance(n, 50, false);
  I.dump_instance(filename);
  return 0;

}