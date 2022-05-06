# HotkeyListener4LogCmd
This is an extension of the [HotkeyListener tool](https://github.com/ChunanGang/HotkeyListener).

The original tool has an issue for log.cmd, since log.cmd requires the start and stop to be run in the same cmd windows.
But the original tool triggers log.cmd in different shells everytime, causing log.cmd fail to start and stop correctly.

This extension fixex this issue by creating a new cmd file (logSwitch.cmd) in run time, and this cmd file controls the start and stop of log.cmd 

## Usage:
  
    HotkeyListener.exe -hotkey HOT_KEY_COMBINATION -program PATH_OF_LOG.CMD -arg log.cmd_aruguments 
    #-arg is optional
 
 ! Make sure you run this program with command prompt as administrator. This is required for log.cmd
 
 Example
    
    HotkeyListener.exe -hotkey CONTROL+P -program "C:\Program Files (x86)\Windows Kits\10\Windows Performance Toolkit\gpuview\log.cmd" -arg "normal light"
   
After you ran this, a new cmd window will pop up. Do not close it. Now you can run other apps and use CONTROL+P to start log.cmd, and CONTROL+P again to stop.

ETL will be captured in the same directory of HotkeyListener.exe

## Download:
https://github.com/ChunanGang/HotkeyListener4LogCmd/releases/tag/1.0
