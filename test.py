for base in [1, 11, 21]:
    for i in range(7):
        i += base
        print("std::tuple<int, int, int>(%d, %d, %d),"%(i, i+1, i+2))