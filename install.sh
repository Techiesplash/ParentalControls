# Test
echo "Going to check if the program is working right, please wait..."
cd test
make
mv testdummyprogram ../testdummyprogram
mv tester ../tester

cd ..
make
sudo ./tester
testResults=$?

rm testdummyprogram
rm tester

echo $testResults
success=0
if [ "$testResults" -eq "$success" ]
then
    # Compile
    make

    # Install
    sudo cp ./parentald /usr/local/bin/parentald
    sudo cp ./parentalctl /usr/local/bin/parentalctl
    sudo cp ./init/systemd/parentald.service /etc/systemd/system/parentald.service
    sudo chmod 640 /etc/systemd/system/parentald.service
    sudo systemctl daemon-reload
    sudo systemctl enable --now parentald.service

    # Cleanup
    make clean
else
    echo "One or more tests failed. This means the program might not be working. Aborted installation."
fi
