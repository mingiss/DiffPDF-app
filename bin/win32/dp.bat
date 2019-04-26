:: Script for manual comparing of resulting pdf's of two ucompare compilations
:: Working dir -- where the root folder of the manuscript with resulting files is located
:: Script parameter -- manuscript name
:: Using example:
::    dp ms001
:: First found pair of pdf's will be compared in following search order:
::    ms001\compilation1\ms001.pdf ms001\compilation2\ms001.pdf
::    ms001\compilation1\www\ms001.pdf ms001\compilation2\www\ms001.pdf
::    ms001\compilation1\print\ms001.pdf ms001\compilation2\print\ms001.pdf

set suffix=%2
if [%suffix%x]==[x] set suffix=pdf

set jobname=%1

set subdir=
if not exist %jobname%\compilation1\%subdir%%jobname%.%suffix% set subdir=www\
if not exist %jobname%\compilation1\%subdir%%jobname%.%suffix% set subdir=print\

if exist %jobname%\compilation1\%subdir%%jobname%.%suffix% (
call diffpdf.bat %jobname%\compilation1\%subdir%%jobname%.%suffix% %jobname%\compilation2\%subdir%%jobname%.%suffix%
) else (
msg "%username%" No pdf files found
)
