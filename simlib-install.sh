#!/bin/bash

# Define the download link
SIMLIB_LINK="https://www.fit.vutbr.cz/~peringer/SIMLIB/source/simlib-3.08-20211004.tar.gz"

# Update and Upgrade the System (Optional, for Debian/Ubuntu systems)
echo "Updating system..."
sudo apt-get update && sudo apt-get upgrade -y

# Install dependencies (example, adjust according to your needs)
echo "Installing required dependencies..."
sudo apt-get install -y build-essential wget

# Download simlib (Replace this part with the appropriate command if it's not a direct download)
echo "Downloading simlib..."
wget $SIMLIB_LINK -O simlib.tar.gz

# Extract the downloaded file
echo "Extracting simlib..."
tar -zxvf simlib.tar.gz

# Navigate to the simlib directory (Adjust the directory name as needed)
cd simlib

# Compile and Install simlib (Adjust these commands according to the actual installation instructions)
echo "Compiling and installing simlib..."
make
ls
sudo make install -B
sudo ldconfig

echo "simlib installation completed!"

# Clean up downloaded files (Optional)
echo "Cleaning up..."
cd ..
rm -rf simlib.tar.gz simlib

echo "Done."