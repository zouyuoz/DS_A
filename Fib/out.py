from PIL import Image, ImageDraw, ImageFont
import os

# 設定輸出資料夾
output_folder = "posts"
os.makedirs(output_folder, exist_ok=True)

# 設定圖片大小
image_size = (720, 720)
font_size = 32  # 字體大小
subscript_size = 24  # 下標字體大小
font_path = "CascadiaCode.ttf"  # 確保字體存在

# 定義 Fibonacci 函數
def Fib(num):
    if num == 0:
        return 0
    if num == 1:
        return 1
    
    f0, f1 = 0, 1
    for _ in range(2, num + 1):  # 計算 Fibonacci 數列
        f0, f1 = f1, f0 + f1  
    
    return f1

# 產生 100 張圖片
for n in range(2, 51):
    img = Image.new("RGB", image_size, color=(40, 40, 40))
    draw = ImageDraw.Draw(img)

    font = ImageFont.truetype(font_path, font_size)
    font_sub = ImageFont.truetype(font_path, subscript_size)

    # 設定要寫入的文字
    text = f"Fibonacci Sequence Day {n}\n"+\
           f"F{n-2} + F{n-1} = F{n}\n"+\
           f"{Fib(n-2)} + {Fib(n-1)} = {Fib(n)}"  # `F_n` 仍為白色

    # 計算整體文本的 bbox，讓它置中
    text_bbox = draw.textbbox((0, 0), text, font=font)
    text_width = text_bbox[2] - text_bbox[0]
    text_height = text_bbox[3] - text_bbox[1]
    position = ((image_size[0] - text_width) // 2, (image_size[1] - text_height) // 2)

    # **第一步：正常繪製全部白色文字**
    draw.multiline_text(position, text, font=font, fill="white", align="center", spacing=12)

    # **第二步：找出 `F_n` 的位置，然後覆蓋藍色**
    half_equation = f"{Fib(n-2)} + {Fib(n-1)} = "  # `F_n` 之前的部分
    text_bbox_equation = draw.textbbox((0, 0), half_equation, font=font)
    text_width_equation = text_bbox_equation[2] - text_bbox_equation[0]
    
    full_eq = f"{Fib(n-2)} + {Fib(n-1)} = {Fib(n)}"
    bboxFull = draw.textbbox((0,0), full_eq, font=font)
    pos_w = bboxFull[2] - bboxFull[0]
    pos = (image_size[0] - pos_w) // 2
    delt = 0
    if (n < 7): delt = 1

    # `F_n` 的位置 = 先取得等號 `=` 之後的位置
    position_fn = (pos + text_width_equation + delt, position[1] + text_height - 8.7)

    # **繪製藍色 `F_n`，覆蓋白色**
    draw.text(position_fn, str(Fib(n)), font=font, fill=(80, 190, 250))

    # 儲存圖片
    filename = f"D{n}.png"
    img.save(os.path.join(output_folder, filename))

print("✅ 圖片產生完成，存放於:", output_folder)
