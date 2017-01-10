#!/usr/bin/env
import subprocess
from sys import argv
import os
from datetime import datetime

def runner(argv):
    
    if argv[0] == argv[1]:
        print("Error, this is the same dir!")
        exit(1)
    
    app_path = os.path.join(os.getcwd(), "bin", "main.app")
    data_input_path = os.path.join(os.getcwd(),argv[0])
    data_output_path = os.path.join(os.getcwd(), argv[1])
    data_instance_path = ""
    out_instance_path = ""
    output_file = ""
    count = argv[2]
    err_ocurr = []

    if not os.path.exists(data_input_path):
        print("Cannot open directory {} ", format(argv[0]))
        exit(1)
    
    if not os.path.exists(data_output_path) or not os.path.isdir(data_output_path):
        os.mkdir(data_output_path)
    
    for i_dir in os.listdir(data_input_path):
        data_instance_path = os.path.join(data_input_path, i_dir)
        
        if os.path.isdir(data_instance_path):
            out_instance_path = os.path.join(data_output_path, "out_"+i_dir)
        if not os.path.isdir(out_instance_path) and not os.path.isdir(out_instance_path):
            print("doesnt exist")
            os.mkdir(out_instance_path)

        for files in os.listdir(data_instance_path):
            if os.path.isfile(files) is False:
                output_file = "out_" + files
                print("Processing {} file now!".format(files))
                cmd = [app_path]
                cmd.append(os.path.join(data_instance_path, files))
                cmd.append(os.path.join(out_instance_path, output_file))
                cmd.append(count)
                process = subprocess.Popen(cmd, stdout=subprocess.PIPE)
                exit_code = process.wait()
                if exit_code != 0:
                    print("An error occured during processing task {} from directory {}".format(files, data_instance_path))
                    err_ocurr.append(files)
                print("Process returned exit code: {}".format(exit_code))
                #for line in process.stdout:
                    #print(line)
                log_write("Process for {} executed with code {} \n".format(files, exit_code))
    
    if len(err_ocurr) == 0:
        log_write("Task done! No errors occured!\n\n\n")
    else:
        log_write("\n\n ERRORS OCCURED!!! \n\n\n")
        for task in err_ocurr:
            log_write("Error occured in: {} \n".format(task))
                
def log_write(log_mess):
    with open("runner_log.txt", "a") as l:
        l.write(log_mess)



if __name__ == "__main__":
    if len(argv) < 4:
        print(argv[0])
        print("Usage: {} <data_input_directory> <data_output_directory> <iter_count>".format(argv[0]))
        exit(1)
    else:
        log_write("\t STARTING JOB {} \n".format(datetime.now().strftime('%Y-%m-%d %H:%M:%S')))
        runner(argv[1:])

