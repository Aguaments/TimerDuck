# Git 在本地构建仓库
```sh
git init # 在当前目录下创建仓库，生成.git文件夹，包含了仓库的一些必要文件
git init xxx # 在当前目录下的xxx文件夹下创建仓库，此时.git文件在xxx目录下
git clone xxxx.git # 从github克隆一个仓库
```

# 工作区域
- 工作区：使用init创建的目录
- 暂存区：修改的代码临时存放区 .git/index
- 本地仓库：本地这边的代码仓 .git/objects

## 文件状态
- 未跟踪：新创建的文件，还没有添加到仓库中
- 未修改：没有修改过的文件
- 已修改：添加到仓库中的文件，并且是修改过的
- 已暂存：通过add添加到暂存区中的文件

# git相关命令
```sh
git status # 查看当前所在分支、仓库状态
git status -s # 简化版
git add . # 将当前目录下的未跟踪的文件添加到暂存区
git commit -m "xxx" # 将暂存区的代码提交到本地仓库，并且需要指定提交的备注信息
git log # 可以查看到本地commit的日志
git log --oneline # 可以看到简洁提交日志
git reflog  
git ls-files # 查看暂存区中的文件
```

# git reset
可以退回到之前的版本 ，如下参数可以添加
- --soft + 版本编号：保留工作区、暂存区
- --hard + 版本编号：丢弃工作区、暂存区
- --mixed + 版本编号：只保留工作区

# git diff
比较两个版本之间的差异，默认比较工作区和暂存区之间的差异
```sh
git diff # 默认比较工作区和暂存区之间的差异
git diff xxxx1 xxxx2 # 比较xxxx1和xxxx2两个版本之间的差异

```

# git rm
```sh
git rm xxx # 可以同时删除工作区和暂存区中的文件

git rm --cached xxx # 只删除暂存区中的文件
```

# 远程仓库  

## 创建ssh密钥
```sh
ssh-keygen -t rsa -b 4096 # 在本机电脑的.ssh文件夹下面就可以看到公私钥
``` 
## git clone
```sh
git clone git@github.com:xxxxx
```

## git pull 
git pull <远程仓库名> <远程分支名>:<本地分支名>

# 分支
可以在不同分支上开发新的功能代码，保证主线代码的有效。

## git branch
```sh
git branch dev(分支名) # 创建dev分支
git checkout dev(分支名) # 切换到dev分支
git switch dev(分支名)
```