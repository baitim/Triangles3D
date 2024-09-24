import os
import glob
import subprocess

to_curr_dir = os.path.dirname(os.path.realpath(__file__))

triangles_exe = "./triangles"

test_num = 0
files = list(map(str, glob.glob(to_curr_dir + "/tests_in/test_*.in")))
files.sort()

def run(answer_dir):
    os.system("mkdir -p " + answer_dir)
    file_name = answer_dir + "/answer_" + f'{test_num+1:03}' + ".ans"
    os.system("touch " + file_name)
    os.system("echo -n > " + file_name)
    ans_file = open(file_name, 'w')
    command = triangles_exe + " < " + file
    ans_file.write(subprocess.check_output(command, shell=True).decode("utf-8"))
    ans_file.close()

for file in files :
    answer_new_dir = to_curr_dir + "/answers_new"
    run(answer_new_dir)

    answer_old_dir = to_curr_dir + "/answers_old"
    run(answer_old_dir)

    test_num += 1
    print("test",  test_num, "passed")