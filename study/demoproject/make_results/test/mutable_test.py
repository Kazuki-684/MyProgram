
class mutable_test():
    mutable = {"businness": True, "company name": False}
    
class mutable_test_ins(mutable_test):
    def __init__(self) -> None:
        super().__init__()
        print(super().mutable)
        
    def change_bool(self):
        super().mutable["company name"] = True
        print(super().mutable)
        
class mutable_test_ins2(mutable_test):
    def __init__(self) -> None:
        super().__init__()
        print(super().mutable)
        
    def change_bool(self):
        super().mutable["company name"] = True
        print(self.mutable)
    
    def instsnce_variable(self):
        self.test = 1
    
    def print_variable(self):
        print(self.test)
    
ins = mutable_test_ins2()
#ins.print_variable()
ins.instsnce_variable()
ins.print_variable()
