#  ML2023Spring - HW3 
>
>  [课程主页](https://speech.ee.ntu.edu.tw/~hylee/ml/2023-spring.php)
> 
>  [课程视频](https://www.bilibili.com/video/BV1TD4y137mP/?spm_id_from=333.337.search-card.all.click&vd_source=436107f586d66ab4fcf756c76eb96c35)
> 
>  [Kaggle link](https://www.kaggle.com/t/86ca241732c04da99aca6490080bae73)


!!! info "2023Spring"
    本文档是对 ML2023Spring - HW03 的解析，主要包括任务目标、性能指标、数据解析、Sample code 主体部分解析、Baselines 等内容。
    

# 任务目标

使用 CNN 进行图像分类

# 目录

- [任务目标（图像分类）](#任务目标图像分类)
- [性能指标（Metric）](#性能指标metric)
- [数据解析](#数据解析)
  - [数据下载（kaggle）](#数据下载kaggle)
- [Gradescope (Report)](#gradescope-report)
  - [Q1. Augmentation Implementation](#q1-augmentation-implementation)
  - [Q2. Visual Representations Implementation](#q2-visual-representations-implementation)
- [Baselines](#baselines)
  - [Simple baseline (0.637)](#simple-baseline-0637)
  - [Medium baseline (0.700)](#medium-baseline-0700)
  - [Strong baseline (0.814)](#strong-baseline-0814)
  - [Boss baseline (0.874)](#boss-baseline-0874)
- [小坑](#小坑)
- [参考链接](#参考链接)

# 任务目标（图像分类）

使用 CNN 进行图像分类

# 性能指标（Metric）

在测试集上的分类精度：
$$
Acc = \frac{pred==label}{len(data)} * 100\% \nonumber
$$

  # 数据解析

- ./train (Training set): 图像命名的格式为 "x_y.png"，其中 x 是类别，含有 10,000 张被标记的图像
- ./valid (Valid set): 图像命名的格式为 "x_y.png"，其中 x 是类别，含有 3,643 张被标记的图像
- ./test (Testing set): 图像命名的格式为 "n.png"，n 是 id，含有 3,000 张未标记的图像

数据来源于 food-11 数据集，共有 11 类


# Q1 Data Augmentation

## Why Data Augmentation is important in CNN?


在使用卷积神经网络（CNN）进行图像分类时，**数据增强（Data Augmentation）** 是提升模型泛化能力、防止过拟合的核心策略之一。其必要性源于以下关键原因：

---

### **1. 缓解过拟合（Overfitting）问题**
- **问题背景**：CNN模型参数量大，若训练数据不足，模型容易“记住”训练样本的噪声或局部特征，而非学习通用规律。
- **数据增强的作用**：通过对原始图像施加随机变换（如旋转、翻转、裁剪），生成新的训练样本，增加数据多样性，迫使模型关注更本质的特征。
- **示例**：  
  - 原始数据：100张猫的图片。  
  - 增强后：通过翻转、旋转等生成500张变体，模型不再依赖特定角度或背景的特征。

---

### **2. 提升模型对真实场景的鲁棒性**
- **现实挑战**：实际应用中，图像可能因光照变化、遮挡、拍摄角度不同而差异显著。
- **数据增强的作用**：模拟真实场景中的多样性，让模型适应复杂条件。  
  - **常用增强方法**：  
    - **几何变换**：旋转（±30°）、水平/垂直翻转、随机裁剪（保留主体）。  
    - **颜色扰动**：调整亮度、对比度、饱和度，添加噪声。  
    - **遮挡模拟**：随机擦除（Random Erasing）、添加遮挡块。  
  - **示例**：  
    - 对医学影像（如X光片）添加随机遮挡，模拟拍摄时的仪器干扰，提升模型对局部病变的识别能力。

---

### **3. 平衡类别不均衡（Class Imbalance）**
- **问题背景**：某些类别样本数量远少于其他类别（如罕见疾病图像），导致模型偏向多数类。
- **数据增强的作用**：对少数类样本进行针对性增强（如更激进的变换），增加其数据量和多样性。  
  - **示例**：  
    - 在猫狗分类任务中，若“猫”类样本较少，可对猫的图片应用更多增强（如弹性变形、颜色抖动），平衡两类数据量。

---

### **4. 减少对数据收集的依赖**
- **实际限制**：标注高质量图像耗时费力，尤其在专业领域（如卫星图像分析、病理切片识别）。
- **数据增强的作用**：通过算法生成新数据，降低对原始数据量的要求。  
  - **示例**：  
    - 农业领域中，仅需少量作物病害图片，通过增强生成不同生长阶段、光照条件下的样本，训练出实用的分类模型。

---

### **5. 增强方法示例与效果**
| **增强类型**       | **具体操作**                          | **适用场景**                     |
|--------------------|---------------------------------------|----------------------------------|
| **几何变换**       | 旋转、翻转、平移、缩放                | 物体方向/位置不固定的分类任务    |
| **颜色扰动**       | 调整HSV通道、添加高斯噪声             | 光照变化频繁的场景（如自动驾驶） |
| **随机裁剪**       | 从图像中随机截取子区域                | 避免模型过度关注局部特征         |
| **混合增强**       | Mixup、CutMix（混合多张图像）         | 提升模型对复杂边界的判断能力     |
| **风格迁移**       | 应用不同纹理或艺术风格                | 艺术图像分类、跨域适应           |

---

### **6. 实验验证**
- **经典案例**：在ImageNet数据集上，数据增强可使Top-1准确率提升3-5%。  
- **代码示例**（使用TensorFlow/Keras）

```python

from tensorflow.keras.preprocessing.image import ImageDataGenerator

  datagen = ImageDataGenerator(
      rotation_range=30,     # 随机旋转±30°
      width_shift_range=0.2, # 水平平移幅度
      height_shift_range=0.2,
      shear_range=0.2,       # 剪切变换
      zoom_range=0.2,        # 随机缩放
      horizontal_flip=True,  # 水平翻转
      fill_mode='nearest'    # 填充新像素的策略
  )

  # 将增强应用于训练数据
  train_generator = datagen.flow_from_directory(
      'train_data/',
      target_size=(224, 224),
      batch_size=32
  )

```


### **总结**
数据增强通过**低成本扩充训练数据**和**模拟现实复杂性**，显著提升CNN模型的泛化能力和鲁棒性。它是解决小样本学习、类别不均衡和过拟合问题的关键技术，尤其在医疗、农业、工业检测等数据稀缺领域不可或缺。合理选择增强策略（需结合具体任务调整），可最大化模型性能。

Reference: [Hoper-J's Note](https://github.com/Hoper-J/HUNG-YI_LEE_Machine-Learning_Homework/tree/master)

## How to implement Data Augmentation in CNN?

使用torchvision库中的transforms模块，可以方便地实现数据增强。
torchvision.transforms 是 pytorch 中的图像预处理包，提供了常用的图像变换方式，可以通过 Compose 将多个变换步骤整合到一起

1.官方的tutorial: https://pytorch.org/vision/stable/transforms.html

2.前辈写好的绘图函数，可以方便地查看增强效果: https://blog.csdn.net/weixin_42426841/article/details/129903800

3.了解compose，Compose 可以将 transforms 的方法组合起来，形成新的 transforms 去使用

```python

compose = T.Compose([
    # 将图像缩放到固定的形状（高度=宽度=128）
    T.Resize((128, 128)),
    # 对图像应用高斯模糊，核大小为3，标准差为0.1
    T.GaussianBlur(3, 0.1),
    # 随机地改变图像的亮度和色调。亮度因子从[0.5, 1.5]之间均匀地选择，色调因子从[-0.3, 0.3]之间均匀地选择。
    T.ColorJitter(brightness=0.5, hue=0.3),
    # 随机反转图像，概率为0.5
    T.RandomInvert(p=0.5),
    # 随机应用一个变换列表，概率为0.6。
    # 这里变换列表中只有一个变换，就是随机旋转图像，角度为0到60度之间
    T.RandomApply(transforms=[T.RandomRotation(degrees=(0, 60))], p=0.6),
])
demo = [compose(orig_img) for i in range(5)]
plot(demo)

```


### 如何通过medium baseline

1. 通过增加数据增强的方法，如旋转、翻转、裁剪、缩放等，增加训练数据的多样性。

2. 增加training epoch.先尝试12个epoch，如果模型没有过拟合，可以逐渐增加epoch的数量。

### 我的尝试过程

2.6 
1.按要求加了data augmentation,但是acc只有0.3~0.35，可能是augmentation太多，难以收敛。或者是训练时间太短。

2.尝试加入了增加epoch,从64增加到128 没有明显提升。

3.怀疑是lr太大，尝试将lr从0.0003降到0.0001，但是没有明显提升。

4.参考dalao的实现 https://github.com/Hoper-J/HUNG-YI_LEE_Machine-Learning_Homework/blob/master/HW03/HW03_Medium_0.70533.ipynb

可能是augmentation方法太难学(),尝试将augmentation方法改为TrivialAugmentWide
```python
train_tfm = transforms.Compose([
    # Resize the image into a fixed shape (height = width = 128)
    transforms.Resize((128, 128)),
    transforms.RandomChoice(transforms=[
        # Apply TrivialAugmentWide data augmentation method
        transforms.TrivialAugmentWide(),

        # Return original image
        transforms.Lambda(lambda x: x),
    ],
    p=[0.95, 0.05]),
    # transforms.RandomHorizontalFlip(),
    # transforms.RandomVerticalFlip(),
    # transforms.RandomGrayscale(0.1),
    # transforms.RandomSolarize(threshold=192.0),
    # transforms.ColorJitter(brightness=.5,hue=0.5),
    # transforms.RandomRotation(degrees=(0, 180)),
    # transforms.RandomInvert(),
    transforms.ToTensor(),
])
```

这段代码是使用 `transforms.RandomChoice` 对图像进行数据增强（data augmentation）

### 1. `transforms.RandomChoice(transforms=[...], p=[...])`
`RandomChoice` 是一种随机选择多个变换方法中的一个应用到图像上的方法。你可以指定一个变换的列表（`transforms`），并为每个变换设置一个概率（`p`）。`RandomChoice` 会根据这些概率随机选择一个变换来应用。

- **`transforms=[...]`**：这是一个包含多个变换方法的列表。每个变换会作用于输入图像。
- **`p=[...]`**：这是与 `transforms` 中每个变换方法对应的概率。每个概率指定了该变换被选择的可能性。

### 2. `transforms.TrivialAugmentWide()`
这是一个常见的图像增强方法，它会应用一组预定义的常见增强操作（比如旋转、翻转、裁剪等），而不需要手动配置每种操作。`TrivialAugmentWide` 是一个简单而高效的增强方法，适用于多种场景。它的操作通常会相对较大幅度地改变图像的视觉效果，增强模型的鲁棒性。

### 3. `transforms.Lambda(lambda x: x)`
这个变换实际上没有对图像做任何改变。它只是简单地返回输入图像 `x`。可以将它视为一个占位符，意味着在某些情况下，你可能选择不对图像进行任何修改。

### 4. `p=[0.95, 0.05]`
这个参数定义了每个变换的选择概率。在这个例子中，`0.95` 是选择 `TrivialAugmentWide` 的概率，而 `0.05` 是选择 `Lambda(lambda x: x)`（即不做任何改变）的概率。



### 总结
这段代码的作用是：
- 在大多数情况下（95% 的概率），应用 `TrivialAugmentWide` 进行数据增强。
- 少数情况下（5% 的概率），直接返回原图，不做任何更改。

### Summary

经过24个epoch之后
[ Train | 024/024 ] loss = 0.60261, acc = 0.80405 
[ Valid | 024/024 ] loss = 1.06140, acc = 0.68441

## Strong Baseline

根据TA的文档
Simple : 0.50099 
Medium : 0.73207 Training Augmentation + Train Longer 
Strong : 0.81872 Training Augmentation + Model Design + Train Looonger  (+Cross Validation + Ensemble) 
Boss :  0.88446 Training Augmentation + Model Design +Test Time 
Augmentation + Train Looonger  (+ Cross Validation + Ensemble) 


1. 使用更复杂的模型，如ResNet、EfficientNet等，提升模型的表达能力。