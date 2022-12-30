systemctl disable --now parentald.service
systemctl daemon-reload

sudo rm /etc/systemd/system/parentald.service
sudo rm /usr/local/bin/parentald
sudo rm /usr/local/bin/parentalctl
sudo rm /usr/local/bin/parentalgui

# For older versions
sudo rm /usr/bin/parentalctl
sudo rm /usr/bin/parentalgui