#Requirements and installation for nrf connect for desktop for Ubuntu 22.04.4 LTS:
https://docs.nordicsemi.com/bundle/nrf-connect-desktop/page/download_cfd.html

Download nRF Connect for Desktop’s executable from Nordic Semiconductor’s website(https://www.nordicsemi.com/Products/Development-tools/nrf-connect-for-desktop).

#Additional requirements

SEGGER J-Link driver

sudo dpkg -i JLink_Linux_V798d_x86_64.deb

Installing libusb-1.0-0 and nrf-udev on Linux

sudo dpkg -i nrf-udev_1.0.1-all.deb

sudo apt-get install libusb-1.0-0

#These are the nessary steps for running the nrfconnect-5.0.2-x86_64.appimage:


sudo apt update
sudo apt upgrade -y
sudo apt install libfuse2
chmod a+x ./nrfconnect-5.0.2-x86_64.appimage
./nrfconnect-5.0.2-x86_64.appimage




######### Maybe this is nesseary too: 
sudo apt install p7zip-full


### For Installing Wireshark
https://www.cherryservers.com/blog/install-wireshark-ubuntu




For Opening nrf connect for desktop application use this command:
./nrfconnect-5.0.2-x86_64.appimage


