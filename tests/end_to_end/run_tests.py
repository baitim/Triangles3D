import os
import glob
import subprocess
from pathlib import Path

tests_dir = str(Path(__file__).parent)
build_dir = str(Path.cwd())

def run(answer_dir, exe_file):
    os.system("mkdir -p " + answer_dir)
    file_name = answer_dir + "/answer_" + f'{test_num+1:03}' + ".ans"
    os.system("touch " + file_name)
    os.system("echo -n > " + file_name)
    ans_file = open(file_name, 'w')
    command = exe_file + " < " + file
    ans_file.write(subprocess.check_output(command, shell=True).decode("utf-8"))
    ans_file.close()

new_exe = build_dir + "/../../src/triangles"
old_exe = build_dir + "/old_version/triangles_old"
answer_new_dir = tests_dir + "/answers_new"
answer_old_dir = tests_dir + "/answers_old"

test_num = 0
files = list(map(str, glob.glob(tests_dir + "/tests_in/test_*.in")))
files.sort()

for file in files :
    run(answer_new_dir, new_exe)
    run(answer_old_dir, old_exe)
    test_num += 1
    print("test",  test_num, "passed")