<p align="center">
  <a href="">
    <img src="https://github.com/Gio200023/Fundamentals_of_Robotics/blob/main/logo1.png">
  </a>
  <h2 align="center">Continual Learning on Max78000 Microcontroller</h2>

  <p align="center">
  Application of Continual Learning on Embedded Device
  <br>University of Trento 
  </p>
</p>
<br>

August 31, 2022

## Table of Contents
* [Repository Structure](#repository-structure)
* [Project Description](#project-description)
* [Tools Installation](#tools-installation)
  * [Prerequisites](#prerequisites)
  * [Project Installation](#project-installation)
  * [Embedded Software Development Kit](#embedded-software-development-kit)
* [Model Training and Synthesis](#model-training-and-synthesis)
* [Build and Flash](#build-and-flash)

## Repository Structure
The repo is structured in the following components:

* `Latex`: contains the source latex, the images used for the thesis and a PDF version of the thesis.
* `emnist_scripts`: contains the EMNIST network model, the EMNIST dataset and scripts to generate samples input from the EMNSIT dataset.
* `python_scripts`: contains python scripts used during the implementation of the project. Each script is commentend with the explanations of it.
* `sample_data_emnist`: contains 1000 smaples from the EMNIST dataset. Those samples are all 'A'.
* `main.c`: it is the head file of the project. This file contains the main pipeline of the CL system, from the CNN inferences to the weights update.
* `backpropagation.c`: this file contain the algorithm applied to find/update the weights and the biases. 
* `weights.c`: contains the weights and biases array.
* `cnn.c`: is the driver file to interact with the CNN accelerator.

---

## Project Description

This project develops a Continual Learning system on an embedded device. Specifically, the device is the [Max78000](https://www.maximintegrated.com/en/products/microcontrollers/MAX78000.html). The board supports a CNN accelerator that enables battery-powered applications to execute AI inferences while spending only microjoules of energy. 

<p align="center">
  <img src="https://www.maximintegrated.com/content/dam/images/product-images/evkits/max78000fthr.jpg" width="500" > 
</p>


<br />
The nexts sections explain how to install the tools required to develop and deploy a project in Max78000.
---

## Tools Installation
The SDK (Software Development Kit) is the most important tool to develop easily a project. Includint the SDK, the expected file system should be like this:

```sh
../ai8x-training/
../ai8x-synthesis/
../MaximSDK/
```
> ".." is the root project

Clone from Github the repositories required inside the root project (I cloned them into my $HOME directory):
```sh
$ git clone --recursive https://github.com/MaximIntegratedAI/ai8x-training.git
$ git clone --recursive https://github.com/MaximIntegratedAI/ai8x-synthesis.git
$ git clone --recursive https://github.com/MaximIntegratedAI/MAX78000_SDK
```
> Note! 
> Inside the synthesis folder there is already a SDK folder, I also cloned the third repository to have more clarity and division. They are the same repositories

### Prerequisites
This software requires PyTorch. Since PyTorch training is very long and require a lot of computation, to train the network model a Cuda 11 device is higly recommended. Ubuntu 20.04 LTS is the official operating system supported by the Maxim tools. I worked on MacOS system to develop the project and used an external computer to train the network. Windows operating system is also supported using WSL2 (windows subsytem for Linux), so every step needed for the linux system are also needed for the windows WSL2 one.

### Project Installation
Some base packages are required.
##### macOS
```sh
$ brew install libomp libsndfile tcl-tk
```
##### Linux
```sh
$ sudo apt-get install -y make build-essential libssl-dev zlib1g-dev \
  libbz2-dev libreadline-dev libsqlite3-dev wget curl llvm \
  libncurses5-dev libncursesw5-dev xz-utils tk-dev libffi-dev liblzma-dev \
  libsndfile-dev portaudio19-dev
```

#### Python 3.8 Pyenv
Python interpreter is almost important as the other tools. My reccomandation is to install pyenv to isolate the different packages needed by the synthetizer and the training folders. <br />

###### MacOS
```sh
$ brew install pyenv pyenv-virtualenv
```
###### Linux
```sh
$ curl -L https://github.com/pyenv/pyenv-installer/raw/master/bin/pyenv-installer | bash  # NOTE: Verify contents of the script before running it!!
```
To enable pyenv each time it called, attached to the end of the .zshrc or .bashrc (based on your shell) the terminal output after installing Pyenv.

Then **open a new terminal** and type:
```sh
$ pyenv install 3.8.11
```
Once installed, create a new environment:
```sh
cd ai8x-training
pyenv local 3.8.11
# check with:
python --version
```
The output should be 3.8.11
Then continue with the following and activate the environment:
```sh
$ python -m venv venv --prompt ai8x-training
$ source venv/bin/activate
```
Then continue with:
```sh
(ai8x-training) $ pip3 install -U pip wheel setuptools
``` 
Next steps differs depending on the system uses CUDA 11.x, or not.
CUDA 11.x on Linux:
```sh
(ai8x-training) $ pip3 install -r requirements-cu11.txt
``` 
For all other systems, including MacOS and CUDA 10.2 on Linux:
```sh
(ai8x-training) $ pip3 install -r requirements.txt
``` 
Now for the synthetis repository do the same exact things, just change directory and remember to 
```sh
(ai8x-training) $ deactivate
``` 
before proceeding to generate another environment for the synthetis folder.
> The `ai8x-synthesis` does not require CUDA

##### Installation Completed
Now the installation of the network tools is done. Remember to deactivate/activate each time you change a folder.
Now proceed wit the installation of the SDK.

### Embedded Software Development Kit

The Embedded SDK for MAX78000 and MAX78002 is used to compile, flash, and debug the output of the ai8x-synthesis (“izer”) tool. It also enables general software development for the microcontroller cores of the MAX78000 and MAX78002. It consists of the following components:

* Peripheral Drivers
* Board Support Packages (BSPs)
* Libraries
* Examples
* Toolchain
  * Arm GCC
  * RISC-V GCC
  * Make
  * OpenOCD

There are two ways to install the SDK.

#### Method 1: SDK installer
The Microcontroller SDK for MAX78000/MAX7802 (“MaximSDK”) is available via the installer links below. These installers require a GUI on your system.

1. Download the MaximSDK installer for your operating system from one of the links below.
    * [Windows](https://www.maximintegrated.com/content/maximintegrated/en/design/software-description.html/swpart=SFW0010820A)
    * [Ubuntu Linux](https://www.maximintegrated.com/content/maximintegrated/en/design/software-description.html/swpart=SFW0018720A)
    * [macOS](https://www.maximintegrated.com/content/maximintegrated/en/design/software-description.html/swpart=SFW0018610A)

2. Run the installer executable. Note: On Linux, this may require making the file executable with the following command:

    ```bash
    $ chmod +x MaximMicrosSDK_linux.run
    ```

3. Follow the instructions in the installer to the component selection.

4. Select the components to install. At _minimum_, the following components must be selected. This will enable command-line development.

    * GNU RISC-V Embedded GCC
    * GNU Tools for ARM Embedded Processors
    * Open On-Chip Debugger
    * MSYS2 (only on Windows)
    * Microcontrollers
      * MAX78000 Resources
      * MAX78002 Resources
    * Product Libs
      * CMSIS Core Libraries
      * Miscellaneous Drivers
      * Peripheral Drivers

5. (Optional) Select the “Eclipse” and/or “Visual Studio Code Support” components to add support for those IDEs.

6. Continue through the instructions to complete the installation of the MaximSDK.

7. (macOS only) Install OpenOCD dependencies using [Homebrew](https://brew.sh/)

    ```shell
    $ brew install libusb-compat libftdi hidapi libusb
    ```

8. (Linux and macOS only) Add the location of the toolchain binaries to the system `PATH`.

    On Linux and macOS, copy the following contents into `~/.profile`...
    On macOS, _also_ copy the following contents into `~/.zprofile`...
    ...and change `MAXIM_PATH` to the installation location of the MaximSDK.

    ```shell
    # MaximSDK location
    MAXIM_PATH=$HOME/MaximSDK  # Change me!
    export MAXIM_PATH
    
    # Arm GCC
    ARMGCC_DIR=$MAXIM_PATH/Tools/GNUTools/10.3
    echo $PATH | grep -q -s "$ARMGCC_DIR/bin"
    if [ $? -eq 1 ] ; then
        PATH=$PATH:"$ARMGCC_DIR/bin"
        export PATH
        export ARMGCC_DIR
    fi
    
    # RISC-V GCC
    RISCVGCC_DIR=$MAXIM_PATH/Tools/xPack/riscv-none-embed-gcc/10.2.0-1.2
    echo $PATH | grep -q -s "$RISCVGCC_DIR/bin"
    if [ $? -eq 1 ] ; then
        PATH=$PATH:"$RISCVGCC_DIR/bin"
        export PATH
        export RISCVGCC_DIR
    fi
    
    # OpenOCD
    OPENOCD_DIR=$MAXIM_PATH/Tools/OpenOCD
    echo $PATH | grep -q -s "$OPENOCD_DIR"
    if [ $? -eq 1 ] ; then
        PATH=$PATH:$OPENOCD_DIR
        export PATH
        export OPENOCD_DIR
    fi
    ```

    On Windows, this step is not necessary. However, “MaximSDK/Tools/MSYS2/msys.bat” file _must_ be used to launch the MSYS2 terminal for command-line development.

Once the tools above have been installed, continue with [Final Check](#final-check).

#### Method 2: Manual Installation

The MAX78000/MAX78002 SDK is available as a git submodule of ai8x-synthesis. It is checked out automatically to a version compatible with the project into the folder `ai8x-synthesis/sdk`. This submodule contains all of the SDK's components _except_ the Arm GCC, RISC-V GCC, and Make. These must be downloaded and installed manually.

1. Download and install the Arm Embedded GNU Toolchain from [https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads).

    * Recommended version: 10.3-2021.10 *(newer versions may or may not work correctly)*
    * Recommended installation location: `/usr/local/gcc-arm-none-eabi-10.3-2021.10/`

2. Download and install the RISC-V Embedded GNU Toolchain from [https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack/releases/](https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack/releases/)

    * Recommended version: 10.2.0-1.2 *(newer versions may or may not work correctly)*
    * Recommended installation location: `/usr/local/riscv-none-embed-gcc/10.2.0-1.2/`

3. Install GNU Make

    * (Linux/macOS) “make” is available on most systems by default. If not, it can be installed via the system package manager.
    * (Windows) Install [MSYS2](https://www.msys2.org/) first, then install “make” using the MSYS2 package manager:

      ```shell
      $ pacman -S --needed base filesystem msys2-runtime make
      ```

4. Install packages for OpenOCD. OpenOCD binaries are available in the “openocd” sub-folder of the ai8x-synthesis repository. However, some additional dependencies are required on most systems. See [openocd/Readme.md](openocd/Readme.md) for a list of packages to install, then return here to continue.

5. Add the location of the toolchain binaries to the system path.

    On Linux and macOS, copy the following contents into `~/.profile`...
    On macOS, _also_ copy the following contents into `~/.zprofile`...
    ...adjusting for the actual `PATH` to the compilers and the system’s architecture (`TARGET_ARCH`):

    ```shell
    # Arm GCC
    ARMGCC_DIR=/usr/local/gcc-arm-none-eabi-10.3-2021.10  # Change me!
    echo $PATH | grep -q -s "$ARMGCC_DIR/bin"
    if [ $? -eq 1 ] ; then
        PATH=$PATH:"$ARMGCC_DIR/bin"
        export PATH
        export ARMGCC_DIR
    fi
    
    # RISC-V GCC
    RISCVGCC_DIR=/usr/local/xpack-riscv-none-embed-gcc-10.2.0-1.2  # Change me!
    echo $PATH | grep -q -s "$RISCVGCC_DIR/bin"
    if [ $? -eq 1 ] ; then
        PATH=$PATH:"$RISCVGCC_DIR/bin"
        export PATH
        export RISCVGCC_DIR
    fi
    
    # OpenOCD
    OPENOCD_DIR=$HOME/Documents/Source/ai8x-synthesis/openocd/bin/TARGET_ARCH  # Change me!
    echo $PATH | grep -q -s "$OPENOCD_DIR"
    if [ $? -eq 1 ] ; then
        PATH=$PATH:$OPENOCD_DIR
        export PATH
        export OPENOCD_DIR
    fi
    ```

    On Windows, add the toolchain paths to the system `PATH` variable (search for  “edit the system environment variables” in the Windows search bar).

Once the tools above have been installed, continue to the [Final Check](#final-check) step below.

#### Final Check

After a successful manual or SDK installation, the following commands will run from on the terminal and display their version numbers:

* `arm-none-eabi-gcc -v`
* `arm-none-eabi-gdb -v`
* `make -v`
* `openocd -v`

`gen-demos-max78000.sh` and `gen-demos-max78002.sh` will create code that is compatible with the SDK and copy it into the SDK’s Example directories.

---

## Model Training and Synthesis
Every step required to create a Network Model, train it and synthesize it (transform it in C code) are explained in [ai8x-synthesis](https://github.com/MaximIntegratedAI/ai8x-synthesis). There you can find each steps to developed,train and load a custom model or a pretrained model on Max78000.  

---

## Build and Flash
