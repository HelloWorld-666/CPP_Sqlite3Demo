# CPP_Sqlite3Demo
sqlite3: search db,write data to txt.

**使用方法：**  
当前目录下有一个.db文件（sqlite本地数据库，可通过navicat打开），里面的数据如下：  
```
name   bar_code
烟草1  6901028207041
烟草2  6901028207042
...
烟草10 6901028207050
```
操作时，会先根据目标值去查找本地db，查找到了则将其打印到桌面的.txt文件中去。  
  
本地数据库创建脚本在当前目录下的.sql文件中。