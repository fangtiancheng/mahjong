#  麻将AI文档

>  ftc at 22-03-08

本项目整体框架如下：

```
|-include/
|	common.h	# 一些基本定义和常用函数
|	mjenum.h	# 打表搜索的离线生成器-01
|	core.h		# 麻将算番轮子
|	syanten_enum.h	# 打表搜索的离线生成器-02
|	model.h		# 基于libtorch的麻将AI模型
|	dataloader.h	# 基于libtorch的oracle-learning数据集合的dataloader
|-src/
|	# 对应头文件的具体实现
|	....
|-docs/
|	# 前期调研的文件资料
|	suphx.pdf
|	oracle-guiding.pdf
|-MahjongLib/
|	# 用来对比速度的
```

## 关于麻将轮子

### 理论

1. 为什么麻将AI要写麻将轮子？

   答：本项目致力于复现suphx，在suphx文中作者提到，部分输入特征是“丢某张牌后能否满足12000点牌型的2向听”。因此需要搜索牌型（递归地丢牌和摸牌）和番型（递归地对手牌做切分）。除此以外，麻将的对局和赢点都非常地有讲究，训练AI也需要有reward，因此需要写麻将轮子。

2. 为什么要重写麻将轮子，现有的轮子不行吗？

   答：现有轮子行，但不完全行。本麻将轮子部分参考了[MahjongAI/MahjongLib](https://github.com/zhangjk95/MahjongAI.git)下面`mjcore`和`syanten`的实现，其中`src/syanten_enum`几乎完全照搬的原文`syanten`。那为什么说原来的轮子不行呢？我询问了一下原作者，他说他搜到了3向听（深度为4），大概在1s以内完成。根据现有轮子剪枝，搜索一次大概需要15s，完全无法满足需要，因此需要在麻将轮子上面做文章。

3. 如何剪枝？

   答：有两部分搜索，分别针对其剪枝。第一部分搜索是替换手牌，三向听深度4，那么这棵树深度就是4。麻将有34张牌，那么一个节点就有34*33个分叉。第二部分是算番剪枝，相同手牌不同分割方法会导致不同的番型，例如：

   ```
   万： 1 1 1 2 2 2 3 3 3
   条： 7 8 9
   筒： 9 9                           门清自摸1万
   
   分割法1： 
   万： (111) (222) (333)
   条： (789)
   筒： (99)
   三暗刻 + 门清自摸 = 3番
   
   分割法2：
   万： (123) (123) (123)
   条： (789)
   筒： (99)
   纯全带幺九 + 平胡 + 一杯口 + 门清自摸 = 6番
   ```

   第一类搜索的剪枝方法是向听剪枝，首先计算`剩余深度`=`最大深度`-`当前深度`，如果`向听数`+1超过剩余深度的话，弃之。此外，上一轮摸的牌这一轮不能丢、已经胡了的牌不再进行搜索了（其他路搜索能搜到）。

   第二类搜索的剪枝方法是查表分割，就是把数牌和字牌每种情况所能分割的面子情况离线打表，然后在线搜索。

4. 现有轮子的优越点在哪？

   [MahjongAI/MahjongLib](https://github.com/zhangjk95/MahjongAI.git)下面的轮子没有实现查表分割，本文实现了。相比之下，`mjcore`和`syanten`组合搜索三向听需要18s的手牌，本文在4s就能搜索完毕（还可以优化，比如减少`hand_t`的复制构造以及多线程搜索）。



### 项目逻辑

1. common

   ```cpp
   typedef std::array<int, 37> hand_t; // 手牌，下标与牌的对应关系见tile_t
   enum tile_t{...}; // 手牌的枚举类型
   enum seq_t{...}; // 面子、杠子的枚举类型
   struct fuuro_t; // 副露类
   enum score_level_t; // 番大小类型
   ```

   

2. mjenum

   ```cpp
   // 生成map的离线算法
   auto load_num_map(); // 将文本化的.dat文件导入内存中
   auto load_wind_map(); // 将文本化的.dat文件导入内存中
   uint32_t // 麻将进行bit压缩后的产物
       // 例如 123400001 => 0b001_010_011_100_000_000_000_000_001
   hand_to_index   // etc: hant_t => [uint32_t(base=M), uint32_t(base=P), 
       			// uint32_t(base=S), uint32_t(base=wind)]
   pure_num_to_seq // etc: _1 _2 _3, base=M => seq_t::M123
   pure_wind_to_seq// etc: _East _East _East _East => EastEEE
   dfs_num  // 用dfs算法去生成数牌的字典
   dfs_wind // 用dfs算法去生成字牌的字典
   xxx_parser // 对文本内容进行解析的函数
   ```

   

3. core

   ```cpp
   // 麻将算番轮子，尚未完工
   ```

   

4. syanten

   ```cpp
   // 向听数，主要参考MahjongAI/MahjongLib/syanten.cpp
   ```

   



## 关于麻将AI

敬请期待



## 关于实战训练

敬请期待
