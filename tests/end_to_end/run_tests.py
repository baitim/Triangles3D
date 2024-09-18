import os
import glob
import subprocess

to_curr_dir = os.path.dirname(os.path.realpath(__file__))

triangles_exe = "./triangles"

answer_dir = to_curr_dir + "/answers"
os.system("mkdir -p " + answer_dir)

test_num = 0
files = list(map(str, glob.glob(to_curr_dir + "/tests_in/test_*.in")))
files.sort()

for file in files :

    file_name = answer_dir + "/answer_" + f'{test_num+1:03}' + ".out"
    os.system("touch " + file_name)
    os.system("echo -n > " + file_name)
    ans_file = open(file_name, 'w')

    command = triangles_exe + " < " + file
    test_str = subprocess.check_output(command, shell=True).decode("utf-8")

    ans_file.write(test_str)
    ans_file.close()
    test_num += 1
    print("test",  test_num, "passed")