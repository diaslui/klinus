from django.urls import path
from apps.portal.views import *

app_name = "portal"

urlpatterns = [

    path('',IndexView.as_view(), name="index"),

]