import random
count_tests = 10

for test_num in range(0, count_tests) :
    file_name = "tests_dat/test_" + f'{test_num+1:03}' + ".in"
    file = open(file_name, 'w')

    count_triangles = random.randint(1000, 2000)
    min_x = -100
    max_x =  100
    min_y = -100
    max_y =  100
    min_z = -100
    max_z =  100

    test_str = str(count_triangles) + "\n\n"
    file.write(test_str)
    for j in range(count_triangles) :

        test_str = "" 
        for k in range(3) :
            point_x = random.uniform(min_x, max_x)
            point_y = random.uniform(min_y, max_y)
            point_z = random.uniform(min_z, max_z)

            test_str += f'{point_x:<20}' + " " + f'{point_y:<20}' + " " + f'{point_z:<20}' + "\n"

        test_str += "\n"
        file.write(test_str)

    file.close()
    print("test ", test_num + 1, " generated")