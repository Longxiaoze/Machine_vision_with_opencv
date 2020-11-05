import cv2
import numpy as np
import matplotlib.pyplot as plt

p = [[30.441362, -38.555408, -0.81197762, 198.48364],
 [25.222166, 19.615177, -37.90221, 98.621315],
 [-0.00082984846, -0.0060274387, -0.0047242129, 1]]

point = np.array([[0, 0, 0,1, 198, 99],
                    [4, 0, 1,1, 322, 163],
                    [2, 0, -1,1, 260, 186],
                    [0, 1, 1, 161, 81],
                    [4, 1, -2,1, 283, 295],
                    [1, 3, -2,1, 116, 261],
                    [3, 0, 1,1, 293, 140],
                    [0, 0, 1,1, 203, 64],
                    [0, 3, 1,1, 91, 125],
                    [0, 1, -2,1, 154, 192],
                    [2, 2, -2,1, 184, 265],
                    [3, 1, -2,1, 353, 274]])

print("点如下所示：")
print(point)
print()
print("根据实际点算出的像素点坐标为:")
a = []
for i in range(len(point)):
    a = np.dot(p,point[i][0:4])
    print(a)

x1 = 3
y1 = 0
z1 = -1
'''
x1 = 3
y1 = 3
z1 = -2
'''
point3 = np.array([x1,y1,z1,1])
point4 = np.dot(p,point3)
print("point4")
print(point4)

image = cv2.imread("mofang.bmp")
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
plt.figure("Image") # 图像窗口名称
plt.imshow(image)
plt.axis('on') # 关掉坐标轴为 off
plt.title('mofang') # 图像题目
plt.text(point4[0],point4[1],"13",color='g')
plt.show()
