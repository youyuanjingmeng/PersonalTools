# -*- coding: UTF-8 -*-
import os
import sys

path = "F://test"
file_ext = ".exe"

def file_back():
    pass

def file_rename(file_name):
    name_ext = os.path.splitext(file_name) # 返回值为tuple类型()
    print(name_ext)
    if (name_ext[1] == ""):
        os.rename(file_name, file_name + file_ext)
    else:
        if (name_ext[1] != file_ext):
            os.rename(file_name, name_ext[0] + file_ext)

def path_walk(path):
    path_coll = []
    for dir_path, dir_names, file_names in os.walk(path):
        for file in file_names:
            full_path = os.path.join(dir_path, file)
            path_coll.append(full_path)
    return path_coll

def main():
    for file in path_walk(path):
        file_rename(file)

if __name__ == '__main__':
    main()