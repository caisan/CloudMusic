#coding:utf-8
import sqlite3

def get_page(page):
    con=sqlite3.connect('music.db')
    cursor=con.cursor()
    cursor.execute("select * from music_list")
    for row in cursor:
        print(row)
        return

get_page(1)
