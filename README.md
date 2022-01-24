# CCurses(C++ Curses)

<img width="80%" src="https://user-images.githubusercontent.com/38195137/150802555-cc822f5f-b3b6-4937-8b3f-ff3c487bd9eb.gif" />

ccurses(c++ curses) is a library made of ncurses library. The basic base was implemented by designing a c# window form.

#### Reference

* https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/

## Feature

* Easy
* Keyboard, mouse event
* Theme
* Wide Character

## requirement

#### Centos

```bash
yum install ncurses-devel
```

#### Ubuntu

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

>If you want Korean language, install a language pack.
>
>```bash
>apt-get install language-pack-ko
>```
>
>```bash
>LANG=ko_KR.UTF-8
>```

## Use

#### Just Make🧑‍🔧

```bash
make
```

#### test

```bash
./bin/Test
```

#### Cursor

move tab:   ``shift`` + ◀️,``shift`` + ▶️

move forcus: ``tab``

select:  ``mouse``, ``enter``

## Widget

* TextBox
* Button
* Input
* Tab
* List
* ProgressBar
* Table
* BarChart
* CheckBox
* Radio(TODO)
