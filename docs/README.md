# 麻将局

> ftc update at `22-02-20`



## 相关论文

1. suphx 2020

   论文下载于`./suphx.pdf`

   论文讲解：[https://www.bilibili.com/video/BV11z411b7jk](https://www.bilibili.com/video/BV11z411b7jk)

2. oracle guiding reinforce learning 2022

   论文下载于`./variational_oracle_guiding_for.pdf`



## 现有成果

1. oracle guiding reinforce learning提供的数据集，下载地址：[https://drive.google.com/drive/folders/19v6bpG_9nfKgSGVscbQ6efaJP1fFoPpo?usp=sharing](https://drive.google.com/drive/folders/19v6bpG_9nfKgSGVscbQ6efaJP1fFoPpo?usp=sharing)

2. 麻将轮子`pymahjong`（整局）

   github地址：[https://github.com/pymahjong/pymahjong](https://github.com/pymahjong/pymahjong)

3. 麻将轮子`MahjongPy`（单局）

   github地址：[https://github.com/Agony5757/mahjong](https://github.com/Agony5757/mahjong)

4. 雀魂对战客户端（支持插件），详见[https://www.bilibili.com/video/BV1PR4y1j7PM](https://www.bilibili.com/video/BV1PR4y1j7PM)

   github地址：[https://github.com/MajsoulPlus/majsoul-plus](https://github.com/MajsoulPlus/majsoul-plus)

5. 离线牌谱分析软件（仅供参考），非深度学习，仅是搜索，rust语言编写，支持天凤和雀魂，详见[https://www.bilibili.com/video/BV1PR4y1j7PM](https://www.bilibili.com/video/BV1PR4y1j7PM)

   github地址：[https://github.com/Equim-chan/akochan-reviewer](https://github.com/Equim-chan/akochan-reviewer)

6. 在线出牌辅助

   （仅支持天凤）github地址：[https://github.com/zhangjk95/MahjongAI](https://github.com/zhangjk95/MahjongAI)
   
   （仅支持雀魂）github地址：[https://github.com/Jimboom7/AlphaJong](https://github.com/Jimboom7/AlphaJong)

**关联**：

* 1、2、3同是论文oracle guide提供的，2是基于3的，2用了3，但是没提供3的文档。
* 4、5是视频https://www.bilibili.com/video/BV1PR4y1j7PM提供的



## 分工

0. 前期调研，轮子编写（发牌、算番等） `已经完成`

1. 雀魂or天凤平台对接
2. 读论文、写强化学习
3. 参考现有内容完成非强化学习版本（搜索算法）的baseline  `可选`
4. 在线实验（基于1）
5. 论文撰写



## 前期调研资料

主要是oracle-guiding提供的数据集，已经上传到百度网盘，如果嫌大的话自己按照上面的地址下载

```
链接: https://pan.baidu.com/s/1dOEbp9XU0LTbU2akNX4n9g  密码: du7i
```



