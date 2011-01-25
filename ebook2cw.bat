@echo off
echo ebook2cw - Batch file for Windows (obsolete; replaced by ebook2cwgui)
echo -
echo Usage: You will be promted for a filename and (at your option)
echo additional parameters for ebook2cw (such as wpm, tone freq etc).
echo -
echo If a config file (ebook2cw.conf) was found in the current directory,
echo the settings in this file are used, but any settings you specify
echo here will override those.
echo -
echo -
echo Enter the name of the text file to convert to CW. Note that you can
echo simply drag and drop a file from the Windows Explorer to this window.
echo -
set /p file="Text file: "
echo -
echo Enter any additional command line parameters for ebook2cw, or leave
echo just press enter to use the values from ebook2cw.conf.
echo -
set /p par="Parameters: "
echo -
ebook2cw.exe %par% %file%
echo Done. 
pause

