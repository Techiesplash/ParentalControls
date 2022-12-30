# Compile
make

# Install
sudo cp ./parentald /usr/local/bin/parentald
sudo cp ./parentalctl /usr/local/bin/parentalctl
sudocp ./init/systemd/parentald.service /etc/systemd/system/parentald.service
sudo chmod 640 /etc/systemd/system/parentald.service
sudo systemctl daemon-reload
sudo systemctl enable --now parentald.service