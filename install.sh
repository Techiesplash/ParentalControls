# Compile
make

# Install
cp ./parentald /usr/local/bin/parentald
cp ./parentalctl /usr/bin/parentalctl
cp ./systemd/parentald.service /etc/systemd/system/parentald.service
chmod 640 /etc/systemd/system/parentald.service
systemctl daemon-reload
systemctl enable --now parentald.service