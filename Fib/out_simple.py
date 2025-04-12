from PIL import Image, ImageDraw, ImageFont
import os

# 設定輸出資料夾
output_folder = "posts"
os.makedirs(output_folder, exist_ok=True)

# 設定圖片大小
image_size = (720, 720)
font_size = 32  # 字體大小
subscript_size = 24  # 下標字體大小
font_path = "CascadiaCode.ttf"  # C:\Windows\Fonts

def Fib(num):
    if (num==0):
        return 0
    if (num==1):
        return 1
    
    f0, f1= 0, 1
    for _ in range(2, num + 1):  # 從 2 開始計算到 num
        f0, f1 = f1, f0 + f1  # 更新數值
    
    return f1

# 產生 100 張圖片
for n in range(1, 2):
    img = Image.new("RGB", image_size, color=(40, 40, 40))
    draw = ImageDraw.Draw(img)

    font = ImageFont.truetype(font_path, font_size)
    font_sub = ImageFont.truetype(font_path, subscript_size)

    # 設定要寫入的文字
    text = f"Fibonacci Sequence Day {n}\n"+\
           f"F1 = 1\n" #rest

    # 計算文字大小以置中對齊
    text_bbox = draw.textbbox((0, 0), text, font=font)
    text_width = text_bbox[2] - text_bbox[0]
    text_height = text_bbox[3] - text_bbox[1]
    position = ((image_size[0] - text_width) // 2, (image_size[1] - text_height) // 2)

    # 繪製文字 (置中)
    draw.multiline_text(position, text, font=font, fill="white", align="center", spacing=12)

    # 儲存圖片
    filename = f"D{n}.png"
    img.save(os.path.join(output_folder, filename))

print("圖片產生完成，存放於:", output_folder)