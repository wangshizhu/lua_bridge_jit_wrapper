
test = {}
test.module = 1
test.test_func_1 = function (num,name) 
    print('hello test_func_1',num,name) 
    return 1,20,"test_func_1"
end

test.test_func_2 = function (num,name) 
    print('hello test_func_2',num,name) 
    return 1,20,"test_func_2"
end

test.test_func_3 = function (num,name) 
    print('hello test_func_3',num,name) 
    return 1,20,"test_func_3"
end

return "test"