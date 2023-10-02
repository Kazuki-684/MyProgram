from django.http import HttpResponse
from rest_framework.views import APIView
from rest_framework.response import Response
from datetime import datetime

def start_hello(request):
    return HttpResponse("Start HELLO!!")

class HelloAPI(APIView):
    def get(self, request):
        return Response( {'事業内容': True,'経営方針と課題': False, '事業等のリスク': True, '沿革': False,'category1':False, 'category2':False})
        """
        return Response({
            {'bussiness': True, 'ja': '事業内容'},
            { 'management_policy': True, 'ja':'経営方針と課題'},
            { 'bussiness_risks': True, 'ja':'事業等のリスク'},
            {'history': True, 'ja':'沿革'},
            {'category1':True, 'ja':'カテゴリー１'},
            {'category2':True, 'ja':'カテゴリー２'}
            })
        """
class GetParam(APIView):
    def get(self, request):
        param_value = request.GET.get("collname")
        print(param_value)
        return Response(param_value)