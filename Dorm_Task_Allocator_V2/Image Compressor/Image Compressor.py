from PIL import Image


paircnt = 0

for i in range(0,16, 2):
    im = Image.open(f'a_{i:06d}.png').convert('1')
    cval = 0
    ccnt = 0
    for y in range(0, im.size[1]):
        for x in range(0, im.size[0]):
            pix = im.getpixel((x,y))
            val = 1 if pix == 255 else 0
            if val != cval:
                print(f"{ccnt}, ", end='')
                paircnt += 1
                cval = val
                ccnt = 1
            else:
                ccnt += 1

            if ccnt >= 256:
                print(f"{ccnt} 0 ", end='')
                paircnt += 2
                ccnt = 0
            # print(val, end='')
        # print()
    print(f"{ccnt}, ", end='')

# print(paircnt)