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

def fix1(file):
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

def fix2(file):
    url_list = []
    with open(file, "r", encoding="utf-8") as f:
        text = f.read()
        imgs_urls = re.findall(pat, text)
        for it in imgs_urls:
            if "../cloud_img" in it[1]:
                new_url = str(it[1]).replace("../cloud_img", "https://raw.githubusercontent.com/bbkgl/bbkgl.github.io/master/cloud_img")
                url_list.append([it[1], new_url])
    for url_pair in url_list:
        text = text.replace(url_pair[0], url_pair[1])
    with open(file, "w", encoding="utf-8") as f:
        f.write(text)

def fix3(file: str):
    url_list = []
    with open(file, "r", encoding="utf-8") as f:
        text = f.read()
        imgs_urls = re.findall(pat, text)
        for it in imgs_urls:
            if "https://raw.githubusercontent.com/bbkgl/bbkgl.github.io/master/cloud_img" in it[1]:
                new_url = str(it[1]).replace("https://raw.githubusercontent.com/bbkgl/bbkgl.github.io/master/cloud_img", "/cloud_img")
                url_list.append([it[1], new_url])
    for url_pair in url_list:
        text = text.replace(url_pair[0], url_pair[1])
    lines = text.split("\n")
    new_lines = []

    for line in lines:
        new_lines.append(line)
        if "layout: " in line:
            new_lines.append("typora-root-url: ..")

    new_text = ""
    for line in new_lines:
        new_text += line
        new_text += "\n"

    with open(file, "w", encoding="utf-8") as f:
        f.write(new_text)


if __name__ == "__main__":
    for fname in os.listdir("./_posts"):
        md_path = "./_posts/" + fname
        fix3(md_path)
    # file_path = "G:\\Mymd\\bbkgl.github.io\\_posts\\2021-01-08-图片测试.md"
    # fix3(file_path)