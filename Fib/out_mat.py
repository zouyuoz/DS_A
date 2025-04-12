from PIL import Image, ImageDraw, ImageFont
import os

# 設定輸出資料夾
output_folder = "output_images"
os.makedirs(output_folder, exist_ok=True)

# 設定圖片大小
image_size = (720, 720)
font_size = 32  # 主字體大小
subscript_size = 24  # 下標字體大小
s = 12  # 行間距
font_path = r"C:\Windows\Fonts\CascadiaCode.ttf"  # 確保字體路徑正確

# 定義 Fibonacci 函數
def Fib(num):
    if num == 0: return 0
    if num == 1: return 1
    f0, f1 = 0, 1
    for _ in range(2, num + 1):
        f0, f1 = f1, f0 + f1
    return f1

# 產生 100 張圖片
for n in range(2, 171):
    # 創建背景
    img = Image.new("RGB", image_size, color=(40, 40, 40))
    draw = ImageDraw.Draw(img)

    # 載入字型
    font = ImageFont.truetype(font_path, font_size)
    font_sub = ImageFont.truetype(font_path, subscript_size)

    # **主要數學公式 (置中對齊)**
    text_main = f"Fibonacci Sequence Day {n}\n" + \
                f"F{n-2} + F{n-1} = F{n}"

    # **數值計算部分 (左對齊)**
    text_rest = f"{Fib(n-2)}\n+ {Fib(n-1)}"

    # **最後一行 (藍色)**
    text_final = f"= {Fib(n)}"

    # 計算 bbox (取得寬度與高度)
    text_bbox_main = draw.textbbox((0, 0), text_main, font=font)
    text_width_main = text_bbox_main[2] - text_bbox_main[0]
    text_height_main = text_bbox_main[3] - text_bbox_main[1]

    text_bbox_rest = draw.textbbox((0, 0), text_rest, font=font)
    text_width_rest = text_bbox_rest[2] - text_bbox_rest[0]
    text_height_rest = text_bbox_rest[3] - text_bbox_rest[1]

    text_bbox_final = draw.textbbox((0, 0), text_final, font=font)
    text_width_final = text_bbox_final[2] - text_bbox_final[0]
    text_height_final = text_bbox_final[3] - text_bbox_final[1]

    # **計算總高度，讓區塊置中**
    total_height = text_height_main + s + text_height_rest + s + text_height_final
    y_center = (image_size[1] - total_height) // 2

    # **計算左右對齊**
    center_x = image_size[0] // 2  # 圖片的水平中心
    max_width = max(text_width_rest, text_width_final)  # 取得較寬的區塊

    # `text_main` 置中
    position_main = (center_x - text_width_main // 2, y_center)

    # `text_final` 置中
    position_final = (center_x - text_width_final // 2, y_center + text_height_rest + text_height_main + 55)

    # `text_rest` 貼齊 `text_final` 右側
    right_margin = center_x + max_width // 2  # 右側對齊點
    position_rest = (right_margin - text_width_rest, y_center + text_height_main + 28)

    # **繪製文字**
    draw.multiline_text(position_main, text_main, font=font, fill="white", align="center", spacing=s)
    draw.multiline_text(position_rest, text_rest, font=font, fill="white", align="right", spacing=s)
    draw.text(position_final, text_final, font=font, fill=(80, 190, 250))  # 藍色

    # 儲存圖片
    filename = os.path.join(output_folder, f"D{n}.png")
    img.save(filename)

print("✅ 圖片產生完成，存放於:", output_folder)
