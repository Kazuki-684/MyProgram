from django.shortcuts import render
from django.http import HttpResponse
from django.core.files.storage import FileSystemStorage
import logging
from .show_business import make_show_business
from django.conf import settings

# Create your views here.
def hello_world(request):
    return HttpResponse('hello world!')

#mediaファイルに書き込むためのもの
#今後はデータベースに書き込むように変更する必要あり？？？
def upload_file(request):
    if request.method == 'POST' and request.FILES['pdfFile']:
        myfile = request.FILES['pdfFile']
        fs = FileSystemStorage()
        filename = fs.save(myfile.name, myfile)
        upload_file_url = fs.url(filename)        
        return render(request, 'upload.html', {'upload_file_url': upload_file_url})
    return render(request, 'upload.html')


#https://blog.janjan.net/2021/03/03/django-url-conf-parameter-include/
def show_business(request, pdf_file_url):
    url = f'{settings.BASE_DIR}/media/{pdf_file_url}'
    content = make_show_business(url)
    return render(request, 'show_result.html', {'content':content})
