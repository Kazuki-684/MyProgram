def show_torf():
    result = {"category": "bussiness", "TorF":True}
    return result

def set_torf(input :dict, result_dict):
    print(input)
    if(input["TorF"]==True):
        result_dict[input["category"]] = True

def test1():
    test_dict = {"bussiness": False, "company name": False}
    torf = show_torf()
    print(torf)
    set_torf(torf, test_dict)
    print(test_dict)
    
test1()