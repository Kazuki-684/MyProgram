from rest_framework.views import APIView
from rest_framework.response import Response
import threading
from .create_boxes import create_bussiness_box, create_bussiness_risks_box, create_history_box, create_management_policy_etc_box
from .create_contents import create_bussiness_contents, create_management_policy_etc_contents, create_bussiness_risks_contents, create_history_contents


class CreateBoxes(APIView):
    def get(self, request):
        result_dict = {}
        collecntion_name = request.GET.get("collname")
        target_functions = [
            create_bussiness_box,
            create_bussiness_risks_box,
            create_management_policy_etc_box,
            create_history_box
        ]
        
        threads = [threading.Thread(target=lambda f=f: f(result_dict, collecntion_name)) for f in target_functions]
        for thread in threads:
            thread.start()

        for thread in threads:
            thread.join()
        
        return Response(result_dict)


class CreateContents(APIView):
    target_function = {
        "事業内容":create_bussiness_contents,
        "経営方針と課題":create_management_policy_etc_contents,
        "事業等のリスク":create_bussiness_risks_contents,
        "沿革":create_history_contents
    }
    
    def get(self, request):
        collecntion_name = request.GET.get("collname")
        category = request.GET.get("category")
        print(f"第回目:{category}")
        result = self.target_function[category](collecntion_name)
        return Response(result)
        

"""
result_dict = {'bussiness': False, 'management_policy': False, 'bussiness_risks': False, 'history': False}
thread1 = threading.Thread(target=lambda: create_bussiness_box(result_dict))
thread2 = threading.Thread(target=lambda: create_bussiness_risks_box(result_dict))
thread3 = threading.Thread(target=lambda: create_management_policy_etc_box(result_dict))
thread4 = threading.Thread(target=lambda: create_history_box(result_dict))
thread1.start()
thread2.start()
thread3.start()
thread4.start()

thread1.join()
thread2.join()
thread3.join()
thread4.join()

print(result_dict)
"""

"""    
def printest():
    result_dict = {'bussiness': False, 'management_policy': False, 'bussiness_risks': False, 'history': False}
    bussiness = create_bussiness_box(result_dict)
    bussiness_risks = create_bussiness_risks_box(result_dict)
    management_policy = create_management_policy_etc_box(result_dict)
    history = create_history_box(result_dict)
        
    print(bussiness)
    print(bussiness_risks)
    print(management_policy)
    print(history)
    
printest()    
"""