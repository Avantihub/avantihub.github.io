这两种 `typedef` 声明在 C 语言中看似相似，但它们有不同的含义和用途。我们来逐个分析。

### 1. `typedef struct point *RECT[5];`

这个声明定义了一个类型别名 `RECT`，它表示一个包含 5 个元素的数组，其中每个元素是一个指向 `struct point` 类型的指针。

#### 解释：
- `struct point`：表示一个结构体类型。
- `*`：表示指针。
- `RECT[5]`：表示一个包含 5 个元素的数组。
  
因此，`typedef struct point *RECT[5];` 的意思是：
- `RECT` 是一个类型，表示一个长度为 5 的数组，这个数组的每个元素都是一个指向 `struct point` 结构体的指针。

换句话说，`RECT` 是一个数组类型，数组有 5 个元素，每个元素都是指向 `struct point` 类型的指针。

#### 示例：
```c
typedef struct point *RECT[5]; // 定义类型 RECT

struct point {
    int x;
    int y;
};

RECT rects;  // rects 是一个长度为 5 的数组，每个元素是指向 struct point 的指针

rects[0] = malloc(sizeof(struct point));  // 分配内存并赋值给第一个元素
rects[1] = malloc(sizeof(struct point));  // 分配内存并赋值给第二个元素
```

在这个例子中，`rects` 是一个长度为 5 的数组，每个数组元素是指向 `struct point` 类型的指针。

### 2. `typedef struct point (*RECT)[5];`

这个声明定义了一个类型别名 `RECT`，它表示一个指向包含 5 个 `struct point` 类型元素的数组的指针。

#### 解释：
- `struct point`：表示一个结构体类型。
- `(*RECT)`：表示一个指针（这里括号是必需的，表示 `RECT` 是一个指针）。
- `[5]`：表示一个长度为 5 的数组。

因此，`typedef struct point (*RECT)[5];` 的意思是：
- `RECT` 是一个类型，表示一个指向包含 5 个 `struct point` 类型元素的数组的指针。

换句话说，`RECT` 是一个指针类型，指向一个包含 5 个 `struct point` 结构体的数组。

#### 示例：
```c
typedef struct point (*RECT)[5]; // 定义类型 RECT

struct point {
    int x;
    int y;
};

RECT rects;  // rects 是一个指向包含 5 个 struct point 元素的数组的指针

struct point points[5];  // 声明一个包含 5 个 struct point 的数组
rects = &points;  // rects 指向 points 数组
```

在这个例子中，`rects` 是一个指针，它指向一个包含 5 个 `struct point` 类型元素的数组。

### 区别总结：

| 特性                              | `typedef struct point *RECT[5];`                       | `typedef struct point (*RECT)[5];`                        |
|-----------------------------------|-------------------------------------------------------|---------------------------------------------------------|
| 类型含义                          | `RECT` 是一个长度为 5 的数组，数组的每个元素是指向 `struct point` 的指针。 | `RECT` 是一个指向包含 5 个 `struct point` 的数组的指针。 |
| 数据结构                          | 数组（`RECT` 是一个数组类型）。                      | 指针（`RECT` 是一个指针类型）。                        |
| 访问方式                          | 访问数组元素时直接通过数组下标，如 `rects[0]`，每个元素是指针。 | 需要先解引用指针，再通过数组下标访问，如 `(*rects)[0]`。 |
| 示例代码中的声明方式              | `RECT rects;` — `rects` 是一个数组。                 | `RECT rects;` — `rects` 是一个指向数组的指针。           |

### 进一步说明：
- `typedef struct point *RECT[5];` 定义了一个数组，数组的每个元素是一个指向 `struct point` 的指针。这意味着你可以通过 `rects[i]` 来访问数组中的指针，并通过该指针访问 `struct point` 的数据。
- `typedef struct point (*RECT)[5];` 定义了一个指向数组的指针。你可以通过 `*rects` 获取指向的数组，然后通过数组下标访问数组中的每个 `struct point` 元素。

### 举个例子区分这两者：

#### 1. `typedef struct point *RECT[5];` 示例：
```c
typedef struct point *RECT[5];  // RECT 是一个长度为 5 的数组，每个元素是指向 struct point 的指针

struct point {
    int x;
    int y;
};

RECT rects;  // 声明一个 RECT 类型的变量 rects

// 为每个指针分配内存并初始化
for (int i = 0; i < 5; i++) {
    rects[i] = malloc(sizeof(struct point));  // 为每个指针分配内存
    rects[i]->x = i;  // 初始化数据
    rects[i]->y = i * 2;
}
```

#### 2. `typedef struct point (*RECT)[5];` 示例：
```c
typedef struct point (*RECT)[5];  // RECT 是一个指向包含 5 个 struct point 元素的数组的指针

struct point {
    int x;
    int y;
};

struct point points[5];  // 声明一个包含 5 个 struct point 的数组
RECT rects = &points;  // rects 指向 points 数组

// 使用 rects 访问数组中的元素
rects[0][0].x = 10;  // 通过 rects 指针访问数组元素
rects[0][0].y = 20;
```

通过这些例子，你可以看到，`typedef struct point *RECT[5];` 用于声明一个指向结构体的指针数组，而 `typedef struct point (*RECT)[5];` 用于声明一个指向结构体数组的指针。