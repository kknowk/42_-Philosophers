# プロジェクトタイトル

42_-Philosophers

## 概要

哲学者が死なないようにフォークを与え、食事と睡眠も与えます。  
実行すると、タイムログと結果が出力されます。


## 動機

42Tokyoの課題であり、また、  
哲学者のグループがいつフォークを手に取り、飢えで死ぬことなくスパゲッティを食べるかを  
正確にタイミングを計ることで、スレッドがどのように機能するかを学ぶことを目的としています。  
スレッド、セマフォによる並列処理、gettimeofdayにようタイムログの出力の仕方を学びます。

## 使用方法

> - **normal**
> ```bash php
> #!/bin/bash
> cd 42_-Philosophers
> cd philo
> make
> ./philo 哲学者の数　餓死するまでの時間　食べる時間　寝る時間　食べる回数
> 0 1 has taken a fork （出力が出ます。）
> ```

> - **bornus**
> ```bash php
> #!/bin/bash
> cd 42_-Philosophers/philo_bonus
> make (以下normalと同じ)

## 出力の例

**無限ループ**  
基本的に、哲学者が偶数なら、  
餓死するまでの時間　> 2 *　(食べる時間 +　寝る時間)で  
奇数なら<br>
餓死するまでの時間　> 3 *　(食べる時間 +　寝る時間)で  
無限ループします。その差が大きいほどそれは安定します。  

> - **無限ループ例**
> ```bash php  
> ./philo 2 410 200 200
> ```

**全ての哲学者が指定回数食べる**  
先ほどの無限ループ条件に追加して  
各々が第6引数である食べる回数まで食べればループが終わります。  

> - **指定回数で抜ける例**
> ```bash php  
> ./philo 2 410 200 200 2
> 0 1 has taken a fork （以下出力結果）
> 0 1 has taken a fork
> 0 1 is eating
> 200 1 is sleeping
> 200 2 has taken a fork
> 200 2 has taken a fork
> 200 2 is eating
> 400 1 is thinking
> 400 2 is sleeping
> 400 1 has taken a fork
> 400 1 has taken a fork
> 400 1 is eating
> 600 2 is thinking
> 600 1 is sleeping
> 600 2 has taken a fork
> 600 2 has taken a fork
> 600 2 is eating
> 800 2 is sleeping
> 800 1 is thinking
> 800 1 has taken a fork
> 800 1 has taken a fork
> 800 1 is eating (ループを抜ける)
> ```

**エラー、餓死する**  
基本的に上記の例以外はエラーか、餓死により、そもそも始まらないか、ループを抜けます。

> - **エラー例**
> ```bash php  
> ./philo 2 410 200 (引数が足りない)
> Error: Wrong number of arguments (出力されます)
> ```

> - **餓死する例**
> ```bash php  
> ./philo 2 300 200 200
> 0 1 has taken a fork （以下出力結果）
> 0 1 has taken a fork
> 0 1 is eating
> 200 1 is sleeping
> 200 2 has taken a fork
> 200 2 has taken a fork
> 200 2 is eating
> 300 1 died (ループを抜ける)
> ```

## 技術スタック

C言語
