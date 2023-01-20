cd test
make
mv testdummyprogram ../testdummyprogram
mv tester ../tester

cd ..
make
sudo ./tester
make clean

rm testdummyprogram
rm tester