from change_picture import *
import os
import sys


if len(sys.argv) <= 1:
    print("usage: python commit.py \"what you want commit\"")
    exit(-1)

what = sys.argv[1]

for fname in os.listdir("./_posts"):
    md_path = "./_posts/" + fname
    fix2(md_path)


print(what)

os.system("git add .")
os.system("git commit -m {}".format(what))
os.system("git push origin master")
