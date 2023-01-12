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

<h2>Requirements</h2>
The GUI interface is made using WxWidgets, which must be installed in order to get it working:
<br />

### Arch Linux:
```
sudo pacman -S wxwidgets-gtk3
```
Alternatively,
```
sudo pacman -S wxwidgets-qt5
```

### Debian / Ubuntu
```
sudo apt-get install libwxgtk3.0-dev
```
<h2>Installing</h2>
To download the source, run this in the terminal (Or download the zip file)

```
git clone https://github.com/Techiesplash/ParentalControls
```
then run (Sudo is required):
```
sudo ./install.sh
```
This script will compile the both the daemon and the CLI interface and install them for you.

To install the GUI interface, run:
```
sudo ./install_gui.sh
```
This will compile and install the GUI.
<br />

<h2>Usage</h2>
The CLI interface can be used with the command:

```
sudo parentalctl
```
The GUI interface can be launched with:
```
sudo parentalgui
```
And the daemon that runs in the background is ```parentald```.

### Examples
Turn off at startup:
```
sudo parentalctl disable
```
Turn off right now (Not permanent)
```
sudo parentactl stop
```
Show the list of programs to kill:
```
sudo parentalctl show
```
Add ```exampleprogram``` to the list:
```
sudo parentalctl add exampleprogram
```
Add ```exampleprogram``` to the list:
```
sudo parentalctl add /program/path/exampleprogram
```
Add multiple programs to the list:
```
sudo parentalctl add example1 example2
```
Remove a program from the list
```
sudo parentalctl remove example1 example2
```
The CLI interface contains a help menu. It provides the available commands to use.
<h2>Warning</h2>
Please be careful of what you add to the list of programs to kill. You may cause problems if you add certain programs. I am not responsible for any problems that may occur due to this.
<br /><br />

## Built With

* [WxFormBuilder](https://github.com/wxFormBuilder/wxFormBuilder) - Used to make the GUI

## Authors

* **Techiesplash** - *Initial work* - [Techiesplash](https://github.com/Techiesplash)

See also the list of [contributors](https://github.com/Techiesplash/ParentalControls/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
