# ASCIItokiocolor

Для использования нужно написать свой конфиг в .txt файле в формате:
letter * *space* * color

Небольшой конфиг рисунка ниже:

```
( blue
) blue
| purple
: purple
; purple
\ purple
/ purple
i purple
T purple
! cyan
d blue
b blue
Y dark
```
![Image alt](https://github.com/sxaxq/ASCIItokiocolor/raw/master/image.png)

## Компиляция:
```
clang++ -std=c++17 vulkanrender.cc -o vulkanrender.exe
```
## Использование
```
vulkanrender.exe <cfg_path> <image_path>
```
