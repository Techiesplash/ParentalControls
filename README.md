<div align="center">
  
# Minimalistic Parental Controls for Linux
Supported Systems:
<br/>

![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

![GitHub forks](https://img.shields.io/github/forks/Techiesplash/ParentalControls)
![GitHub repo size](https://img.shields.io/github/repo-size/Techiesplash/ParentalControls)
![GitHub issues](https://img.shields.io/github/issues/Techiesplash/ParentalControls)

![GitHub](https://img.shields.io/github/license/Techiesplash/ParentalControls)

<h2>Introduction</h2>
I made this project, as I could not easily find many working Parental Control stuff for Linux.
This automatically closes programs off a list. Meant to enforce on those without root access.

<br />
It includes the code for a systemd daemon, a CLI interface, and a GUI interface using wxWidgets.
<br /><br />
<h2>Setup</h2>
Download the source code, then run "./install.sh" in the folder to install the CLI interface and the daemon. 
<br />

### GUI
Additionally, you can run "./install.sh" in the GUI folder to install the GUI interface. Please ensure you have the required "wxWidgets" libraries:

<br />

### Arch Linux:
Install either the ```wxwidgets-gtk3``` or the ```wxwidgets-qt5``` package, depending on your preferences.

### Debian / Ubuntu
I believe you should install the ```libwxgtk3.0-dev``` package... Need to make sure though. Will do this soon

<br />
<h2>Usage</h2>
Use with the CLI using parentalctl, use with the GUI using parentalgui. The service name is "parentald.service".
<br /><br />
parentalctl disable/enable - Toggle whether the daemon should start activated<br />
parentalctl start/stop - Toggle whether or not the daemon will currently enforce<br />
parentalctl show - Display the list of programs to kill<br />
parentalctl add [program]... - Add program(s) to the list (path or name)<br />
parentalctl remove [program]... - Remove the following program(s) from the list
<br /><br />
<h2>Warning</h2>
Please be careful of what you add to the list of programs to kill. You may cause problems if you add certain programs. I am not responsible for any problems that may occur due to this.
<br /><br />
<h3>Anyone is free to use, copy, modify, merge, publish, distribute, sublicense, or and/or sell copies of the software*.</h3>
