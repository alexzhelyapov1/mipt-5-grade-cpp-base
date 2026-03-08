# Ubuntu 22.04

### Update cmake
```sh
sudo apt purge --auto-remove cmake

sudo apt update && sudo apt install -y gpg wget apt-transport-https

wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main" | sudo tee /etc/apt/sources.list.d/kitware.list >/dev/null

sudo apt update && sudo apt install -y cmake
```

### Update ninja
```sh
pip install --upgrade ninja
ninja --version
```

### Update clang to 18 version
```sh
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh 18 all

sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt update && sudo apt install -y libstdc++-14-dev
```