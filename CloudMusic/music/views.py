#coding:utf-8
from django.shortcuts import render
from django.http import HttpResponse
import sqlite3
import json
# Create your views here.

def index(request):
    return HttpResponse("Welcome!")

def get_music_list(request):
    page=int(request.GET['page'])
    data=get_page(page)
    return HttpResponse(json.dumps(data))

def get_songs(request):
    list_id=request.GET['id']
    data=get_list(list_id)
    data=eval(data)
    return HttpResponse(json.dumps(data))

def get_page(page):
    con=sqlite3.connect('music.db')
    cursor=con.cursor()
    cursor.execute("select * from music_list")
    count=0
    data=[]
    for row in cursor:
        if(count<page*9):
            count+=1
            continue
        music_list={}
        music_list['id']=row[0]
        music_list['name']=row[1]
        music_list['image_url']=row[2]
        data.append(music_list)
        if(len(data)==9):
            break
    cursor.close()
    con.close()
    return data

def get_list(list_id):
    con=sqlite3.connect('music.db')
    cursor=con.cursor()
    cursor.execute("select songs from music_list where code='%s'"%list_id)
    for row in cursor:
        data=row[0]
    return data
