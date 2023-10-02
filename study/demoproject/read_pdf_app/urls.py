from django.contrib import admin
from django.urls import path
from .views import hello_world, upload_file, show_business

urlpatterns = [
    path('read/', upload_file, name='upload_file'),
    path('business/media/<pdf_file_url>/', show_business, name='business'),
    path('hello/', hello_world, name='hello'),
]