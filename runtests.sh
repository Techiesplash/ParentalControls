cd test
make
mv testdummyprogram ../testdummyprogram
mv tester ../tester

cd ..
make
sudo ./tester
result=$?

rm parentald
rm parentalctl

rm testdummyprogram
rm tester