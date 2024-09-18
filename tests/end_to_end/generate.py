import random
count_tests = 10

for test_num in range(0, count_tests) :
    file_name = "tests_in/test_" + f'{test_num+1:03}' + ".in"
    file = open(file_name, 'w')

    count_triangles = random.randint(30, 60)

    min_x = -200
    max_x =  200
    min_y = -200
    max_y =  200
    min_z = -200
    max_z =  200

    stepx  = 7000
    shiftx = max(abs(min_x), abs(max_x))
    stepy  = 7000
    shifty = max(abs(min_y), abs(max_y))
    stepz  = 7000
    shiftz = max(abs(min_z), abs(max_z))

    test_str = str(count_triangles) + "\n\n"
    file.write(test_str)
    for j in range(count_triangles) :

        test_str = "" 
        for k in range(3) :
            point_x = random.uniform(min_x, max_x) + random.randint(-stepx, stepx) * shiftx
            point_y = random.uniform(min_y, max_y) + random.randint(-stepy, stepy) * shifty
            point_z = random.uniform(min_z, max_z) + random.randint(-stepz, stepz) * shiftz

            test_str += f'{point_x:<20}' + " " + f'{point_y:<20}' + " " + f'{point_z:<20}' + "\n"

        test_str += "\n"
        file.write(test_str)

    file.close()
    print("test ", test_num + 1, " generated")