import os

fdir = "_posts/"

file_names = os.listdir(fdir)

for name in file_names:
    if "2019" not in name:
        old_name = "./" + fdir + name
        new_name = "./" + fdir + "2019-09-26-" + name
        os.rename(old_name, new_name)

print(os.listdir(fdir))

