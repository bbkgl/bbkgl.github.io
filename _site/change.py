import os

fdir = "_posts/"

file_names = os.listdir(fdir)

for name in file_names:
    file = "./" + fdir + name
    text = None
    new_text = ""
    with open(file, 'r') as f:        
        text = f.read()
    cnt = 1
    for line in text.split("\n"):
        if "title" in line and cnt == 4:
            print(line)
            new_text += "subtitle:   " + "你快乐吗？\n"
        else:
            new_text += line + "\n"
        cnt += 1
    with open(file, 'w') as f:
        f.write(new_text)

print(os.listdir(fdir))

