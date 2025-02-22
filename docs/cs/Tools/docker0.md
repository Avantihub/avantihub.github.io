在 Ubuntu 中运行 `docker build -t audiowmark .` 这条指令之前，需要完成以下准备工作，包括安装 Docker、配置 Docker 环境以及准备 Dockerfile 和相关文件。以下是详细步骤：

---

### **1. 安装 Docker**
Docker 是一个容器化平台，用于构建、运行和管理容器。首先需要在 Ubuntu 中安装 Docker。

#### **步骤 1.1：更新系统包**
```bash
sudo apt update
sudo apt upgrade -y
```

#### **步骤 1.2：安装依赖工具**
```bash
sudo apt install apt-transport-https ca-certificates curl software-properties-common
```

#### **步骤 1.3：添加 Docker 官方 GPG 密钥**
```bash
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
```

#### **步骤 1.4：添加 Docker 仓库**
```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

#### **步骤 1.5：安装 Docker**
```bash
sudo apt update
sudo apt install docker-ce docker-ce-cli containerd.io
```

#### **步骤 1.6：验证 Docker 安装**
```bash
sudo docker --version
```
如果输出类似 `Docker version 20.10.12, build e91ed57`，说明安装成功。

---

### **2. 配置 Docker**
安装完成后，需要对 Docker 进行一些基本配置。

#### **步骤 2.1：启动 Docker 服务**
```bash
sudo systemctl start docker
sudo systemctl enable docker
```

#### **步骤 2.2：将当前用户加入 Docker 组（避免每次使用 `sudo`）**
```bash
sudo usermod -aG docker $USER
```
注销并重新登录以生效。

#### **步骤 2.3：验证 Docker 运行**
```bash
docker run hello-world
```
如果看到 `Hello from Docker!` 的输出，说明 Docker 配置成功。

---

### **3. 准备 Dockerfile 和相关文件**
`docker build -t audiowmark .` 指令会基于当前目录下的 `Dockerfile` 构建镜像。因此，需要确保以下文件已准备好：

#### **步骤 3.1：创建 Dockerfile**
在项目根目录下创建一个名为 `Dockerfile` 的文件，内容示例如下：
```Dockerfile
# 使用基础镜像
FROM ubuntu:20.04

# 安装依赖
RUN apt update && apt install -y \
    build-essential \
    cmake \
    libsndfile1-dev \
    git

# 克隆 audiowmark 源码
RUN git clone https://github.com/auerswald/audiowmark.git /app

# 构建 audiowmark
WORKDIR /app
RUN mkdir build && cd build && cmake .. && make

# 设置默认命令
CMD ["/app/build/audiowmark", "--help"]
```

#### **步骤 3.2：确保项目文件完整**
- 如果 `audiowmark` 项目需要额外的配置文件或资源文件，确保它们位于当前目录中。
- 如果项目依赖外部数据（如音频文件），可以通过 `COPY` 指令将其添加到镜像中。

---

### **4. 构建 Docker 镜像**
完成上述准备后，可以运行 `docker build` 指令构建镜像。

#### **步骤 4.1：进入项目目录**
```bash
cd /path/to/audiowmark
```

#### **步骤 4.2：构建镜像**
```bash
docker build -t audiowmark .
```
- **`-t audiowmark`**：为镜像指定标签（名称）。
- **`.`**：表示使用当前目录下的 `Dockerfile`。

#### **步骤 4.3：验证镜像**
```bash
docker images
```
如果看到 `audiowmark` 镜像，说明构建成功。

---

### **5. 运行容器**
构建完成后，可以通过以下命令运行容器：
```bash
docker run audiowmark
```
如果需要与容器交互，可以添加 `-it` 参数：
```bash
docker run -it audiowmark
```

---

### **6. 总结**
1. **安装 Docker**：通过官方仓库安装 Docker。
2. **配置 Docker**：启动服务并将用户加入 Docker 组。
3. **准备 Dockerfile**：编写 `Dockerfile` 并确保项目文件完整。
4. **构建镜像**：运行 `docker build -t audiowmark .`。
5. **运行容器**：通过 `docker run` 启动容器。

通过以上步骤，您可以在 Ubuntu 中成功运行 `docker build -t audiowmark .` 并构建 `audiowmark` 镜像。