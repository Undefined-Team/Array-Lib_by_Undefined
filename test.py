def func(list):
    sort_list = sorted(list) 
    print(sort_list) # [1, 2, 3, 4, 6, 7, 8, 99, 100]
    new_str = str(sort_list[0])
    i = 1
    while i in range(len(sort_list)):
        if sort_list[i] == sort_list[i - 1] + 1:
            new_str += "-" + str(sort_list[i])
        else:
            new_str += "," + str(sort_list[i])
        i+=1
    print(new_str)
    return new_str

func([6,7,8,99,100,2,3,4,1])