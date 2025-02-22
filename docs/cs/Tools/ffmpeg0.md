`./configure --with-ffmpeg` 和 `./configure --enable-mpeg` 是两个常见的配置选项，但它们的作用和适用场景不同。以下是详细解释：

---

### **1. `--with-ffmpeg`**
#### **作用**
- **`--with-ffmpeg`** 是一个 **外部库依赖选项**，用于指定项目是否使用 `ffmpeg` 库。
- 它通常用于配置项目是否链接到 `ffmpeg` 库，以支持 `ffmpeg` 提供的功能（如音视频编解码、格式转换等）。

#### **使用场景**
- 如果项目需要处理多种音视频格式（如 MP4、AVI、MKV），并且依赖 `ffmpeg` 的功能，可以使用 `--with-ffmpeg`。
- 例如，多媒体处理工具（如 `VLC`、`HandBrake`）通常会支持 `ffmpeg`。

#### **示例**
```bash
./configure --with-ffmpeg
```
- 如果系统中已安装 `ffmpeg`，配置脚本会自动检测并启用 `ffmpeg` 支持。
- 如果未安装 `ffmpeg`，可以指定路径：
  ```bash
  ./configure --with-ffmpeg=/path/to/ffmpeg
  ```

#### **依赖**
- 需要提前安装 `ffmpeg` 库及其开发文件：
  ```bash
  sudo apt install ffmpeg libavcodec-dev libavformat-dev libavutil-dev
  ```

---

### **2. `--enable-mpeg`**
#### **作用**
- **`--enable-mpeg`** 是一个 **功能启用选项**，用于启用项目内部的 MPEG 格式支持。
- 它通常用于配置项目是否支持 MPEG 格式（如 MP3、MPEG-1、MPEG-2）。

#### **使用场景**
- 如果项目需要处理 MPEG 格式的音视频文件，可以使用 `--enable-mpeg`。
- 例如，音频处理工具（如 `libsndfile`）可能支持 MPEG 格式。

#### **示例**
```bash
./configure --enable-mpeg
```
- 如果项目支持该选项，配置脚本会启用 MPEG 相关功能。
- 如果项目不支持该选项，会报错 `unrecognized options: --enable-mpeg`。

#### **依赖**
- 可能需要安装 MPEG 相关的库（如 `libmpg123`）：
  ```bash
  sudo apt install libmpg123-dev
  ```

---

### **3. 区别对比**
| **特性**         | **`--with-ffmpeg`**                          | **`--enable-mpeg`**                        |
|------------------|---------------------------------------------|-------------------------------------------|
| **类型**         | 外部库依赖选项                              | 功能启用选项                              |
| **作用**         | 指定是否使用 `ffmpeg` 库                    | 启用项目内部的 MPEG 格式支持              |
| **适用场景**     | 需要 `ffmpeg` 提供的音视频处理功能          | 需要支持 MPEG 格式（如 MP3、MPEG-1/2）    |
| **依赖**         | 需要安装 `ffmpeg` 及其开发文件              | 可能需要安装 MPEG 相关库（如 `libmpg123`）|
| **示例**         | `./configure --with-ffmpeg`                 | `./configure --enable-mpeg`               |
| **错误处理**     | 如果未安装 `ffmpeg`，配置脚本可能报错       | 如果项目不支持该选项，会报错              |

---

### **4. 实际应用**
#### **场景 1：多媒体处理工具**
- 如果需要支持多种音视频格式（如 MP4、AVI、MKV），使用 `--with-ffmpeg`。
- 示例：
  ```bash
  ./configure --with-ffmpeg
  ```

#### **场景 2：音频处理工具**
- 如果需要支持 MPEG 格式（如 MP3），使用 `--enable-mpeg`。
- 示例：
  ```bash
  ./configure --enable-mpeg
  ```

#### **场景 3：同时支持**
- 如果项目既需要 `ffmpeg` 的功能，又需要 MPEG 格式支持，可以同时使用两个选项：
  ```bash
  ./configure --with-ffmpeg --enable-mpeg
  ```

---

### **5. 总结**
- **`--with-ffmpeg`**：用于指定是否使用 `ffmpeg` 库，适用于需要 `ffmpeg` 功能的项目。
- **`--enable-mpeg`**：用于启用项目内部的 MPEG 格式支持，适用于需要处理 MPEG 格式的项目。
- 根据项目需求选择合适的选项，并确保相关依赖已安装。