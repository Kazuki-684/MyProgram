from django.shortcuts import render
from django.http import HttpResponse
from django.core.files.storage import FileSystemStorage
import logging
from .ocr2 import tesseractOCR
from django.conf import settings
import json
from django.views.decorators.csrf import csrf_exempt

# Create your views here.
def hello_world(request):
    greet = {'id':1,'greet':'Hello World!'}
    return HttpResponse(json.dumps(greet,indent=2))

#mediaファイルに書き込むためのもの
#今後はデータベースに書き込むように変更する必要あり？？？
@csrf_exempt
def upload_file(request):
    if request.method == 'POST' and request.FILES['imgFile']:
        myfile = request.FILES['imgFile']
        fs = FileSystemStorage()
        filename = fs.save(myfile.name, myfile)
        upload_file_url = fs.url(filename) 
        Json = {"status":"upload succeed!","content":f"{upload_file_url}"}
        return HttpResponse(json.dumps(Json,indent=2))
    return HttpResponse("Please use 'POST' method")


def get_text(request, img_url):
    url = f'{settings.BASE_DIR}/{img_url}'
    try:
        content = tesseractOCR(url)
        temp = {"status": "OCR succeed!", "content": f"{content}"}
        Json = json.dumps(temp, indent=2, ensure_ascii=False)  # UTF-8エンコーディングを使用するようにする
        return HttpResponse(Json, content_type='application/json; charset=utf-8')
    except Exception as e:
        return HttpResponse(json.dumps({"status": "failure", "content": "none"}, indent=2), content_type='application/json; charset=utf-8')

"""
#https://blog.janjan.net/2021/03/03/django-url-conf-parameter-include/
def get_text(request, img_url):
    url = f'{settings.BASE_DIR}/{img_url}'
    try:
        content = tesseractOCR(url)
        temp = {"status":"OCR succeed!","content":f"{content}"}
        Json = json.dumps(temp,indent=2)
        return HttpResponse(Json)
    except Exception as e:
        return HttpResponse(json.dumps({"status":"failure","cotent":"none"},indent=2))  
    #return HttpResponse(json.dumps(Json,indent=2)) 
"""

