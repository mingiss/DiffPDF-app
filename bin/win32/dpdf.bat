@echo off
:: PDF comparing script to be used in ucompare 
:: Two pdf file paths should be provided as script parameters
:: Using example:
::    dpdf foo.pdf bar.pdf 
:: Returns zero errorlevel in case of no differences

D:\bin\utils\texgr\DiffPDF\diffpdf_vtex.exe -a %1 %2 diff.pdf
if "%errorlevel%" == "0" (
  echo Success: no differences
) else (
  echo !Error: files are different
)
exit %errorlevel%
