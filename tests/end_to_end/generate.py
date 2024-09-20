import random
count_tests = 10

for test_num in range(0, count_tests) :
    file_name = "tests_in/test_" + f'{test_num+1:03}' + ".in"
    file = open(file_name, 'w')

    count_triangles = random.randint(200, 300)

    min_x = -200
    max_x =  200
    min_y = -200
    max_y =  200
    min_z = -200
    max_z =  200

    cub_sqrt_count_triangles = (int)(count_triangles ** (1/3))
    stepx  = cub_sqrt_count_triangles
    stepy  = cub_sqrt_count_triangles
    stepz  = cub_sqrt_count_triangles
    
    shiftx = max(abs(min_x), abs(max_x)) - 1
    shifty = max(abs(min_y), abs(max_y)) - 1
    shiftz = max(abs(min_z), abs(max_z)) - 1

    test_str = str(count_triangles) + "\n\n"
    file.write(test_str)
    for j in range(count_triangles) :

        test_str = ""
        cur_shiftx = random.randint(-stepx, stepx) * shiftx
        cur_shifty = random.randint(-stepy, stepy) * shifty
        cur_shiftz = random.randint(-stepz, stepz) * shiftz
        for k in range(3) :
            point_x = round(random.uniform(min_x, max_x), 2) + cur_shiftx
            point_y = round(random.uniform(min_y, max_y), 2) + cur_shifty
            point_z = round(random.uniform(min_z, max_z), 2) + cur_shiftz

            test_str += f'{point_x:<12}' + " " + f'{point_y:<12}' + " " + f'{point_z:<12}' + "\n"

        test_str += "\n"
        file.write(test_str)

    file.close()
    print("test ", test_num + 1, " generated")