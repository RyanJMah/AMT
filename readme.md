This project attempts to build an automatic music transciber using
digital signal processing techniques.

**To install and run:**

```bash
# clone the repo
git clone https://github.com/RyanJMah/AMT.git
cd AMT

# build
cd cpp
make
```

**Editing `cpp/makefile`**

Depending on your system, you will need to make some edits to `cpp/makefile`
to get it to build. Below is a list of variables you may need to edit:

* `SHELL` - change to your shell of choice (ex. `zsh`, `bash`, etc.)
* `OS` - change to either "macos" or "linux"
* `BOOST_PY_VER` - change to the version of Python you're running on your
system **without** any dots (ex. 38 for python3.8)
* `PY_VER` - change to the version of Python you're running on your system 
**with** dots (ex. 3.8 for python3.8)