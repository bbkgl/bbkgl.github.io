import os
import re
import requests

pat = "(?:!\[(.*?)\]\((.*?)\))"

def download(url:str):
    r = requests.get(url)
    img = r.content
    img_name = url.split("/")[-1]
    img_path = "cloud_img/" + img_name
    with open(img_path, "wb") as f:
        f.write(img)
    return "../" + img_path

def fix(file):
    imgs = []
    text = ""
    url_list = []
    with open(file, "r", encoding="utf-8") as f:
        text = f.read()
        imgs_urls = re.findall(pat, text)
        for it in imgs_urls:
            if "bbkglpic" in it[1]:
                new_url = download(it[1])
                url_list.append([it[1], new_url])
    for url_pair in url_list:
        text = text.replace(url_pair[0], url_pair[1])
    with open(file, "w", encoding="utf-8") as f:
        f.write(text)



md_path = "_posts/2019-11-03-opecv检测图像中几何图形.md"
fix(md_path)