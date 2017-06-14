# php src: 5.2.17

# 基本流程
## 给扩展起一个名字，比如 demo
 
## 开发
### 在ext目录 写一个 demo.def
### ./ext_skel  --extname=demo  --proto=./demo.def
###  To use your new extension, you will have to execute the following steps:
  1. $ cd ..
  2. $ vi ext/demo/config.m4
  2.2  rm autom4te.cache -rf   
  3. $ ./buildconf   会重新生成./configure文件
  4. $ ./configure --[with|enable]-demo
  5. $ make
  6. $  ./sapi/cli/php  -ddisplay_errors=On  ext/demo/demo.php
  7. $ vi ext/demo/demo.c
  8. $ make
  Repeat steps 2-6 until you are satisfied with ext/demo/config.m4 and
  step 6 confirms that your module is compiled into PHP. Then, start writing
  code and repeat the last two steps as often as necessary.
   
## 单元测试并与php相同函数的结果进行diff
## 内存泄露check 以及其它的check(都有啥)
## 性能评估
## 修改原有的php函数，使其成为扩展函数的封装， 即[适配器模式]。 
## 扩展上线。
