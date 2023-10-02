from django.urls import path
from django.conf import settings
from .views import CreateBoxes, CreateContents
#import debug_toolbar

urlpatterns = [
    path('bool_all/', CreateBoxes.as_view(), name='create_boxes'),
    path('contents/',CreateContents.as_view(), name='create_contents')
]