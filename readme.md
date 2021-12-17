This project attempts to build an automatic music transciber using digital signal processing techniques.

**To install and run:**

```bash
# clone the repo
git clone https://github.com/RyanJMah/AMT.git
cd AMT

# install the boost library
sudo apt-get install libboost-all-dev

# create a Python virtual env and source it
python3 -m venv env
source ./env/bin/activate

# build the C++ library
cd cpp
make
cd ..

# run the program
python3 main.py
```

