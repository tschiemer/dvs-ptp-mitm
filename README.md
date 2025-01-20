

                              /[-])//  ___
                         __ --\ `_/~--|  / \
                       /_-/~~--~~ /~~~\\_\ /\
                       |  |___|===|_-- | \ \ \
     _/~~~~~~~~|~~\,   ---|---\___/----|  \/\-\
     ~\________|__/   / // \__ |  ||  / | |   | |
              ,~-|~~~~~\--, | \|--|/~|||  |   | |
              [3-|____---~~ _--'==;/ _,   |   |_|
                          /   /\__|_/  \  \__/--/
                         /---/_\  -___/ |  /,--|
                         /  /\/~--|   | |  \///
                        /  / |-__ \    |/
                       |--/ /      |-- | \
                      \^~~\\/\      \   \/- _
                       \    |  \     |~~\~~| \
                        \    \  \     \   \  | \
                          \    \ |     \   \    \
                           |~~|\/\|     \   \   |
                          |   |/         \_--_- |\
                          |  /            /   |/\/
                           ~~             /  /
                                         |__/


               ==== DVS PTP MITM =====

    Targets:

	h|help		shows this help.txt
	b|build		compiles code
	c|clean		remove built code
	dir		echo directory for manual intervention

    The following targets require sudo, ex 'sudo make install'

	install		sets up man-in-the-middle
	uninstall	remove man-in-the-middle


# Installation notes

## macOS

Creating and using the installation script requires you to work on the terminal and to have the essential command line tools installed.

1. Uncomment the desired options in the beginning of `ptp-mitm.c` (options below are default):
```
// #define DISABLE_SLAVE_ONLY 		// Allow DVS to become leader
// #define ENABLE_PTPV2 					// Enable PTPv2 support
```
2. Open up the terminal by starting the `Terminal.app` in `Applications > Utilities`
3. Change to the directory to where you saved the (unzipped) files of this repository. Ex if the files are located on your desktop in a folder dvs-ptp-mitm type `cd ~/Desktop/dcs-ptp-mitm`.
4. If you don't know wether you have the command line tools installed type `xcode-select --install`
5. When you thus type `make` you should see the contents of this readme printed onto the screen.
7. To create/compile the source code to a binary type `make build`. This should create a file called ptp-mitm in the same folder.
8. To install the binary type `sudo make install`

9. To uninstall again type `sudo make uninstall`

To simplify repeated installation (step 6) and uninstallation (step 7) you can also run the two automator apps `Activate / Deactivate DVS-PTP-MITM`.

## Windows

The makefile / scripts do not work, manual compilation and installation is required.

If you have no other compiler at hand, you could use the mingw compiler for which you will find an installer here:

https://github.com/Vuniverse0/mingwInstaller/releases/

To compile, in command line (once changed to directory with `ptp-mitm.c` file) type the following command which should generate a `ptp-mitm.exe` file:

`cc -o ptp-mitm ptp-mitm.c`

Please remember to uncomment the desired options in the beginning of `ptp-mitm.c` before compilation.

## Manual Installation

In DVS's application library (on macos `/Library/Application Support/Audinate/DanteVirtualSoundcard`, on windows `C:\Program Files\Audinate\Dante Virtual Soundcard`) rename the original `ptp` file to `ptp-original` and copy the compiled `ptp-mitm` to in place of the old `ptp` binary.



# Application note

As you can also clearly see when looking at the source code `ptp-mitm.c` what happens is that the new executable calls the original ptp executable with the exact same arguments *except* for the changed options.

DVS's ptp service comes with more possibilities than actually enabled through normal DVS use.
